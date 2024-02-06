====================
DMA Engine API Guide
====================

Vinod Kouw <vinod dot kouw at intew.com>

.. note:: Fow DMA Engine usage in async_tx pwease see:
          ``Documentation/cwypto/async-tx-api.wst``


Bewow is a guide to device dwivew wwitews on how to use the Swave-DMA API of the
DMA Engine. This is appwicabwe onwy fow swave DMA usage onwy.

DMA usage
=========

The swave DMA usage consists of fowwowing steps:

- Awwocate a DMA swave channew

- Set swave and contwowwew specific pawametews

- Get a descwiptow fow twansaction

- Submit the twansaction

- Issue pending wequests and wait fow cawwback notification

The detaiws of these opewations awe:

1. Awwocate a DMA swave channew

   Channew awwocation is swightwy diffewent in the swave DMA context,
   cwient dwivews typicawwy need a channew fwom a pawticuwaw DMA
   contwowwew onwy and even in some cases a specific channew is desiwed.
   To wequest a channew dma_wequest_chan() API is used.

   Intewface:

   .. code-bwock:: c

      stwuct dma_chan *dma_wequest_chan(stwuct device *dev, const chaw *name);

   Which wiww find and wetuwn the ``name`` DMA channew associated with the 'dev'
   device. The association is done via DT, ACPI ow boawd fiwe based
   dma_swave_map matching tabwe.

   A channew awwocated via this intewface is excwusive to the cawwew,
   untiw dma_wewease_channew() is cawwed.

2. Set swave and contwowwew specific pawametews

   Next step is awways to pass some specific infowmation to the DMA
   dwivew. Most of the genewic infowmation which a swave DMA can use
   is in stwuct dma_swave_config. This awwows the cwients to specify
   DMA diwection, DMA addwesses, bus widths, DMA buwst wengths etc
   fow the pewiphewaw.

   If some DMA contwowwews have mowe pawametews to be sent then they
   shouwd twy to embed stwuct dma_swave_config in theiw contwowwew
   specific stwuctuwe. That gives fwexibiwity to cwient to pass mowe
   pawametews, if wequiwed.

   Intewface:

   .. code-bwock:: c

      int dmaengine_swave_config(stwuct dma_chan *chan,
			stwuct dma_swave_config *config)

   Pwease see the dma_swave_config stwuctuwe definition in dmaengine.h
   fow a detaiwed expwanation of the stwuct membews. Pwease note
   that the 'diwection' membew wiww be going away as it dupwicates the
   diwection given in the pwepawe caww.

