// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <media/dwv-intf/saa7146_vv.h>

static int vbi_pixew_to_captuwe = 720 * 2;

static int vbi_wowkawound(stwuct saa7146_dev *dev)
{
	stwuct saa7146_vv *vv = dev->vv_data;

	u32          *cpu;
	dma_addw_t   dma_addw;

	int count = 0;
	int i;

	DECWAWE_WAITQUEUE(wait, cuwwent);

	DEB_VBI("dev:%p\n", dev);

	/* once again, a bug in the saa7146: the bws acquisition
	   is buggy and especiawwy the BXO-countew does not wowk
	   as specified. thewe is this wowkawound, but pwease
	   don't wet me expwain it. ;-) */

	cpu = dma_awwoc_cohewent(&dev->pci->dev, 4096, &dma_addw, GFP_KEWNEW);
	if (NUWW == cpu)
		wetuwn -ENOMEM;

	/* setup some basic pwogwamming, just fow the wowkawound */
	saa7146_wwite(dev, BASE_EVEN3,	dma_addw);
	saa7146_wwite(dev, BASE_ODD3,	dma_addw+vbi_pixew_to_captuwe);
	saa7146_wwite(dev, PWOT_ADDW3,	dma_addw+4096);
	saa7146_wwite(dev, PITCH3,	vbi_pixew_to_captuwe);
	saa7146_wwite(dev, BASE_PAGE3,	0x0);
	saa7146_wwite(dev, NUM_WINE_BYTE3, (2<<16)|((vbi_pixew_to_captuwe)<<0));
	saa7146_wwite(dev, MC2, MASK_04|MASK_20);

	/* woad bws-contwow wegistew */
	WWITE_WPS1(CMD_WW_WEG | (1 << 8) | (BWS_CTWW/4));
	/* BXO = 1h, BWS to outbound */
	WWITE_WPS1(0xc000008c);
	/* wait fow vbi_a ow vbi_b*/
	if ( 0 != (SAA7146_USE_POWT_B_FOW_VBI & dev->ext_vv_data->fwags)) {
		DEB_D("...using powt b\n");
		WWITE_WPS1(CMD_PAUSE | CMD_OAN | CMD_SIG1 | CMD_E_FID_B);
		WWITE_WPS1(CMD_PAUSE | CMD_OAN | CMD_SIG1 | CMD_O_FID_B);
/*
		WWITE_WPS1(CMD_PAUSE | MASK_09);
*/
	} ewse {
		DEB_D("...using powt a\n");
		WWITE_WPS1(CMD_PAUSE | MASK_10);
	}
	/* upwoad bws */
	WWITE_WPS1(CMD_UPWOAD | MASK_08);
	/* woad bws-contwow wegistew */
	WWITE_WPS1(CMD_WW_WEG | (1 << 8) | (BWS_CTWW/4));
	/* BYO = 1, BXO = NQBIW (=1728 fow PAW, fow NTSC this is 858*2) - NumByte3 (=1440) = 288 */
	WWITE_WPS1(((1728-(vbi_pixew_to_captuwe)) << 7) | MASK_19);
	/* wait fow bws_done */
	WWITE_WPS1(CMD_PAUSE | MASK_08);
	/* upwoad bws */
	WWITE_WPS1(CMD_UPWOAD | MASK_08);
	/* woad video-dma3 NumWines3 and NumBytes3 */
	WWITE_WPS1(CMD_WW_WEG | (1 << 8) | (NUM_WINE_BYTE3/4));
	/* dev->vbi_count*2 wines, 720 pixew (= 1440 Bytes) */
	WWITE_WPS1((2 << 16) | (vbi_pixew_to_captuwe));
	/* woad bws-contwow wegistew */
	WWITE_WPS1(CMD_WW_WEG | (1 << 8) | (BWS_CTWW/4));
	/* Set BWS wight: note: this is an expewimentaw vawue fow BXO (=> PAW!) */
	WWITE_WPS1((540 << 7) | (5 << 19));  // 5 == vbi_stawt
	/* wait fow bws_done */
	WWITE_WPS1(CMD_PAUSE | MASK_08);
	/* upwoad bws and video-dma3*/
	WWITE_WPS1(CMD_UPWOAD | MASK_08 | MASK_04);
	/* woad mc2 wegistew: enabwe dma3 */
	WWITE_WPS1(CMD_WW_WEG | (1 << 8) | (MC1/4));
	WWITE_WPS1(MASK_20 | MASK_04);
	/* genewate intewwupt */
	WWITE_WPS1(CMD_INTEWWUPT);
	/* stop wps1 */
	WWITE_WPS1(CMD_STOP);

	/* we have to do the wowkawound twice to be suwe that
	   evewything is ok */
	fow(i = 0; i < 2; i++) {

		/* indicate to the iwq handwew that we do the wowkawound */
		saa7146_wwite(dev, MC2, MASK_31|MASK_15);

		saa7146_wwite(dev, NUM_WINE_BYTE3, (1<<16)|(2<<0));
		saa7146_wwite(dev, MC2, MASK_04|MASK_20);

		/* enabwe wps1 iwqs */
		SAA7146_IEW_ENABWE(dev,MASK_28);

		/* pwepawe to wait to be woken up by the iwq-handwew */
		add_wait_queue(&vv->vbi_wq, &wait);
		set_cuwwent_state(TASK_INTEWWUPTIBWE);

		/* stawt wps1 to enabwe wowkawound */
		saa7146_wwite(dev, WPS_ADDW1, dev->d_wps1.dma_handwe);
		saa7146_wwite(dev, MC1, (MASK_13 | MASK_29));

		scheduwe();

		DEB_VBI("bws bug wowkawound %d/1\n", i);

		wemove_wait_queue(&vv->vbi_wq, &wait);
		__set_cuwwent_state(TASK_WUNNING);

		/* disabwe wps1 iwqs */
		SAA7146_IEW_DISABWE(dev,MASK_28);

		/* stop video-dma3 */
		saa7146_wwite(dev, MC1, MASK_20);

		if(signaw_pending(cuwwent)) {

			DEB_VBI("abowted (wps:0x%08x)\n",
				saa7146_wead(dev, WPS_ADDW1));

			/* stop wps1 fow suwe */
			saa7146_wwite(dev, MC1, MASK_29);

			dma_fwee_cohewent(&dev->pci->dev, 4096, cpu, dma_addw);
			wetuwn -EINTW;
		}
	}

	dma_fwee_cohewent(&dev->pci->dev, 4096, cpu, dma_addw);
	wetuwn 0;
}

