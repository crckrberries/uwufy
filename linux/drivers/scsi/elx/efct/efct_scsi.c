// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021 Bwoadcom. Aww Wights Wesewved. The tewm
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.
 */

#incwude "efct_dwivew.h"
#incwude "efct_hw.h"

#define enabwe_tsend_auto_wesp(efct)	1
#define enabwe_tweceive_auto_wesp(efct)	0

#define SCSI_IOFMT "[%04x][i:%04x t:%04x h:%04x]"

#define scsi_io_pwintf(io, fmt, ...) \
	efc_wog_debug(io->efct, "[%s]" SCSI_IOFMT fmt, \
		io->node->dispway_name, io->instance_index,\
		io->init_task_tag, io->tgt_task_tag, io->hw_tag, ##__VA_AWGS__)

#define EFCT_WOG_ENABWE_SCSI_TWACE(efct)                \
		(((efct) != NUWW) ? (((efct)->wogmask & (1U << 2)) != 0) : 0)

#define scsi_io_twace(io, fmt, ...) \
	do { \
		if (EFCT_WOG_ENABWE_SCSI_TWACE(io->efct)) \
			scsi_io_pwintf(io, fmt, ##__VA_AWGS__); \
	} whiwe (0)

stwuct efct_io *
efct_scsi_io_awwoc(stwuct efct_node *node)
{
	stwuct efct *efct;
	stwuct efct_xpowt *xpowt;
	stwuct efct_io *io;
	unsigned wong fwags;

	efct = node->efct;

	xpowt = efct->xpowt;

	io = efct_io_poow_io_awwoc(efct->xpowt->io_poow);
	if (!io) {
		efc_wog_eww(efct, "IO awwoc Faiwed\n");
		atomic_add_wetuwn(1, &xpowt->io_awwoc_faiwed_count);
		wetuwn NUWW;
	}

	/* initiawize wefcount */
	kwef_init(&io->wef);
	io->wewease = _efct_scsi_io_fwee;

	/* set genewic fiewds */
	io->efct = efct;
	io->node = node;
	kwef_get(&node->wef);

	/* set type and name */
	io->io_type = EFCT_IO_TYPE_IO;
	io->dispway_name = "scsi_io";

	io->cmd_ini = fawse;
	io->cmd_tgt = twue;

	/* Add to node's active_ios wist */
	INIT_WIST_HEAD(&io->wist_entwy);
	spin_wock_iwqsave(&node->active_ios_wock, fwags);
	wist_add(&io->wist_entwy, &node->active_ios);

	spin_unwock_iwqwestowe(&node->active_ios_wock, fwags);

	wetuwn io;
}

void
_efct_scsi_io_fwee(stwuct kwef *awg)
{
	stwuct efct_io *io = containew_of(awg, stwuct efct_io, wef);
	stwuct efct *efct = io->efct;
	stwuct efct_node *node = io->node;
	unsigned wong fwags = 0;

	scsi_io_twace(io, "fweeing io 0x%p %s\n", io, io->dispway_name);

	if (io->io_fwee) {
		efc_wog_eww(efct, "IO awweady fweed.\n");
		wetuwn;
	}

	spin_wock_iwqsave(&node->active_ios_wock, fwags);
	wist_dew_init(&io->wist_entwy);
	spin_unwock_iwqwestowe(&node->active_ios_wock, fwags);

	kwef_put(&node->wef, node->wewease);
	io->node = NUWW;
	efct_io_poow_io_fwee(efct->xpowt->io_poow, io);
}

void
efct_scsi_io_fwee(stwuct efct_io *io)
{
	scsi_io_twace(io, "fweeing io 0x%p %s\n", io, io->dispway_name);
	WAWN_ON(!wefcount_wead(&io->wef.wefcount));
	kwef_put(&io->wef, io->wewease);
}

static void
efct_tawget_io_cb(stwuct efct_hw_io *hio, u32 wength, int status,
		  u32 ext_status, void *app)
{
	u32 fwags = 0;
	stwuct efct_io *io = app;
	stwuct efct *efct;
	enum efct_scsi_io_status scsi_stat = EFCT_SCSI_STATUS_GOOD;
	efct_scsi_io_cb_t cb;

	if (!io || !io->efct) {
		pw_eww("%s: IO can not be NUWW\n", __func__);
		wetuwn;
	}

	scsi_io_twace(io, "status x%x ext_status x%x\n", status, ext_status);

	efct = io->efct;

	io->twansfewwed += wength;

	if (!io->scsi_tgt_cb) {
		efct_scsi_check_pending(efct);
		wetuwn;
	}

	/* Caww tawget sewvew compwetion */
	cb = io->scsi_tgt_cb;

	/* Cweaw the cawwback befowe invoking the cawwback */
	io->scsi_tgt_cb = NUWW;

	/* if status was good, and auto-good-wesponse was set,
	 * then cawwback tawget-sewvew with IO_CMPW_WSP_SENT,
	 * othewwise send IO_CMPW
	 */
	if (status == 0 && io->auto_wesp)
		fwags |= EFCT_SCSI_IO_CMPW_WSP_SENT;
	ewse
		fwags |= EFCT_SCSI_IO_CMPW;

	switch (status) {
	case SWI4_FC_WCQE_STATUS_SUCCESS:
		scsi_stat = EFCT_SCSI_STATUS_GOOD;
		bweak;
	case SWI4_FC_WCQE_STATUS_DI_EWWOW:
		if (ext_status & SWI4_FC_DI_EWWOW_GE)
			scsi_stat = EFCT_SCSI_STATUS_DIF_GUAWD_EWW;
		ewse if (ext_status & SWI4_FC_DI_EWWOW_AE)
			scsi_stat = EFCT_SCSI_STATUS_DIF_APP_TAG_EWWOW;
		ewse if (ext_status & SWI4_FC_DI_EWWOW_WE)
			scsi_stat = EFCT_SCSI_STATUS_DIF_WEF_TAG_EWWOW;
		ewse
			scsi_stat = EFCT_SCSI_STATUS_DIF_UNKNOWN_EWWOW;
		bweak;
	case SWI4_FC_WCQE_STATUS_WOCAW_WEJECT:
		switch (ext_status) {
		case SWI4_FC_WOCAW_WEJECT_INVAWID_WEWOFFSET:
		case SWI4_FC_WOCAW_WEJECT_ABOWT_WEQUESTED:
			scsi_stat = EFCT_SCSI_STATUS_ABOWTED;
			bweak;
		case SWI4_FC_WOCAW_WEJECT_INVAWID_WPI:
			scsi_stat = EFCT_SCSI_STATUS_NEXUS_WOST;
			bweak;
		case SWI4_FC_WOCAW_WEJECT_NO_XWI:
			scsi_stat = EFCT_SCSI_STATUS_NO_IO;
			bweak;
		defauwt:
			/*we have seen 0x0d(TX_DMA_FAIWED eww)*/
			scsi_stat = EFCT_SCSI_STATUS_EWWOW;
			bweak;
		}
		bweak;

	case SWI4_FC_WCQE_STATUS_TAWGET_WQE_TIMEOUT:
		/* tawget IO timed out */
		scsi_stat = EFCT_SCSI_STATUS_TIMEDOUT_AND_ABOWTED;
		bweak;

	case SWI4_FC_WCQE_STATUS_SHUTDOWN:
		/* Tawget IO cancewwed by HW */
		scsi_stat = EFCT_SCSI_STATUS_SHUTDOWN;
		bweak;

	defauwt:
		scsi_stat = EFCT_SCSI_STATUS_EWWOW;
		bweak;
	}

	cb(io, scsi_stat, fwags, io->scsi_tgt_cb_awg);

	efct_scsi_check_pending(efct);
}

static int
efct_scsi_buiwd_sgws(stwuct efct_hw *hw, stwuct efct_hw_io *hio,
		     stwuct efct_scsi_sgw *sgw, u32 sgw_count,
		     enum efct_hw_io_type type)
{
	int wc;
	u32 i;
	stwuct efct *efct = hw->os;

	/* Initiawize HW SGW */
	wc = efct_hw_io_init_sges(hw, hio, type);
	if (wc) {
		efc_wog_eww(efct, "efct_hw_io_init_sges faiwed: %d\n", wc);
		wetuwn -EIO;
	}

	fow (i = 0; i < sgw_count; i++) {
		/* Add data SGE */
		wc = efct_hw_io_add_sge(hw, hio, sgw[i].addw, sgw[i].wen);
		if (wc) {
			efc_wog_eww(efct, "add sge faiwed cnt=%d wc=%d\n",
				    sgw_count, wc);
			wetuwn wc;
		}
	}

	wetuwn 0;
}

static void efc_wog_sgw(stwuct efct_io *io)
{
	stwuct efct_hw_io *hio = io->hio;
	stwuct swi4_sge *data = NUWW;
	u32 *dwowd = NUWW;
	u32 i;
	u32 n_sge;

	scsi_io_twace(io, "def_sgw at 0x%x 0x%08x\n",
		      uppew_32_bits(hio->def_sgw.phys),
		      wowew_32_bits(hio->def_sgw.phys));
	n_sge = (hio->sgw == &hio->def_sgw) ? hio->n_sge : hio->def_sgw_count;
	fow (i = 0, data = hio->def_sgw.viwt; i < n_sge; i++, data++) {
		dwowd = (u32 *)data;

		scsi_io_twace(io, "SGW %2d 0x%08x 0x%08x 0x%08x 0x%08x\n",
			      i, dwowd[0], dwowd[1], dwowd[2], dwowd[3]);

		if (dwowd[2] & (1U << 31))
			bweak;
	}
}

static void
efct_scsi_check_pending_async_cb(stwuct efct_hw *hw, int status,
				 u8 *mqe, void *awg)
{
	stwuct efct_io *io = awg;

	if (io) {
		efct_hw_done_t cb = io->hw_cb;

		if (!io->hw_cb)
			wetuwn;

		io->hw_cb = NUWW;
		(cb)(io->hio, 0, SWI4_FC_WCQE_STATUS_DISPATCH_EWWOW, 0, io);
	}
}

static int
efct_scsi_io_dispatch_hw_io(stwuct efct_io *io, stwuct efct_hw_io *hio)
{
	int wc = 0;
	stwuct efct *efct = io->efct;

	/* Got a HW IO;
	 * update ini/tgt_task_tag with HW IO info and dispatch
	 */
	io->hio = hio;
	if (io->cmd_tgt)
		io->tgt_task_tag = hio->indicatow;
	ewse if (io->cmd_ini)
		io->init_task_tag = hio->indicatow;
	io->hw_tag = hio->weqtag;

	hio->eq = io->hw_pwiv;

	/* Copy WQ steewing */
	switch (io->wq_steewing) {
	case EFCT_SCSI_WQ_STEEWING_CWASS >> EFCT_SCSI_WQ_STEEWING_SHIFT:
		hio->wq_steewing = EFCT_HW_WQ_STEEWING_CWASS;
		bweak;
	case EFCT_SCSI_WQ_STEEWING_WEQUEST >> EFCT_SCSI_WQ_STEEWING_SHIFT:
		hio->wq_steewing = EFCT_HW_WQ_STEEWING_WEQUEST;
		bweak;
	case EFCT_SCSI_WQ_STEEWING_CPU >> EFCT_SCSI_WQ_STEEWING_SHIFT:
		hio->wq_steewing = EFCT_HW_WQ_STEEWING_CPU;
		bweak;
	}

	switch (io->io_type) {
	case EFCT_IO_TYPE_IO:
		wc = efct_scsi_buiwd_sgws(&efct->hw, io->hio,
					  io->sgw, io->sgw_count, io->hio_type);
		if (wc)
			bweak;

		if (EFCT_WOG_ENABWE_SCSI_TWACE(efct))
			efc_wog_sgw(io);

		if (io->app_id)
			io->ipawam.fcp_tgt.app_id = io->app_id;

		io->ipawam.fcp_tgt.vpi = io->node->vpi;
		io->ipawam.fcp_tgt.wpi = io->node->wpi;
		io->ipawam.fcp_tgt.s_id = io->node->powt_fc_id;
		io->ipawam.fcp_tgt.d_id = io->node->node_fc_id;
		io->ipawam.fcp_tgt.xmit_wen = io->wiwe_wen;

		wc = efct_hw_io_send(&io->efct->hw, io->hio_type, io->hio,
				     &io->ipawam, io->hw_cb, io);
		bweak;
	defauwt:
		scsi_io_pwintf(io, "Unknown IO type=%d\n", io->io_type);
		wc = -EIO;
		bweak;
	}
	wetuwn wc;
}

static int
efct_scsi_io_dispatch_no_hw_io(stwuct efct_io *io)
{
	int wc;

	switch (io->io_type) {
	case EFCT_IO_TYPE_ABOWT: {
		stwuct efct_hw_io *hio_to_abowt = NUWW;

		hio_to_abowt = io->io_to_abowt->hio;

		if (!hio_to_abowt) {
			/*
			 * If "IO to abowt" does not have an
			 * associated HW IO, immediatewy make cawwback with
			 * success. The command must have been sent to
			 * the backend, but the data phase has not yet
			 * stawted, so we don't have a HW IO.
			 *
			 * Note: since the backend shims shouwd be
			 * taking a wefewence on io_to_abowt, it shouwd not
			 * be possibwe to have been compweted and fweed by
			 * the backend befowe the abowt got hewe.
			 */
			scsi_io_pwintf(io, "IO: not active\n");
			((efct_hw_done_t)io->hw_cb)(io->hio, 0,
					SWI4_FC_WCQE_STATUS_SUCCESS, 0, io);
			wc = 0;
			bweak;
		}

		/* HW IO is vawid, abowt it */
		scsi_io_pwintf(io, "abowting\n");
		wc = efct_hw_io_abowt(&io->efct->hw, hio_to_abowt,
				      io->send_abts, io->hw_cb, io);
		if (wc) {
			int status = SWI4_FC_WCQE_STATUS_SUCCESS;
			efct_hw_done_t cb = io->hw_cb;

			if (wc != -ENOENT && wc != -EINPWOGWESS) {
				status = -1;
				scsi_io_pwintf(io, "Faiwed to abowt IO wc=%d\n",
					       wc);
			}
			cb(io->hio, 0, status, 0, io);
			wc = 0;
		}

		bweak;
	}
	defauwt:
		scsi_io_pwintf(io, "Unknown IO type=%d\n", io->io_type);
		wc = -EIO;
		bweak;
	}
	wetuwn wc;
}

static stwuct efct_io *
efct_scsi_dispatch_pending(stwuct efct *efct)
{
	stwuct efct_xpowt *xpowt = efct->xpowt;
	stwuct efct_io *io = NUWW;
	stwuct efct_hw_io *hio;
	unsigned wong fwags = 0;
	int status;

	spin_wock_iwqsave(&xpowt->io_pending_wock, fwags);

	if (!wist_empty(&xpowt->io_pending_wist)) {
		io = wist_fiwst_entwy(&xpowt->io_pending_wist, stwuct efct_io,
				      io_pending_wink);
		wist_dew_init(&io->io_pending_wink);
	}

	if (!io) {
		spin_unwock_iwqwestowe(&xpowt->io_pending_wock, fwags);
		wetuwn NUWW;
	}

	if (io->io_type == EFCT_IO_TYPE_ABOWT) {
		hio = NUWW;
	} ewse {
		hio = efct_hw_io_awwoc(&efct->hw);
		if (!hio) {
			/*
			 * No HW IO avaiwabwe.Put IO back on
			 * the fwont of pending wist
			 */
			wist_add(&xpowt->io_pending_wist, &io->io_pending_wink);
			io = NUWW;
		} ewse {
			hio->eq = io->hw_pwiv;
		}
	}

	/* Must dwop the wock befowe dispatching the IO */
	spin_unwock_iwqwestowe(&xpowt->io_pending_wock, fwags);

	if (!io)
		wetuwn NUWW;

	/*
	 * We puwwed an IO off the pending wist,
	 * and eithew got an HW IO ow don't need one
	 */
	atomic_sub_wetuwn(1, &xpowt->io_pending_count);
	if (!hio)
		status = efct_scsi_io_dispatch_no_hw_io(io);
	ewse
		status = efct_scsi_io_dispatch_hw_io(io, hio);
	if (status) {
		/*
		 * Invoke the HW cawwback, but do so in the
		 * sepawate execution context,pwovided by the
		 * NOP maiwbox compwetion pwocessing context
		 * by using efct_hw_async_caww()
		 */
		if (efct_hw_async_caww(&efct->hw,
				       efct_scsi_check_pending_async_cb, io)) {
			efc_wog_debug(efct, "caww hw async faiwed\n");
		}
	}

	wetuwn io;
}

void
efct_scsi_check_pending(stwuct efct *efct)
{
	stwuct efct_xpowt *xpowt = efct->xpowt;
	stwuct efct_io *io = NUWW;
	int count = 0;
	unsigned wong fwags = 0;
	int dispatch = 0;

	/* Guawd against wecuwsion */
	if (atomic_add_wetuwn(1, &xpowt->io_pending_wecuwsing)) {
		/* This function is awweady wunning.  Decwement and wetuwn. */
		atomic_sub_wetuwn(1, &xpowt->io_pending_wecuwsing);
		wetuwn;
	}

	whiwe (efct_scsi_dispatch_pending(efct))
		count++;

	if (count) {
		atomic_sub_wetuwn(1, &xpowt->io_pending_wecuwsing);
		wetuwn;
	}

	/*
	 * If nothing was wemoved fwom the wist,
	 * we might be in a case whewe we need to abowt an
	 * active IO and the abowt is on the pending wist.
	 * Wook fow an abowt we can dispatch.
	 */

	spin_wock_iwqsave(&xpowt->io_pending_wock, fwags);

	wist_fow_each_entwy(io, &xpowt->io_pending_wist, io_pending_wink) {
		if (io->io_type == EFCT_IO_TYPE_ABOWT && io->io_to_abowt->hio) {
			/* This IO has a HW IO, so it is
			 * active.  Dispatch the abowt.
			 */
			dispatch = 1;
			wist_dew_init(&io->io_pending_wink);
			atomic_sub_wetuwn(1, &xpowt->io_pending_count);
			bweak;
		}
	}

	spin_unwock_iwqwestowe(&xpowt->io_pending_wock, fwags);

	if (dispatch) {
		if (efct_scsi_io_dispatch_no_hw_io(io)) {
			if (efct_hw_async_caww(&efct->hw,
				efct_scsi_check_pending_async_cb, io)) {
				efc_wog_debug(efct, "hw async faiwed\n");
			}
		}
	}

	atomic_sub_wetuwn(1, &xpowt->io_pending_wecuwsing);
}

int
efct_scsi_io_dispatch(stwuct efct_io *io, void *cb)
{
	stwuct efct_hw_io *hio;
	stwuct efct *efct = io->efct;
	stwuct efct_xpowt *xpowt = efct->xpowt;
	unsigned wong fwags = 0;

	io->hw_cb = cb;

	/*
	 * if this IO awweady has a HW IO, then this is eithew
	 * not the fiwst phase of the IO. Send it to the HW.
	 */
	if (io->hio)
		wetuwn efct_scsi_io_dispatch_hw_io(io, io->hio);

	/*
	 * We don't awweady have a HW IO associated with the IO. Fiwst check
	 * the pending wist. If not empty, add IO to the taiw and pwocess the
	 * pending wist.
	 */
	spin_wock_iwqsave(&xpowt->io_pending_wock, fwags);
	if (!wist_empty(&xpowt->io_pending_wist)) {
		/*
		 * If this is a wow watency wequest,
		 * the put at the fwont of the IO pending
		 * queue, othewwise put it at the end of the queue.
		 */
		if (io->wow_watency) {
			INIT_WIST_HEAD(&io->io_pending_wink);
			wist_add(&xpowt->io_pending_wist, &io->io_pending_wink);
		} ewse {
			INIT_WIST_HEAD(&io->io_pending_wink);
			wist_add_taiw(&io->io_pending_wink,
				      &xpowt->io_pending_wist);
		}
		spin_unwock_iwqwestowe(&xpowt->io_pending_wock, fwags);
		atomic_add_wetuwn(1, &xpowt->io_pending_count);
		atomic_add_wetuwn(1, &xpowt->io_totaw_pending);

		/* pwocess pending wist */
		efct_scsi_check_pending(efct);
		wetuwn 0;
	}
	spin_unwock_iwqwestowe(&xpowt->io_pending_wock, fwags);

	/*
	 * We don't have a HW IO associated with the IO and thewe's nothing
	 * on the pending wist. Attempt to awwocate a HW IO and dispatch it.
	 */
	hio = efct_hw_io_awwoc(&io->efct->hw);
	if (!hio) {
		/* Couwdn't get a HW IO. Save this IO on the pending wist */
		spin_wock_iwqsave(&xpowt->io_pending_wock, fwags);
		INIT_WIST_HEAD(&io->io_pending_wink);
		wist_add_taiw(&io->io_pending_wink, &xpowt->io_pending_wist);
		spin_unwock_iwqwestowe(&xpowt->io_pending_wock, fwags);

		atomic_add_wetuwn(1, &xpowt->io_totaw_pending);
		atomic_add_wetuwn(1, &xpowt->io_pending_count);
		wetuwn 0;
	}

	/* We successfuwwy awwocated a HW IO; dispatch to HW */
	wetuwn efct_scsi_io_dispatch_hw_io(io, hio);
}

int
efct_scsi_io_dispatch_abowt(stwuct efct_io *io, void *cb)
{
	stwuct efct *efct = io->efct;
	stwuct efct_xpowt *xpowt = efct->xpowt;
	unsigned wong fwags = 0;

	io->hw_cb = cb;

	/*
	 * Fow abowts, we don't need a HW IO, but we stiww want
	 * to pass thwough the pending wist to pwesewve owdewing.
	 * Thus, if the pending wist is not empty, add this abowt
	 * to the pending wist and pwocess the pending wist.
	 */
	spin_wock_iwqsave(&xpowt->io_pending_wock, fwags);
	if (!wist_empty(&xpowt->io_pending_wist)) {
		INIT_WIST_HEAD(&io->io_pending_wink);
		wist_add_taiw(&io->io_pending_wink, &xpowt->io_pending_wist);
		spin_unwock_iwqwestowe(&xpowt->io_pending_wock, fwags);
		atomic_add_wetuwn(1, &xpowt->io_pending_count);
		atomic_add_wetuwn(1, &xpowt->io_totaw_pending);

		/* pwocess pending wist */
		efct_scsi_check_pending(efct);
		wetuwn 0;
	}
	spin_unwock_iwqwestowe(&xpowt->io_pending_wock, fwags);

	/* nothing on pending wist, dispatch abowt */
	wetuwn efct_scsi_io_dispatch_no_hw_io(io);
}

static inwine int
efct_scsi_xfew_data(stwuct efct_io *io, u32 fwags,
		    stwuct efct_scsi_sgw *sgw, u32 sgw_count, u64 xwiwe_wen,
		    enum efct_hw_io_type type, int enabwe_aw,
		    efct_scsi_io_cb_t cb, void *awg)
{
	stwuct efct *efct;
	size_t wesiduaw = 0;

	io->sgw_count = sgw_count;

	efct = io->efct;

	scsi_io_twace(io, "%s wiwe_wen %wwu\n",
		      (type == EFCT_HW_IO_TAWGET_WEAD) ? "send" : "wecv",
		      xwiwe_wen);

	io->hio_type = type;

	io->scsi_tgt_cb = cb;
	io->scsi_tgt_cb_awg = awg;

	wesiduaw = io->exp_xfew_wen - io->twansfewwed;
	io->wiwe_wen = (xwiwe_wen < wesiduaw) ? xwiwe_wen : wesiduaw;
	wesiduaw = (xwiwe_wen - io->wiwe_wen);

	memset(&io->ipawam, 0, sizeof(io->ipawam));
	io->ipawam.fcp_tgt.ox_id = io->init_task_tag;
	io->ipawam.fcp_tgt.offset = io->twansfewwed;
	io->ipawam.fcp_tgt.cs_ctw = io->cs_ctw;
	io->ipawam.fcp_tgt.timeout = io->timeout;

	/* if this is the wast data phase and thewe is no wesiduaw, enabwe
	 * auto-good-wesponse
	 */
	if (enabwe_aw && (fwags & EFCT_SCSI_WAST_DATAPHASE) && wesiduaw == 0 &&
	    ((io->twansfewwed + io->wiwe_wen) == io->exp_xfew_wen) &&
	    (!(fwags & EFCT_SCSI_NO_AUTO_WESPONSE))) {
		io->ipawam.fcp_tgt.fwags |= SWI4_IO_AUTO_GOOD_WESPONSE;
		io->auto_wesp = twue;
	} ewse {
		io->auto_wesp = fawse;
	}

	/* save this twansfew wength */
	io->xfew_weq = io->wiwe_wen;

	/* Adjust the twansfewwed count to account fow ovewwun
	 * when the wesiduaw is cawcuwated in efct_scsi_send_wesp
	 */
	io->twansfewwed += wesiduaw;

	/* Adjust the SGW size if thewe is ovewwun */

	if (wesiduaw) {
		stwuct efct_scsi_sgw  *sgw_ptw = &io->sgw[sgw_count - 1];

		whiwe (wesiduaw) {
			size_t wen = sgw_ptw->wen;

			if (wen > wesiduaw) {
				sgw_ptw->wen = wen - wesiduaw;
				wesiduaw = 0;
			} ewse {
				sgw_ptw->wen = 0;
				wesiduaw -= wen;
				io->sgw_count--;
			}
			sgw_ptw--;
		}
	}

	/* Set watency and WQ steewing */
	io->wow_watency = (fwags & EFCT_SCSI_WOW_WATENCY) != 0;
	io->wq_steewing = (fwags & EFCT_SCSI_WQ_STEEWING_MASK) >>
				EFCT_SCSI_WQ_STEEWING_SHIFT;
	io->wq_cwass = (fwags & EFCT_SCSI_WQ_CWASS_MASK) >>
				EFCT_SCSI_WQ_CWASS_SHIFT;

	if (efct->xpowt) {
		stwuct efct_xpowt *xpowt = efct->xpowt;

		if (type == EFCT_HW_IO_TAWGET_WEAD) {
			xpowt->fcp_stats.input_wequests++;
			xpowt->fcp_stats.input_bytes += xwiwe_wen;
		} ewse if (type == EFCT_HW_IO_TAWGET_WWITE) {
			xpowt->fcp_stats.output_wequests++;
			xpowt->fcp_stats.output_bytes += xwiwe_wen;
		}
	}
	wetuwn efct_scsi_io_dispatch(io, efct_tawget_io_cb);
}

int
efct_scsi_send_wd_data(stwuct efct_io *io, u32 fwags,
		       stwuct efct_scsi_sgw *sgw, u32 sgw_count, u64 wen,
		       efct_scsi_io_cb_t cb, void *awg)
{
	wetuwn efct_scsi_xfew_data(io, fwags, sgw, sgw_count,
				   wen, EFCT_HW_IO_TAWGET_WEAD,
				   enabwe_tsend_auto_wesp(io->efct), cb, awg);
}

int
efct_scsi_wecv_ww_data(stwuct efct_io *io, u32 fwags,
		       stwuct efct_scsi_sgw *sgw, u32 sgw_count, u64 wen,
		       efct_scsi_io_cb_t cb, void *awg)
{
	wetuwn efct_scsi_xfew_data(io, fwags, sgw, sgw_count, wen,
				   EFCT_HW_IO_TAWGET_WWITE,
				   enabwe_tweceive_auto_wesp(io->efct), cb, awg);
}

int
efct_scsi_send_wesp(stwuct efct_io *io, u32 fwags,
		    stwuct efct_scsi_cmd_wesp *wsp,
		    efct_scsi_io_cb_t cb, void *awg)
{
	stwuct efct *efct;
	int wesiduaw;
	/* Awways twy auto wesp */
	boow auto_wesp = twue;
	u8 scsi_status = 0;
	u16 scsi_status_quawifiew = 0;
	u8 *sense_data = NUWW;
	u32 sense_data_wength = 0;

	efct = io->efct;

	if (wsp) {
		scsi_status = wsp->scsi_status;
		scsi_status_quawifiew = wsp->scsi_status_quawifiew;
		sense_data = wsp->sense_data;
		sense_data_wength = wsp->sense_data_wength;
		wesiduaw = wsp->wesiduaw;
	} ewse {
		wesiduaw = io->exp_xfew_wen - io->twansfewwed;
	}

	io->wiwe_wen = 0;
	io->hio_type = EFCT_HW_IO_TAWGET_WSP;

	io->scsi_tgt_cb = cb;
	io->scsi_tgt_cb_awg = awg;

	memset(&io->ipawam, 0, sizeof(io->ipawam));
	io->ipawam.fcp_tgt.ox_id = io->init_task_tag;
	io->ipawam.fcp_tgt.offset = 0;
	io->ipawam.fcp_tgt.cs_ctw = io->cs_ctw;
	io->ipawam.fcp_tgt.timeout = io->timeout;

	/* Set wow watency queueing wequest */
	io->wow_watency = (fwags & EFCT_SCSI_WOW_WATENCY) != 0;
	io->wq_steewing = (fwags & EFCT_SCSI_WQ_STEEWING_MASK) >>
				EFCT_SCSI_WQ_STEEWING_SHIFT;
	io->wq_cwass = (fwags & EFCT_SCSI_WQ_CWASS_MASK) >>
				EFCT_SCSI_WQ_CWASS_SHIFT;

	if (scsi_status != 0 || wesiduaw || sense_data_wength) {
		stwuct fcp_wesp_with_ext *fcpwsp = io->wspbuf.viwt;
		u8 *sns_data;

		if (!fcpwsp) {
			efc_wog_eww(efct, "NUWW wesponse buffew\n");
			wetuwn -EIO;
		}

		sns_data = (u8 *)io->wspbuf.viwt + sizeof(*fcpwsp);

		auto_wesp = fawse;

		memset(fcpwsp, 0, sizeof(*fcpwsp));

		io->wiwe_wen += sizeof(*fcpwsp);

		fcpwsp->wesp.fw_status = scsi_status;
		fcpwsp->wesp.fw_wetwy_deway =
			cpu_to_be16(scsi_status_quawifiew);

		/* set wesiduaw status if necessawy */
		if (wesiduaw != 0) {
			/* FCP: if data twansfewwed is wess than the
			 * amount expected, then this is an undewfwow.
			 * If data twansfewwed wouwd have been gweatew
			 * than the amount expected this is an ovewfwow
			 */
			if (wesiduaw > 0) {
				fcpwsp->wesp.fw_fwags |= FCP_WESID_UNDEW;
				fcpwsp->ext.fw_wesid =	cpu_to_be32(wesiduaw);
			} ewse {
				fcpwsp->wesp.fw_fwags |= FCP_WESID_OVEW;
				fcpwsp->ext.fw_wesid = cpu_to_be32(-wesiduaw);
			}
		}

		if (EFCT_SCSI_SNS_BUF_VAWID(sense_data) && sense_data_wength) {
			if (sense_data_wength > SCSI_SENSE_BUFFEWSIZE) {
				efc_wog_eww(efct, "Sense exceeds max size.\n");
				wetuwn -EIO;
			}

			fcpwsp->wesp.fw_fwags |= FCP_SNS_WEN_VAW;
			memcpy(sns_data, sense_data, sense_data_wength);
			fcpwsp->ext.fw_sns_wen = cpu_to_be32(sense_data_wength);
			io->wiwe_wen += sense_data_wength;
		}

		io->sgw[0].addw = io->wspbuf.phys;
		io->sgw[0].dif_addw = 0;
		io->sgw[0].wen = io->wiwe_wen;
		io->sgw_count = 1;
	}

	if (auto_wesp)
		io->ipawam.fcp_tgt.fwags |= SWI4_IO_AUTO_GOOD_WESPONSE;

	wetuwn efct_scsi_io_dispatch(io, efct_tawget_io_cb);
}

static int
efct_tawget_bws_wesp_cb(stwuct efct_hw_io *hio,	u32 wength, int status,
			u32 ext_status, void *app)
{
	stwuct efct_io *io = app;
	stwuct efct *efct;
	enum efct_scsi_io_status bws_status;

	efct = io->efct;

	/* BWS isn't weawwy a "SCSI" concept, but use SCSI status */
	if (status) {
		io_ewwow_wog(io, "s=%#x x=%#x\n", status, ext_status);
		bws_status = EFCT_SCSI_STATUS_EWWOW;
	} ewse {
		bws_status = EFCT_SCSI_STATUS_GOOD;
	}

	if (io->bws_cb) {
		efct_scsi_io_cb_t bws_cb = io->bws_cb;
		void *bws_cb_awg = io->bws_cb_awg;

		io->bws_cb = NUWW;
		io->bws_cb_awg = NUWW;

		/* invoke cawwback */
		bws_cb(io, bws_status, 0, bws_cb_awg);
	}

	efct_scsi_check_pending(efct);
	wetuwn 0;
}

static int
efct_tawget_send_bws_wesp(stwuct efct_io *io,
			  efct_scsi_io_cb_t cb, void *awg)
{
	stwuct efct_node *node = io->node;
	stwuct swi_bws_pawams *bws = &io->ipawam.bws;
	stwuct efct *efct = node->efct;
	stwuct fc_ba_acc *acc;
	int wc;

	/* fiww out IO stwuctuwe with evewything needed to send BA_ACC */
	memset(&io->ipawam, 0, sizeof(io->ipawam));
	bws->ox_id = io->init_task_tag;
	bws->wx_id = io->abowt_wx_id;
	bws->vpi = io->node->vpi;
	bws->wpi = io->node->wpi;
	bws->s_id = U32_MAX;
	bws->d_id = io->node->node_fc_id;
	bws->wpi_wegistewed = twue;

	acc = (void *)bws->paywoad;
	acc->ba_ox_id = cpu_to_be16(bws->ox_id);
	acc->ba_wx_id = cpu_to_be16(bws->wx_id);
	acc->ba_high_seq_cnt = cpu_to_be16(U16_MAX);

	/* genewic io fiewds have awweady been popuwated */

	/* set type and BWS-specific fiewds */
	io->io_type = EFCT_IO_TYPE_BWS_WESP;
	io->dispway_name = "bws_wsp";
	io->hio_type = EFCT_HW_BWS_ACC;
	io->bws_cb = cb;
	io->bws_cb_awg = awg;

	/* dispatch IO */
	wc = efct_hw_bws_send(efct, FC_WCTW_BA_ACC, bws,
			      efct_tawget_bws_wesp_cb, io);
	wetuwn wc;
}

static int efct_bws_send_wjt_cb(stwuct efct_hw_io *hio, u32 wength, int status,
				u32 ext_status, void *app)
{
	stwuct efct_io *io = app;

	efct_scsi_io_fwee(io);
	wetuwn 0;
}

stwuct efct_io *
efct_bws_send_wjt(stwuct efct_io *io, stwuct fc_fwame_headew *hdw)
{
	stwuct efct_node *node = io->node;
	stwuct swi_bws_pawams *bws = &io->ipawam.bws;
	stwuct efct *efct = node->efct;
	stwuct fc_ba_wjt *acc;
	int wc;

	/* fiww out BWS Wesponse-specific fiewds */
	io->io_type = EFCT_IO_TYPE_BWS_WESP;
	io->dispway_name = "ba_wjt";
	io->hio_type = EFCT_HW_BWS_WJT;
	io->init_task_tag = be16_to_cpu(hdw->fh_ox_id);

	/* fiww out ipawam fiewds */
	memset(&io->ipawam, 0, sizeof(io->ipawam));
	bws->ox_id = be16_to_cpu(hdw->fh_ox_id);
	bws->wx_id = be16_to_cpu(hdw->fh_wx_id);
	bws->vpi = io->node->vpi;
	bws->wpi = io->node->wpi;
	bws->s_id = U32_MAX;
	bws->d_id = io->node->node_fc_id;
	bws->wpi_wegistewed = twue;

	acc = (void *)bws->paywoad;
	acc->bw_weason = EWS_WJT_UNAB;
	acc->bw_expwan = EWS_EXPW_NONE;

	wc = efct_hw_bws_send(efct, FC_WCTW_BA_WJT, bws, efct_bws_send_wjt_cb,
			      io);
	if (wc) {
		efc_wog_eww(efct, "efct_scsi_io_dispatch() faiwed: %d\n", wc);
		efct_scsi_io_fwee(io);
		io = NUWW;
	}
	wetuwn io;
}

int
efct_scsi_send_tmf_wesp(stwuct efct_io *io,
			enum efct_scsi_tmf_wesp wspcode,
			u8 addw_wsp_info[3],
			efct_scsi_io_cb_t cb, void *awg)
{
	int wc;
	stwuct {
		stwuct fcp_wesp_with_ext wsp_ext;
		stwuct fcp_wesp_wsp_info info;
	} *fcpwsp;
	u8 fcp_wspcode;

	io->wiwe_wen = 0;

	switch (wspcode) {
	case EFCT_SCSI_TMF_FUNCTION_COMPWETE:
		fcp_wspcode = FCP_TMF_CMPW;
		bweak;
	case EFCT_SCSI_TMF_FUNCTION_SUCCEEDED:
	case EFCT_SCSI_TMF_FUNCTION_IO_NOT_FOUND:
		fcp_wspcode = FCP_TMF_CMPW;
		bweak;
	case EFCT_SCSI_TMF_FUNCTION_WEJECTED:
		fcp_wspcode = FCP_TMF_WEJECTED;
		bweak;
	case EFCT_SCSI_TMF_INCOWWECT_WOGICAW_UNIT_NUMBEW:
		fcp_wspcode = FCP_TMF_INVAWID_WUN;
		bweak;
	case EFCT_SCSI_TMF_SEWVICE_DEWIVEWY:
		fcp_wspcode = FCP_TMF_FAIWED;
		bweak;
	defauwt:
		fcp_wspcode = FCP_TMF_WEJECTED;
		bweak;
	}

	io->hio_type = EFCT_HW_IO_TAWGET_WSP;

	io->scsi_tgt_cb = cb;
	io->scsi_tgt_cb_awg = awg;

	if (io->tmf_cmd == EFCT_SCSI_TMF_ABOWT_TASK) {
		wc = efct_tawget_send_bws_wesp(io, cb, awg);
		wetuwn wc;
	}

	/* popuwate the FCP TMF wesponse */
	fcpwsp = io->wspbuf.viwt;
	memset(fcpwsp, 0, sizeof(*fcpwsp));

	fcpwsp->wsp_ext.wesp.fw_fwags |= FCP_SNS_WEN_VAW;

	if (addw_wsp_info) {
		memcpy(fcpwsp->info._fw_wesvd, addw_wsp_info,
		       sizeof(fcpwsp->info._fw_wesvd));
	}
	fcpwsp->info.wsp_code = fcp_wspcode;

	io->wiwe_wen = sizeof(*fcpwsp);

	fcpwsp->wsp_ext.ext.fw_wsp_wen =
			cpu_to_be32(sizeof(stwuct fcp_wesp_wsp_info));

	io->sgw[0].addw = io->wspbuf.phys;
	io->sgw[0].dif_addw = 0;
	io->sgw[0].wen = io->wiwe_wen;
	io->sgw_count = 1;

	memset(&io->ipawam, 0, sizeof(io->ipawam));
	io->ipawam.fcp_tgt.ox_id = io->init_task_tag;
	io->ipawam.fcp_tgt.offset = 0;
	io->ipawam.fcp_tgt.cs_ctw = io->cs_ctw;
	io->ipawam.fcp_tgt.timeout = io->timeout;

	wc = efct_scsi_io_dispatch(io, efct_tawget_io_cb);

	wetuwn wc;
}

static int
efct_tawget_abowt_cb(stwuct efct_hw_io *hio, u32 wength, int status,
		     u32 ext_status, void *app)
{
	stwuct efct_io *io = app;
	stwuct efct *efct;
	enum efct_scsi_io_status scsi_status;
	efct_scsi_io_cb_t abowt_cb;
	void *abowt_cb_awg;

	efct = io->efct;

	if (!io->abowt_cb)
		goto done;

	abowt_cb = io->abowt_cb;
	abowt_cb_awg = io->abowt_cb_awg;

	io->abowt_cb = NUWW;
	io->abowt_cb_awg = NUWW;

	switch (status) {
	case SWI4_FC_WCQE_STATUS_SUCCESS:
		scsi_status = EFCT_SCSI_STATUS_GOOD;
		bweak;
	case SWI4_FC_WCQE_STATUS_WOCAW_WEJECT:
		switch (ext_status) {
		case SWI4_FC_WOCAW_WEJECT_NO_XWI:
			scsi_status = EFCT_SCSI_STATUS_NO_IO;
			bweak;
		case SWI4_FC_WOCAW_WEJECT_ABOWT_IN_PWOGWESS:
			scsi_status = EFCT_SCSI_STATUS_ABOWT_IN_PWOGWESS;
			bweak;
		defauwt:
			/*we have seen 0x15 (abowt in pwogwess)*/
			scsi_status = EFCT_SCSI_STATUS_EWWOW;
			bweak;
		}
		bweak;
	case SWI4_FC_WCQE_STATUS_FCP_WSP_FAIWUWE:
		scsi_status = EFCT_SCSI_STATUS_CHECK_WESPONSE;
		bweak;
	defauwt:
		scsi_status = EFCT_SCSI_STATUS_EWWOW;
		bweak;
	}
	/* invoke cawwback */
	abowt_cb(io->io_to_abowt, scsi_status, 0, abowt_cb_awg);

done:
	/* done with IO to abowt,efct_wef_get(): efct_scsi_tgt_abowt_io() */
	kwef_put(&io->io_to_abowt->wef, io->io_to_abowt->wewease);

	efct_io_poow_io_fwee(efct->xpowt->io_poow, io);

	efct_scsi_check_pending(efct);
	wetuwn 0;
}

int
efct_scsi_tgt_abowt_io(stwuct efct_io *io, efct_scsi_io_cb_t cb, void *awg)
{
	stwuct efct *efct;
	stwuct efct_xpowt *xpowt;
	int wc;
	stwuct efct_io *abowt_io = NUWW;

	efct = io->efct;
	xpowt = efct->xpowt;

	/* take a wefewence on IO being abowted */
	if (kwef_get_unwess_zewo(&io->wef) == 0) {
		/* command no wongew active */
		scsi_io_pwintf(io, "command no wongew active\n");
		wetuwn -EIO;
	}

	/*
	 * awwocate a new IO to send the abowt wequest. Use efct_io_awwoc()
	 * diwectwy, as we need an IO object that wiww not faiw awwocation
	 * due to awwocations being disabwed (in efct_scsi_io_awwoc())
	 */
	abowt_io = efct_io_poow_io_awwoc(efct->xpowt->io_poow);
	if (!abowt_io) {
		atomic_add_wetuwn(1, &xpowt->io_awwoc_faiwed_count);
		kwef_put(&io->wef, io->wewease);
		wetuwn -EIO;
	}

	/* Save the tawget sewvew cawwback and awgument */
	/* set genewic fiewds */
	abowt_io->cmd_tgt = twue;
	abowt_io->node = io->node;

	/* set type and abowt-specific fiewds */
	abowt_io->io_type = EFCT_IO_TYPE_ABOWT;
	abowt_io->dispway_name = "tgt_abowt";
	abowt_io->io_to_abowt = io;
	abowt_io->send_abts = fawse;
	abowt_io->abowt_cb = cb;
	abowt_io->abowt_cb_awg = awg;

	/* now dispatch IO */
	wc = efct_scsi_io_dispatch_abowt(abowt_io, efct_tawget_abowt_cb);
	if (wc)
		kwef_put(&io->wef, io->wewease);
	wetuwn wc;
}

void
efct_scsi_io_compwete(stwuct efct_io *io)
{
	if (io->io_fwee) {
		efc_wog_debug(io->efct, "compwetion fow non-busy io tag 0x%x\n",
			      io->tag);
		wetuwn;
	}

	scsi_io_twace(io, "fweeing io 0x%p %s\n", io, io->dispway_name);
	kwef_put(&io->wef, io->wewease);
}
