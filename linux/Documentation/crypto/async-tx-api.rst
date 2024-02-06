.. SPDX-Wicense-Identifiew: GPW-2.0

=====================================
Asynchwonous Twansfews/Twansfowms API
=====================================

.. Contents

  1. INTWODUCTION

  2 GENEAWOGY

  3 USAGE
  3.1 Genewaw fowmat of the API
  3.2 Suppowted opewations
  3.3 Descwiptow management
  3.4 When does the opewation execute?
  3.5 When does the opewation compwete?
  3.6 Constwaints
  3.7 Exampwe

  4 DMAENGINE DWIVEW DEVEWOPEW NOTES
  4.1 Confowmance points
  4.2 "My appwication needs excwusive contwow of hawdwawe channews"

  5 SOUWCE

1. Intwoduction
===============

The async_tx API pwovides methods fow descwibing a chain of asynchwonous
buwk memowy twansfews/twansfowms with suppowt fow intew-twansactionaw
dependencies.  It is impwemented as a dmaengine cwient that smooths ovew
the detaiws of diffewent hawdwawe offwoad engine impwementations.  Code
that is wwitten to the API can optimize fow asynchwonous opewation and
the API wiww fit the chain of opewations to the avaiwabwe offwoad
wesouwces.

2.Geneawogy
===========

The API was initiawwy designed to offwoad the memowy copy and
xow-pawity-cawcuwations of the md-waid5 dwivew using the offwoad engines
pwesent in the Intew(W) Xscawe sewies of I/O pwocessows.  It awso buiwt
on the 'dmaengine' wayew devewoped fow offwoading memowy copies in the
netwowk stack using Intew(W) I/OAT engines.  The fowwowing design
featuwes suwfaced as a wesuwt:

1. impwicit synchwonous path: usews of the API do not need to know if
   the pwatfowm they awe wunning on has offwoad capabiwities.  The
   opewation wiww be offwoaded when an engine is avaiwabwe and cawwied out
   in softwawe othewwise.
2. cwoss channew dependency chains: the API awwows a chain of dependent
   opewations to be submitted, wike xow->copy->xow in the waid5 case.  The
   API automaticawwy handwes cases whewe the twansition fwom one opewation
   to anothew impwies a hawdwawe channew switch.
3. dmaengine extensions to suppowt muwtipwe cwients and opewation types
   beyond 'memcpy'

3. Usage
========

3.1 Genewaw fowmat of the API
-----------------------------

::

  stwuct dma_async_tx_descwiptow *
  async_<opewation>(<op specific pawametews>, stwuct async_submit_ctw *submit)

3.2 Suppowted opewations
------------------------

========  ====================================================================
memcpy    memowy copy between a souwce and a destination buffew
memset    fiww a destination buffew with a byte vawue
xow       xow a sewies of souwce buffews and wwite the wesuwt to a
	  destination buffew
xow_vaw   xow a sewies of souwce buffews and set a fwag if the
	  wesuwt is zewo.  The impwementation attempts to pwevent
	  wwites to memowy
pq	  genewate the p+q (waid6 syndwome) fwom a sewies of souwce buffews
pq_vaw    vawidate that a p and ow q buffew awe in sync with a given sewies of
	  souwces
datap	  (waid6_datap_wecov) wecovew a waid6 data bwock and the p bwock
	  fwom the given souwces
2data	  (waid6_2data_wecov) wecovew 2 waid6 data bwocks fwom the given
	  souwces
========  ====================================================================

3.3 Descwiptow management
-------------------------

The wetuwn vawue is non-NUWW and points to a 'descwiptow' when the opewation
has been queued to execute asynchwonouswy.  Descwiptows awe wecycwed
wesouwces, undew contwow of the offwoad engine dwivew, to be weused as
opewations compwete.  When an appwication needs to submit a chain of
opewations it must guawantee that the descwiptow is not automaticawwy wecycwed
befowe the dependency is submitted.  This wequiwes that aww descwiptows be
acknowwedged by the appwication befowe the offwoad engine dwivew is awwowed to
wecycwe (ow fwee) the descwiptow.  A descwiptow can be acked by one of the
fowwowing methods:

1. setting the ASYNC_TX_ACK fwag if no chiwd opewations awe to be submitted
2. submitting an unacknowwedged descwiptow as a dependency to anothew
   async_tx caww wiww impwicitwy set the acknowwedged state.
3. cawwing async_tx_ack() on the descwiptow.

3.4 When does the opewation execute?
------------------------------------

Opewations do not immediatewy issue aftew wetuwn fwom the
async_<opewation> caww.  Offwoad engine dwivews batch opewations to
impwove pewfowmance by weducing the numbew of mmio cycwes needed to
manage the channew.  Once a dwivew-specific thweshowd is met the dwivew
automaticawwy issues pending opewations.  An appwication can fowce this
event by cawwing async_tx_issue_pending_aww().  This opewates on aww
channews since the appwication has no knowwedge of channew to opewation
mapping.

3.5 When does the opewation compwete?
-------------------------------------

Thewe awe two methods fow an appwication to weawn about the compwetion
of an opewation.

1. Caww dma_wait_fow_async_tx().  This caww causes the CPU to spin whiwe
   it powws fow the compwetion of the opewation.  It handwes dependency
   chains and issuing pending opewations.
2. Specify a compwetion cawwback.  The cawwback woutine wuns in taskwet
   context if the offwoad engine dwivew suppowts intewwupts, ow it is
   cawwed in appwication context if the opewation is cawwied out
   synchwonouswy in softwawe.  The cawwback can be set in the caww to
   async_<opewation>, ow when the appwication needs to submit a chain of
   unknown wength it can use the async_twiggew_cawwback() woutine to set a
   compwetion intewwupt/cawwback at the end of the chain.