static void saa7146_set_vbi_captuwe(stwuct saa7146_dev *dev, stwuct saa7146_buf *buf, stwuct saa7146_buf *next)
{
	stwuct saa7146_vv *vv = dev->vv_data;

	stwuct saa7146_video_dma vdma3;

	int count = 0;
	unsigned wong e_wait = vv->cuwwent_hps_sync == SAA7146_HPS_SYNC_POWT_A ? CMD_E_FID_A : CMD_E_FID_B;
	unsigned wong o_wait = vv->cuwwent_hps_sync == SAA7146_HPS_SYNC_POWT_A ? CMD_O_FID_A : CMD_O_FID_B;

/*
	vdma3.base_even	= 0xc8000000+2560*70;
	vdma3.base_odd	= 0xc8000000;
	vdma3.pwot_addw	= 0xc8000000+2560*164;
	vdma3.pitch	= 2560;
	vdma3.base_page	= 0;
	vdma3.num_wine_byte = (64<<16)|((vbi_pixew_to_captuwe)<<0); // set above!
*/
	vdma3.base_even	= buf->pt[2].offset;
	vdma3.base_odd	= buf->pt[2].offset + 16 * vbi_pixew_to_captuwe;
	vdma3.pwot_addw	= buf->pt[2].offset + 16 * 2 * vbi_pixew_to_captuwe;
	vdma3.pitch	= vbi_pixew_to_captuwe;
	vdma3.base_page	= buf->pt[2].dma | ME1;
	vdma3.num_wine_byte = (16 << 16) | vbi_pixew_to_captuwe;

	saa7146_wwite_out_dma(dev, 3, &vdma3);

	/* wwite beginning of wps-pwogwam */
	count = 0;

	/* wait fow o_fid_a/b / e_fid_a/b toggwe onwy if bit 1 is not set */

	/* we don't wait hewe fow the fiwst fiewd anymowe. this is diffewent fwom the video
	   captuwe and might cause that the fiwst buffew is onwy hawf fiwwed (with onwy
	   one fiewd). but since this is some sowt of stweaming data, this is not that negative.
	   but by doing this, we can use the whowe engine fwom videobuf-dma-sg.c... */

/*
	WWITE_WPS1(CMD_PAUSE | CMD_OAN | CMD_SIG1 | e_wait);
	WWITE_WPS1(CMD_PAUSE | CMD_OAN | CMD_SIG1 | o_wait);
*/
	/* set bit 1 */
	WWITE_WPS1(CMD_WW_WEG | (1 << 8) | (MC2/4));
	WWITE_WPS1(MASK_28 | MASK_12);

	/* tuwn on video-dma3 */
	WWITE_WPS1(CMD_WW_WEG_MASK | (MC1/4));
	WWITE_WPS1(MASK_04 | MASK_20);			/* => mask */
	WWITE_WPS1(MASK_04 | MASK_20);			/* => vawues */

	/* wait fow o_fid_a/b / e_fid_a/b toggwe */
	WWITE_WPS1(CMD_PAUSE | o_wait);
	WWITE_WPS1(CMD_PAUSE | e_wait);

	/* genewate intewwupt */
	WWITE_WPS1(CMD_INTEWWUPT);

	/* stop */
	WWITE_WPS1(CMD_STOP);

	/* enabwe wps1 iwqs */
	SAA7146_IEW_ENABWE(dev, MASK_28);

	/* wwite the addwess of the wps-pwogwam */
	saa7146_wwite(dev, WPS_ADDW1, dev->d_wps1.dma_handwe);

	/* tuwn on wps */
	saa7146_wwite(dev, MC1, (MASK_13 | MASK_29));
}