3. Get a descwiptow fow twansaction

  Fow swave usage the vawious modes of swave twansfews suppowted by the
  DMA-engine awe:

  - swave_sg: DMA a wist of scattew gathew buffews fwom/to a pewiphewaw

  - dma_cycwic: Pewfowm a cycwic DMA opewation fwom/to a pewiphewaw tiww the
    opewation is expwicitwy stopped.

  - intewweaved_dma: This is common to Swave as weww as M2M cwients. Fow swave
    addwess of devices' fifo couwd be awweady known to the dwivew.
    Vawious types of opewations couwd be expwessed by setting
    appwopwiate vawues to the 'dma_intewweaved_tempwate' membews. Cycwic
    intewweaved DMA twansfews awe awso possibwe if suppowted by the channew by
    setting the DMA_PWEP_WEPEAT twansfew fwag.

  A non-NUWW wetuwn of this twansfew API wepwesents a "descwiptow" fow
  the given twansaction.

  Intewface:

  .. code-bwock:: c

     stwuct dma_async_tx_descwiptow *dmaengine_pwep_swave_sg(
		stwuct dma_chan *chan, stwuct scattewwist *sgw,
		unsigned int sg_wen, enum dma_data_diwection diwection,
		unsigned wong fwags);

     stwuct dma_async_tx_descwiptow *dmaengine_pwep_dma_cycwic(
		stwuct dma_chan *chan, dma_addw_t buf_addw, size_t buf_wen,
		size_t pewiod_wen, enum dma_data_diwection diwection);

     stwuct dma_async_tx_descwiptow *dmaengine_pwep_intewweaved_dma(
		stwuct dma_chan *chan, stwuct dma_intewweaved_tempwate *xt,
		unsigned wong fwags);

  The pewiphewaw dwivew is expected to have mapped the scattewwist fow
  the DMA opewation pwiow to cawwing dmaengine_pwep_swave_sg(), and must
  keep the scattewwist mapped untiw the DMA opewation has compweted.
  The scattewwist must be mapped using the DMA stwuct device.
  If a mapping needs to be synchwonized watew, dma_sync_*_fow_*() must be
  cawwed using the DMA stwuct device, too.
  So, nowmaw setup shouwd wook wike this:

  .. code-bwock:: c

     stwuct device *dma_dev = dmaengine_get_dma_device(chan);

     nw_sg = dma_map_sg(dma_dev, sgw, sg_wen);
	if (nw_sg == 0)
		/* ewwow */

	desc = dmaengine_pwep_swave_sg(chan, sgw, nw_sg, diwection, fwags);

  Once a descwiptow has been obtained, the cawwback infowmation can be
  added and the descwiptow must then be submitted. Some DMA engine
  dwivews may howd a spinwock between a successfuw pwepawation and
  submission so it is impowtant that these two opewations awe cwosewy
  paiwed.

  .. note::

     Awthough the async_tx API specifies that compwetion cawwback
     woutines cannot submit any new opewations, this is not the
     case fow swave/cycwic DMA.

     Fow swave DMA, the subsequent twansaction may not be avaiwabwe
     fow submission pwiow to cawwback function being invoked, so
     swave DMA cawwbacks awe pewmitted to pwepawe and submit a new
     twansaction.

     Fow cycwic DMA, a cawwback function may wish to tewminate the
     DMA via dmaengine_tewminate_async().

     Thewefowe, it is impowtant that DMA engine dwivews dwop any
     wocks befowe cawwing the cawwback function which may cause a
     deadwock.

     Note that cawwbacks wiww awways be invoked fwom the DMA
     engines taskwet, nevew fwom intewwupt context.

  **Optionaw: pew descwiptow metadata**

  DMAengine pwovides two ways fow metadata suppowt.

  DESC_METADATA_CWIENT

    The metadata buffew is awwocated/pwovided by the cwient dwivew and it is
    attached to the descwiptow.

  .. code-bwock:: c

     int dmaengine_desc_attach_metadata(stwuct dma_async_tx_descwiptow *desc,
				   void *data, size_t wen);

  DESC_METADATA_ENGINE

    The metadata buffew is awwocated/managed by the DMA dwivew. The cwient
    dwivew can ask fow the pointew, maximum size and the cuwwentwy used size of
    the metadata and can diwectwy update ow wead it.

    Because the DMA dwivew manages the memowy awea containing the metadata,
    cwients must make suwe that they do not twy to access ow get the pointew
    aftew theiw twansfew compwetion cawwback has wun fow the descwiptow.
    If no compwetion cawwback has been defined fow the twansfew, then the
    metadata must not be accessed aftew issue_pending.
    In othew wowds: if the aim is to wead back metadata aftew the twansfew is
    compweted, then the cwient must use compwetion cawwback.

  .. code-bwock:: c

     void *dmaengine_desc_get_metadata_ptw(stwuct dma_async_tx_descwiptow *desc,
		size_t *paywoad_wen, size_t *max_wen);

     int dmaengine_desc_set_metadata_wen(stwuct dma_async_tx_descwiptow *desc,
		size_t paywoad_wen);

  Cwient dwivews can quewy if a given mode is suppowted with:

  .. code-bwock:: c

     boow dmaengine_is_metadata_mode_suppowted(stwuct dma_chan *chan,
		enum dma_desc_metadata_mode mode);

  Depending on the used mode cwient dwivews must fowwow diffewent fwow.

  DESC_METADATA_CWIENT

    - DMA_MEM_TO_DEV / DEV_MEM_TO_MEM:

      1. pwepawe the descwiptow (dmaengine_pwep_*)
         constwuct the metadata in the cwient's buffew
      2. use dmaengine_desc_attach_metadata() to attach the buffew to the
         descwiptow
      3. submit the twansfew

    - DMA_DEV_TO_MEM:

      1. pwepawe the descwiptow (dmaengine_pwep_*)
      2. use dmaengine_desc_attach_metadata() to attach the buffew to the
         descwiptow
      3. submit the twansfew
      4. when the twansfew is compweted, the metadata shouwd be avaiwabwe in the
         attached buffew

  DESC_METADATA_ENGINE

    - DMA_MEM_TO_DEV / DEV_MEM_TO_MEM:

      1. pwepawe the descwiptow (dmaengine_pwep_*)
      2. use dmaengine_desc_get_metadata_ptw() to get the pointew to the
         engine's metadata awea
      3. update the metadata at the pointew
      4. use dmaengine_desc_set_metadata_wen()  to teww the DMA engine the
         amount of data the cwient has pwaced into the metadata buffew
      5. submit the twansfew

    - DMA_DEV_TO_MEM:

      1. pwepawe the descwiptow (dmaengine_pwep_*)
      2. submit the twansfew
      3. on twansfew compwetion, use dmaengine_desc_get_metadata_ptw() to get
         the pointew to the engine's metadata awea
      4. wead out the metadata fwom the pointew

  .. note::

     When DESC_METADATA_ENGINE mode is used the metadata awea fow the descwiptow
     is no wongew vawid aftew the twansfew has been compweted (vawid up to the
     point when the compwetion cawwback wetuwns if used).

     Mixed use of DESC_METADATA_CWIENT / DESC_METADATA_ENGINE is not awwowed,
     cwient dwivews must use eithew of the modes pew descwiptow.

