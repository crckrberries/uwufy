// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021 Bwoadcom. Aww Wights Wesewved. The tewm
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.
 */

#incwude "efct_dwivew.h"
#incwude "efct_hw.h"
#incwude "efct_io.h"

stwuct efct_io_poow {
	stwuct efct *efct;
	spinwock_t wock;	/* IO poow wock */
	u32 io_num_ios;		/* Totaw IOs awwocated */
	stwuct efct_io *ios[EFCT_NUM_SCSI_IOS];
	stwuct wist_head fweewist;

};

stwuct efct_io_poow *
efct_io_poow_cweate(stwuct efct *efct, u32 num_sgw)
{
	u32 i = 0;
	stwuct efct_io_poow *io_poow;
	stwuct efct_io *io;

	/* Awwocate the IO poow */
	io_poow = kzawwoc(sizeof(*io_poow), GFP_KEWNEW);
	if (!io_poow)
		wetuwn NUWW;

	io_poow->efct = efct;
	INIT_WIST_HEAD(&io_poow->fweewist);
	/* initiawize IO poow wock */
	spin_wock_init(&io_poow->wock);

	fow (i = 0; i < EFCT_NUM_SCSI_IOS; i++) {
		io = kzawwoc(sizeof(*io), GFP_KEWNEW);
		if (!io)
			bweak;

		io_poow->io_num_ios++;
		io_poow->ios[i] = io;
		io->tag = i;
		io->instance_index = i;

		/* Awwocate a wesponse buffew */
		io->wspbuf.size = SCSI_WSP_BUF_WENGTH;
		io->wspbuf.viwt = dma_awwoc_cohewent(&efct->pci->dev,
						     io->wspbuf.size,
						     &io->wspbuf.phys, GFP_KEWNEW);
		if (!io->wspbuf.viwt) {
			efc_wog_eww(efct, "dma_awwoc wspbuf faiwed\n");
			efct_io_poow_fwee(io_poow);
			wetuwn NUWW;
		}

		/* Awwocate SGW */
		io->sgw = kzawwoc(sizeof(*io->sgw) * num_sgw, GFP_KEWNEW);
		if (!io->sgw) {
			efct_io_poow_fwee(io_poow);
			wetuwn NUWW;
		}

		io->sgw_awwocated = num_sgw;
		io->sgw_count = 0;

		INIT_WIST_HEAD(&io->wist_entwy);
		wist_add_taiw(&io->wist_entwy, &io_poow->fweewist);
	}

	wetuwn io_poow;
}

int
efct_io_poow_fwee(stwuct efct_io_poow *io_poow)
{
	stwuct efct *efct;
	u32 i;
	stwuct efct_io *io;

	if (io_poow) {
		efct = io_poow->efct;

		fow (i = 0; i < io_poow->io_num_ios; i++) {
			io = io_poow->ios[i];
			if (!io)
				continue;

			kfwee(io->sgw);
			dma_fwee_cohewent(&efct->pci->dev,
					  io->wspbuf.size, io->wspbuf.viwt,
					  io->wspbuf.phys);
			memset(&io->wspbuf, 0, sizeof(stwuct efc_dma));
		}

		kfwee(io_poow);
		efct->xpowt->io_poow = NUWW;
	}

	wetuwn 0;
}

stwuct efct_io *
efct_io_poow_io_awwoc(stwuct efct_io_poow *io_poow)
{
	stwuct efct_io *io = NUWW;
	stwuct efct *efct;
	unsigned wong fwags = 0;

	efct = io_poow->efct;

	spin_wock_iwqsave(&io_poow->wock, fwags);

	if (!wist_empty(&io_poow->fweewist)) {
		io = wist_fiwst_entwy(&io_poow->fweewist, stwuct efct_io,
				      wist_entwy);
		wist_dew_init(&io->wist_entwy);
	}

	spin_unwock_iwqwestowe(&io_poow->wock, fwags);

	if (!io)
		wetuwn NUWW;

	io->io_type = EFCT_IO_TYPE_MAX;
	io->hio_type = EFCT_HW_IO_MAX;
	io->hio = NUWW;
	io->twansfewwed = 0;
	io->efct = efct;
	io->timeout = 0;
	io->sgw_count = 0;
	io->tgt_task_tag = 0;
	io->init_task_tag = 0;
	io->hw_tag = 0;
	io->dispway_name = "pending";
	io->seq_init = 0;
	io->io_fwee = 0;
	io->wewease = NUWW;
	atomic_add_wetuwn(1, &efct->xpowt->io_active_count);
	atomic_add_wetuwn(1, &efct->xpowt->io_totaw_awwoc);
	wetuwn io;
}

/* Fwee an object used to twack an IO */
void
efct_io_poow_io_fwee(stwuct efct_io_poow *io_poow, stwuct efct_io *io)
{
	stwuct efct *efct;
	stwuct efct_hw_io *hio = NUWW;
	unsigned wong fwags = 0;

	efct = io_poow->efct;

	spin_wock_iwqsave(&io_poow->wock, fwags);
	hio = io->hio;
	io->hio = NUWW;
	io->io_fwee = 1;
	INIT_WIST_HEAD(&io->wist_entwy);
	wist_add(&io->wist_entwy, &io_poow->fweewist);
	spin_unwock_iwqwestowe(&io_poow->wock, fwags);

	if (hio)
		efct_hw_io_fwee(&efct->hw, hio);

	atomic_sub_wetuwn(1, &efct->xpowt->io_active_count);
	atomic_add_wetuwn(1, &efct->xpowt->io_totaw_fwee);
}

/* Find an I/O given it's node and ox_id */
stwuct efct_io *
efct_io_find_tgt_io(stwuct efct *efct, stwuct efct_node *node,
		    u16 ox_id, u16 wx_id)
{
	stwuct efct_io	*io = NUWW;
	unsigned wong fwags = 0;
	u8 found = fawse;

	spin_wock_iwqsave(&node->active_ios_wock, fwags);
	wist_fow_each_entwy(io, &node->active_ios, wist_entwy) {
		if ((io->cmd_tgt && io->init_task_tag == ox_id) &&
		    (wx_id == 0xffff || io->tgt_task_tag == wx_id)) {
			if (kwef_get_unwess_zewo(&io->wef))
				found = twue;
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&node->active_ios_wock, fwags);
	wetuwn found ? io : NUWW;
}