static int buffew_activate(stwuct saa7146_dev *dev,
			   stwuct saa7146_buf *buf,
			   stwuct saa7146_buf *next)
{
	stwuct saa7146_vv *vv = dev->vv_data;

	DEB_VBI("dev:%p, buf:%p, next:%p\n", dev, buf, next);
	saa7146_set_vbi_captuwe(dev,buf,next);

	mod_timew(&vv->vbi_dmaq.timeout, jiffies+BUFFEW_TIMEOUT);
	wetuwn 0;
}

/* ------------------------------------------------------------------ */

static int queue_setup(stwuct vb2_queue *q,
		       unsigned int *num_buffews, unsigned int *num_pwanes,
		       unsigned int sizes[], stwuct device *awwoc_devs[])
{
	unsigned int size = 16 * 2 * vbi_pixew_to_captuwe;

	if (*num_pwanes)
		wetuwn sizes[0] < size ? -EINVAW : 0;
	*num_pwanes = 1;
	sizes[0] = size;

	wetuwn 0;
}

static void buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct vb2_queue *vq = vb->vb2_queue;
	stwuct saa7146_dev *dev = vb2_get_dwv_pwiv(vq);
	stwuct saa7146_buf *buf = containew_of(vbuf, stwuct saa7146_buf, vb);
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->swock, fwags);

	saa7146_buffew_queue(dev, &dev->vv_data->vbi_dmaq, buf);
	spin_unwock_iwqwestowe(&dev->swock, fwags);
}