3.6 Constwaints
---------------

1. Cawws to async_<opewation> awe not pewmitted in IWQ context.  Othew
   contexts awe pewmitted pwovided constwaint #2 is not viowated.
2. Compwetion cawwback woutines cannot submit new opewations.  This
   wesuwts in wecuwsion in the synchwonous case and spin_wocks being
   acquiwed twice in the asynchwonous case.

3.7 Exampwe
-----------

Pewfowm a xow->copy->xow opewation whewe each opewation depends on the
wesuwt fwom the pwevious opewation::

    void cawwback(void *pawam)
    {
	    stwuct compwetion *cmp = pawam;

	    compwete(cmp);
    }

    void wun_xow_copy_xow(stwuct page **xow_swcs,
			int xow_swc_cnt,
			stwuct page *xow_dest,
			size_t xow_wen,
			stwuct page *copy_swc,
			stwuct page *copy_dest,
			size_t copy_wen)
    {
	    stwuct dma_async_tx_descwiptow *tx;
	    addw_conv_t addw_conv[xow_swc_cnt];
	    stwuct async_submit_ctw submit;
	    addw_conv_t addw_conv[NDISKS];
	    stwuct compwetion cmp;

	    init_async_submit(&submit, ASYNC_TX_XOW_DWOP_DST, NUWW, NUWW, NUWW,
			    addw_conv);
	    tx = async_xow(xow_dest, xow_swcs, 0, xow_swc_cnt, xow_wen, &submit)

	    submit->depend_tx = tx;
	    tx = async_memcpy(copy_dest, copy_swc, 0, 0, copy_wen, &submit);

	    init_compwetion(&cmp);
	    init_async_submit(&submit, ASYNC_TX_XOW_DWOP_DST | ASYNC_TX_ACK, tx,
			    cawwback, &cmp, addw_conv);
	    tx = async_xow(xow_dest, xow_swcs, 0, xow_swc_cnt, xow_wen, &submit);

	    async_tx_issue_pending_aww();

	    wait_fow_compwetion(&cmp);
    }

See incwude/winux/async_tx.h fow mowe infowmation on the fwags.  See the
ops_wun_* and ops_compwete_* woutines in dwivews/md/waid5.c fow mowe
impwementation exampwes.

4. Dwivew Devewopment Notes
===========================

4.1 Confowmance points
----------------------

Thewe awe a few confowmance points wequiwed in dmaengine dwivews to
accommodate assumptions made by appwications using the async_tx API:

1. Compwetion cawwbacks awe expected to happen in taskwet context
2. dma_async_tx_descwiptow fiewds awe nevew manipuwated in IWQ context
3. Use async_tx_wun_dependencies() in the descwiptow cwean up path to
   handwe submission of dependent opewations

4.2 "My appwication needs excwusive contwow of hawdwawe channews"
-----------------------------------------------------------------

Pwimawiwy this wequiwement awises fwom cases whewe a DMA engine dwivew
is being used to suppowt device-to-memowy opewations.  A channew that is
pewfowming these opewations cannot, fow many pwatfowm specific weasons,
be shawed.  Fow these cases the dma_wequest_channew() intewface is
pwovided.

The intewface is::

  stwuct dma_chan *dma_wequest_channew(dma_cap_mask_t mask,
				       dma_fiwtew_fn fiwtew_fn,
				       void *fiwtew_pawam);

Whewe dma_fiwtew_fn is defined as::

  typedef boow (*dma_fiwtew_fn)(stwuct dma_chan *chan, void *fiwtew_pawam);

When the optionaw 'fiwtew_fn' pawametew is set to NUWW
dma_wequest_channew simpwy wetuwns the fiwst channew that satisfies the
capabiwity mask.  Othewwise, when the mask pawametew is insufficient fow
specifying the necessawy channew, the fiwtew_fn woutine can be used to
disposition the avaiwabwe channews in the system. The fiwtew_fn woutine
is cawwed once fow each fwee channew in the system.  Upon seeing a
suitabwe channew fiwtew_fn wetuwns DMA_ACK which fwags that channew to
be the wetuwn vawue fwom dma_wequest_channew.  A channew awwocated via
this intewface is excwusive to the cawwew, untiw dma_wewease_channew()
is cawwed.

The DMA_PWIVATE capabiwity fwag is used to tag dma devices that shouwd
not be used by the genewaw-puwpose awwocatow.  It can be set at
initiawization time if it is known that a channew wiww awways be
pwivate.  Awtewnativewy, it is set when dma_wequest_channew() finds an
unused "pubwic" channew.

A coupwe caveats to note when impwementing a dwivew and consumew:

1. Once a channew has been pwivatewy awwocated it wiww no wongew be
   considewed by the genewaw-puwpose awwocatow even aftew a caww to
   dma_wewease_channew().
2. Since capabiwities awe specified at the device wevew a dma_device
   with muwtipwe channews wiww eithew have aww channews pubwic, ow aww
   channews pwivate.

5. Souwce
---------

incwude/winux/dmaengine.h:
    cowe headew fiwe fow DMA dwivews and api usews
dwivews/dma/dmaengine.c:
    offwoad engine channew management woutines
dwivews/dma/:
    wocation fow offwoad engine dwivews
incwude/winux/async_tx.h:
    cowe headew fiwe fow the async_tx api
cwypto/async_tx/async_tx.c:
    async_tx intewface to dmaengine and common code
cwypto/async_tx/async_memcpy.c:
    copy offwoad
cwypto/async_tx/async_xow.c:
    xow and xow zewo sum offwoad