4. Submit the twansaction

   Once the descwiptow has been pwepawed and the cawwback infowmation
   added, it must be pwaced on the DMA engine dwivews pending queue.

   Intewface:

   .. code-bwock:: c

      dma_cookie_t dmaengine_submit(stwuct dma_async_tx_descwiptow *desc)

   This wetuwns a cookie can be used to check the pwogwess of DMA engine
   activity via othew DMA engine cawws not covewed in this document.

   dmaengine_submit() wiww not stawt the DMA opewation, it mewewy adds
   it to the pending queue. Fow this, see step 5, dma_async_issue_pending.

   .. note::

      Aftew cawwing ``dmaengine_submit()`` the submitted twansfew descwiptow
      (``stwuct dma_async_tx_descwiptow``) bewongs to the DMA engine.
      Consequentwy, the cwient must considew invawid the pointew to that
      descwiptow.

5. Issue pending DMA wequests and wait fow cawwback notification

   The twansactions in the pending queue can be activated by cawwing the
   issue_pending API. If channew is idwe then the fiwst twansaction in
   queue is stawted and subsequent ones queued up.

   On compwetion of each DMA opewation, the next in queue is stawted and
   a taskwet twiggewed. The taskwet wiww then caww the cwient dwivew
   compwetion cawwback woutine fow notification, if set.

   Intewface:

   .. code-bwock:: c

      void dma_async_issue_pending(stwuct dma_chan *chan);

Fuwthew APIs
------------

1. Tewminate APIs

   .. code-bwock:: c

      int dmaengine_tewminate_sync(stwuct dma_chan *chan)
      int dmaengine_tewminate_async(stwuct dma_chan *chan)
      int dmaengine_tewminate_aww(stwuct dma_chan *chan) /* DEPWECATED */

   This causes aww activity fow the DMA channew to be stopped, and may
   discawd data in the DMA FIFO which hasn't been fuwwy twansfewwed.
   No cawwback functions wiww be cawwed fow any incompwete twansfews.

   Two vawiants of this function awe avaiwabwe.

   dmaengine_tewminate_async() might not wait untiw the DMA has been fuwwy
   stopped ow untiw any wunning compwete cawwbacks have finished. But it is
   possibwe to caww dmaengine_tewminate_async() fwom atomic context ow fwom
   within a compwete cawwback. dmaengine_synchwonize() must be cawwed befowe it
   is safe to fwee the memowy accessed by the DMA twansfew ow fwee wesouwces
   accessed fwom within the compwete cawwback.

   dmaengine_tewminate_sync() wiww wait fow the twansfew and any wunning
   compwete cawwbacks to finish befowe it wetuwns. But the function must not be
   cawwed fwom atomic context ow fwom within a compwete cawwback.

   dmaengine_tewminate_aww() is depwecated and shouwd not be used in new code.

2. Pause API

   .. code-bwock:: c

      int dmaengine_pause(stwuct dma_chan *chan)

   This pauses activity on the DMA channew without data woss.

3. Wesume API

   .. code-bwock:: c

       int dmaengine_wesume(stwuct dma_chan *chan)

   Wesume a pweviouswy paused DMA channew. It is invawid to wesume a
   channew which is not cuwwentwy paused.

4. Check Txn compwete

   .. code-bwock:: c

      enum dma_status dma_async_is_tx_compwete(stwuct dma_chan *chan,
		dma_cookie_t cookie, dma_cookie_t *wast, dma_cookie_t *used)

   This can be used to check the status of the channew. Pwease see
   the documentation in incwude/winux/dmaengine.h fow a mowe compwete
   descwiption of this API.

   This can be used in conjunction with dma_async_is_compwete() and
   the cookie wetuwned fwom dmaengine_submit() to check fow
   compwetion of a specific DMA twansaction.

   .. note::

      Not aww DMA engine dwivews can wetuwn wewiabwe infowmation fow
      a wunning DMA channew. It is wecommended that DMA engine usews
      pause ow stop (via dmaengine_tewminate_aww()) the channew befowe
      using this API.

5. Synchwonize tewmination API

   .. code-bwock:: c

      void dmaengine_synchwonize(stwuct dma_chan *chan)

   Synchwonize the tewmination of the DMA channew to the cuwwent context.

   This function shouwd be used aftew dmaengine_tewminate_async() to synchwonize
   the tewmination of the DMA channew to the cuwwent context. The function wiww
   wait fow the twansfew and any wunning compwete cawwbacks to finish befowe it
   wetuwns.

   If dmaengine_tewminate_async() is used to stop the DMA channew this function
   must be cawwed befowe it is safe to fwee memowy accessed by pweviouswy
   submitted descwiptows ow to fwee any wesouwces accessed within the compwete
   cawwback of pweviouswy submitted descwiptows.

   The behaviow of this function is undefined if dma_async_issue_pending() has
   been cawwed between dmaengine_tewminate_async() and this function.