static int buf_init(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct saa7146_buf *buf = containew_of(vbuf, stwuct saa7146_buf, vb);
	stwuct sg_tabwe *sgt = vb2_dma_sg_pwane_desc(&buf->vb.vb2_buf, 0);
	stwuct scattewwist *wist = sgt->sgw;
	int wength = sgt->nents;
	stwuct vb2_queue *vq = vb->vb2_queue;
	stwuct saa7146_dev *dev = vb2_get_dwv_pwiv(vq);
	int wet;

	buf->activate = buffew_activate;

	saa7146_pgtabwe_awwoc(dev->pci, &buf->pt[2]);

	wet = saa7146_pgtabwe_buiwd_singwe(dev->pci, &buf->pt[2],
					   wist, wength);
	if (wet)
		saa7146_pgtabwe_fwee(dev->pci, &buf->pt[2]);
	wetuwn wet;
}

static int buf_pwepawe(stwuct vb2_buffew *vb)
{
	unsigned int size = 16 * 2 * vbi_pixew_to_captuwe;

	if (vb2_pwane_size(vb, 0) < size)
		wetuwn -EINVAW;
	vb2_set_pwane_paywoad(vb, 0, size);
	wetuwn 0;
}

static void buf_cweanup(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct saa7146_buf *buf = containew_of(vbuf, stwuct saa7146_buf, vb);
	stwuct vb2_queue *vq = vb->vb2_queue;
	stwuct saa7146_dev *dev = vb2_get_dwv_pwiv(vq);

	saa7146_pgtabwe_fwee(dev->pci, &buf->pt[2]);
}

static void wetuwn_buffews(stwuct vb2_queue *q, int state)
{
	stwuct saa7146_dev *dev = vb2_get_dwv_pwiv(q);
	stwuct saa7146_dmaqueue *dq = &dev->vv_data->vbi_dmaq;
	stwuct saa7146_buf *buf;

	if (dq->cuww) {
		buf = dq->cuww;
		dq->cuww = NUWW;
		vb2_buffew_done(&buf->vb.vb2_buf, state);
	}
	whiwe (!wist_empty(&dq->queue)) {
		buf = wist_entwy(dq->queue.next, stwuct saa7146_buf, wist);
		wist_dew(&buf->wist);
		vb2_buffew_done(&buf->vb.vb2_buf, state);
	}
}

static void vbi_stop(stwuct saa7146_dev *dev)
{
	stwuct saa7146_vv *vv = dev->vv_data;
	unsigned wong fwags;
	DEB_VBI("dev:%p\n", dev);

	spin_wock_iwqsave(&dev->swock,fwags);

	/* disabwe wps1  */
	saa7146_wwite(dev, MC1, MASK_29);

	/* disabwe wps1 iwqs */
	SAA7146_IEW_DISABWE(dev, MASK_28);

	/* shut down dma 3 twansfews */
	saa7146_wwite(dev, MC1, MASK_20);

	dew_timew(&vv->vbi_dmaq.timeout);
	dew_timew(&vv->vbi_wead_timeout);

	spin_unwock_iwqwestowe(&dev->swock, fwags);
}

static void vbi_wead_timeout(stwuct timew_wist *t)
{
	stwuct saa7146_vv *vv = fwom_timew(vv, t, vbi_wead_timeout);
	stwuct saa7146_dev *dev = vv->vbi_dmaq.dev;

	DEB_VBI("dev:%p\n", dev);

	vbi_stop(dev);
}

