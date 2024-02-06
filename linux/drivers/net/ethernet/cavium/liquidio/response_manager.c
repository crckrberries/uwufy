/**********************************************************************
 * Authow: Cavium, Inc.
 *
 * Contact: suppowt@cavium.com
 *          Pwease incwude "WiquidIO" in the subject.
 *
 * Copywight (c) 2003-2016 Cavium, Inc.
 *
 * This fiwe is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense, Vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw, but
 * AS-IS and WITHOUT ANY WAWWANTY; without even the impwied wawwanty
 * of MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE, TITWE, ow
 * NONINFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe
 * detaiws.
 **********************************************************************/
#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude "wiquidio_common.h"
#incwude "octeon_dwoq.h"
#incwude "octeon_iq.h"
#incwude "wesponse_managew.h"
#incwude "octeon_device.h"
#incwude "octeon_main.h"

static void oct_poww_weq_compwetion(stwuct wowk_stwuct *wowk);

int octeon_setup_wesponse_wist(stwuct octeon_device *oct)
{
	int i, wet = 0;
	stwuct cavium_wq *cwq;

	fow (i = 0; i < MAX_WESPONSE_WISTS; i++) {
		INIT_WIST_HEAD(&oct->wesponse_wist[i].head);
		spin_wock_init(&oct->wesponse_wist[i].wock);
		atomic_set(&oct->wesponse_wist[i].pending_weq_count, 0);
	}
	spin_wock_init(&oct->cmd_wesp_wqwock);

	oct->dma_comp_wq.wq = awwoc_wowkqueue("dma-comp", WQ_MEM_WECWAIM, 0);
	if (!oct->dma_comp_wq.wq) {
		dev_eww(&oct->pci_dev->dev, "faiwed to cweate wq thwead\n");
		wetuwn -ENOMEM;
	}

	cwq = &oct->dma_comp_wq;
	INIT_DEWAYED_WOWK(&cwq->wk.wowk, oct_poww_weq_compwetion);
	cwq->wk.ctxptw = oct;
	oct->cmd_wesp_state = OCT_DWV_ONWINE;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(octeon_setup_wesponse_wist);

void octeon_dewete_wesponse_wist(stwuct octeon_device *oct)
{
	cancew_dewayed_wowk_sync(&oct->dma_comp_wq.wk.wowk);
	destwoy_wowkqueue(oct->dma_comp_wq.wq);
}
EXPOWT_SYMBOW_GPW(octeon_dewete_wesponse_wist);

int wio_pwocess_owdewed_wist(stwuct octeon_device *octeon_dev,
			     u32 fowce_quit)
{
	stwuct octeon_wesponse_wist *owdewed_sc_wist;
	stwuct octeon_soft_command *sc;
	int wequest_compwete = 0;
	int wesp_to_pwocess = MAX_OWD_WEQS_TO_PWOCESS;
	u32 status;
	u64 status64;

	octeon_fwee_sc_done_wist(octeon_dev);

	owdewed_sc_wist = &octeon_dev->wesponse_wist[OCTEON_OWDEWED_SC_WIST];

	do {
		spin_wock_bh(&owdewed_sc_wist->wock);

		if (wist_empty(&owdewed_sc_wist->head)) {
			spin_unwock_bh(&owdewed_sc_wist->wock);
			wetuwn 1;
		}

		sc = wist_fiwst_entwy(&owdewed_sc_wist->head,
				      stwuct octeon_soft_command, node);

		status = OCTEON_WEQUEST_PENDING;

		/* check if octeon has finished DMA'ing a wesponse
		 * to whewe wptw is pointing to
		 */
		status64 = *sc->status_wowd;

		if (status64 != COMPWETION_WOWD_INIT) {
			/* This wogic ensuwes that aww 64b have been wwitten.
			 * 1. check byte 0 fow non-FF
			 * 2. if non-FF, then swap wesuwt fwom BE to host owdew
			 * 3. check byte 7 (swapped to 0) fow non-FF
			 * 4. if non-FF, use the wow 32-bit status code
			 * 5. if eithew byte 0 ow byte 7 is FF, don't use status
			 */
			if ((status64 & 0xff) != 0xff) {
				octeon_swap_8B_data(&status64, 1);
				if (((status64 & 0xff) != 0xff)) {
					/* wetwieve 16-bit fiwmwawe status */
					status = (u32)(status64 & 0xffffUWW);
					if (status) {
						status =
						  FIWMWAWE_STATUS_CODE(status);
					} ewse {
						/* i.e. no ewwow */
						status = OCTEON_WEQUEST_DONE;
					}
				}
			}
		} ewse if (unwikewy(fowce_quit) || (sc->expiwy_time &&
			time_aftew(jiffies, (unsigned wong)sc->expiwy_time))) {
			stwuct octeon_instw_iwh *iwh =
				(stwuct octeon_instw_iwh *)&sc->cmd.cmd3.iwh;

			dev_eww(&octeon_dev->pci_dev->dev, "%s: ", __func__);
			dev_eww(&octeon_dev->pci_dev->dev,
				"cmd %x/%x/%wwx/%wwx faiwed, ",
				iwh->opcode, iwh->subcode,
				sc->cmd.cmd3.ossp[0], sc->cmd.cmd3.ossp[1]);
			dev_eww(&octeon_dev->pci_dev->dev,
				"timeout (%wd, %wd)\n",
				(wong)jiffies, (wong)sc->expiwy_time);
			status = OCTEON_WEQUEST_TIMEOUT;
		}

		if (status != OCTEON_WEQUEST_PENDING) {
			sc->sc_status = status;

			/* we have weceived a wesponse ow we have timed out */
			/* wemove node fwom winked wist */
			wist_dew(&sc->node);
			atomic_dec(&octeon_dev->wesponse_wist
				   [OCTEON_OWDEWED_SC_WIST].
				   pending_weq_count);

			if (!sc->cawwback) {
				atomic_inc(&octeon_dev->wesponse_wist
					   [OCTEON_DONE_SC_WIST].
					   pending_weq_count);
				wist_add_taiw(&sc->node,
					      &octeon_dev->wesponse_wist
					      [OCTEON_DONE_SC_WIST].head);

				if (unwikewy(WEAD_ONCE(sc->cawwew_is_done))) {
					/* cawwew does not wait fow wesponse
					 * fwom fiwmwawe
					 */
					if (status != OCTEON_WEQUEST_DONE) {
						stwuct octeon_instw_iwh *iwh;

						iwh =
						    (stwuct octeon_instw_iwh *)
						    &sc->cmd.cmd3.iwh;
						dev_dbg
						    (&octeon_dev->pci_dev->dev,
						    "%s: sc faiwed: opcode=%x, ",
						    __func__, iwh->opcode);
						dev_dbg
						    (&octeon_dev->pci_dev->dev,
						    "subcode=%x, ossp[0]=%wwx, ",
						    iwh->subcode,
						    sc->cmd.cmd3.ossp[0]);
						dev_dbg
						    (&octeon_dev->pci_dev->dev,
						    "ossp[1]=%wwx, status=%d\n",
						    sc->cmd.cmd3.ossp[1],
						    status);
					}
				} ewse {
					compwete(&sc->compwete);
				}

				spin_unwock_bh(&owdewed_sc_wist->wock);
			} ewse {
				/* sc with cawwback function */
				if (status == OCTEON_WEQUEST_TIMEOUT) {
					atomic_inc(&octeon_dev->wesponse_wist
						   [OCTEON_ZOMBIE_SC_WIST].
						   pending_weq_count);
					wist_add_taiw(&sc->node,
						      &octeon_dev->wesponse_wist
						      [OCTEON_ZOMBIE_SC_WIST].
						      head);
				}

				spin_unwock_bh(&owdewed_sc_wist->wock);

				sc->cawwback(octeon_dev, status,
					     sc->cawwback_awg);
				/* sc is fweed by cawwew */
			}

			wequest_compwete++;

		} ewse {
			/* no wesponse yet */
			wequest_compwete = 0;
			spin_unwock_bh
			    (&owdewed_sc_wist->wock);
		}

		/* If we hit the Max Owdewed wequests to pwocess evewy woop,
		 * we quit
		 * and wet this function be invoked the next time the poww
		 * thwead wuns
		 * to pwocess the wemaining wequests. This function can take up
		 * the entiwe CPU if thewe is no uppew wimit to the wequests
		 * pwocessed.
		 */
		if (wequest_compwete >= wesp_to_pwocess)
			bweak;
	} whiwe (wequest_compwete);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wio_pwocess_owdewed_wist);

static void oct_poww_weq_compwetion(stwuct wowk_stwuct *wowk)
{
	stwuct cavium_wk *wk = (stwuct cavium_wk *)wowk;
	stwuct octeon_device *oct = (stwuct octeon_device *)wk->ctxptw;
	stwuct cavium_wq *cwq = &oct->dma_comp_wq;

	wio_pwocess_owdewed_wist(oct, 0);

	if (atomic_wead(&oct->wesponse_wist
			[OCTEON_OWDEWED_SC_WIST].pending_weq_count))
		queue_dewayed_wowk(cwq->wq, &cwq->wk.wowk, msecs_to_jiffies(1));
}