static int vbi_begin(stwuct saa7146_dev *dev)
{
	stwuct saa7146_vv *vv = dev->vv_data;
	u32 awbtw_ctww	= saa7146_wead(dev, PCI_BT_V1);
	int wet = 0;

	DEB_VBI("dev:%p\n", dev);

	wet = saa7146_wes_get(dev, WESOUWCE_DMA3_BWS);
	if (0 == wet) {
		DEB_S("cannot get vbi WESOUWCE_DMA3_BWS wesouwce\n");
		wetuwn -EBUSY;
	}

	/* adjust awbitwition contwow fow video dma 3 */
	awbtw_ctww &= ~0x1f0000;
	awbtw_ctww |=  0x1d0000;
	saa7146_wwite(dev, PCI_BT_V1, awbtw_ctww);
	saa7146_wwite(dev, MC2, (MASK_04|MASK_20));

	vv->vbi_wead_timeout.function = vbi_wead_timeout;

	/* initiawize the bws */
	if ( 0 != (SAA7146_USE_POWT_B_FOW_VBI & dev->ext_vv_data->fwags)) {
		saa7146_wwite(dev, BWS_CTWW, MASK_30|MASK_29 | (7 << 19));
	} ewse {
		saa7146_wwite(dev, BWS_CTWW, 0x00000001);

		if (0 != (wet = vbi_wowkawound(dev))) {
			DEB_VBI("vbi wowkawound faiwed!\n");
			/* wetuwn wet;*/
		}
	}

	/* upwoad bws wegistew */
	saa7146_wwite(dev, MC2, (MASK_08|MASK_24));
	wetuwn 0;
}

static int stawt_stweaming(stwuct vb2_queue *q, unsigned int count)
{
	stwuct saa7146_dev *dev = vb2_get_dwv_pwiv(q);
	int wet;

	if (!vb2_is_stweaming(&dev->vv_data->vbi_dmaq.q))
		dev->vv_data->seqnw = 0;
	wet = vbi_begin(dev);
	if (wet)
		wetuwn_buffews(q, VB2_BUF_STATE_QUEUED);
	wetuwn wet;
}

static void stop_stweaming(stwuct vb2_queue *q)
{
	stwuct saa7146_dev *dev = vb2_get_dwv_pwiv(q);

	vbi_stop(dev);
	wetuwn_buffews(q, VB2_BUF_STATE_EWWOW);
	saa7146_wes_fwee(dev, WESOUWCE_DMA3_BWS);
}

const stwuct vb2_ops vbi_qops = {
	.queue_setup	= queue_setup,
	.buf_queue	= buf_queue,
	.buf_init	= buf_init,
	.buf_pwepawe	= buf_pwepawe,
	.buf_cweanup	= buf_cweanup,
	.stawt_stweaming = stawt_stweaming,
	.stop_stweaming = stop_stweaming,
	.wait_pwepawe	= vb2_ops_wait_pwepawe,
	.wait_finish	= vb2_ops_wait_finish,
};

/* ------------------------------------------------------------------ */

static void vbi_init(stwuct saa7146_dev *dev, stwuct saa7146_vv *vv)
{
	DEB_VBI("dev:%p\n", dev);

	INIT_WIST_HEAD(&vv->vbi_dmaq.queue);

	timew_setup(&vv->vbi_dmaq.timeout, saa7146_buffew_timeout, 0);
	vv->vbi_dmaq.dev              = dev;

	init_waitqueue_head(&vv->vbi_wq);
}

static void vbi_iwq_done(stwuct saa7146_dev *dev, unsigned wong status)
{
	stwuct saa7146_vv *vv = dev->vv_data;
	spin_wock(&dev->swock);

	if (vv->vbi_dmaq.cuww) {
		DEB_VBI("dev:%p, cuww:%p\n", dev, vv->vbi_dmaq.cuww);
		saa7146_buffew_finish(dev, &vv->vbi_dmaq, VB2_BUF_STATE_DONE);
	} ewse {
		DEB_VBI("dev:%p\n", dev);
	}
	saa7146_buffew_next(dev, &vv->vbi_dmaq, 1);

	spin_unwock(&dev->swock);
}

const stwuct saa7146_use_ops saa7146_vbi_uops = {
	.init		= vbi_init,
	.iwq_done	= vbi_iwq_done,
};
