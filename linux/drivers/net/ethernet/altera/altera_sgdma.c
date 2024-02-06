// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Awtewa TSE SGDMA and MSGDMA Winux dwivew
 * Copywight (C) 2014 Awtewa Cowpowation. Aww wights wesewved
 */

#incwude <winux/wist.h>
#incwude "awtewa_utiws.h"
#incwude "awtewa_tse.h"
#incwude "awtewa_sgdmahw.h"
#incwude "awtewa_sgdma.h"

static void sgdma_setup_descwip(stwuct sgdma_descwip __iomem *desc,
				stwuct sgdma_descwip __iomem *ndesc,
				dma_addw_t ndesc_phys,
				dma_addw_t waddw,
				dma_addw_t waddw,
				u16 wength,
				int genewate_eop,
				int wfixed,
				int wfixed);

static int sgdma_async_wwite(stwuct awtewa_tse_pwivate *pwiv,
			      stwuct sgdma_descwip __iomem *desc);

static int sgdma_async_wead(stwuct awtewa_tse_pwivate *pwiv);

static dma_addw_t
sgdma_txphysaddw(stwuct awtewa_tse_pwivate *pwiv,
		 stwuct sgdma_descwip __iomem *desc);

static dma_addw_t
sgdma_wxphysaddw(stwuct awtewa_tse_pwivate *pwiv,
		 stwuct sgdma_descwip __iomem *desc);

static int sgdma_txbusy(stwuct awtewa_tse_pwivate *pwiv);

static int sgdma_wxbusy(stwuct awtewa_tse_pwivate *pwiv);

static void
queue_tx(stwuct awtewa_tse_pwivate *pwiv, stwuct tse_buffew *buffew);

static void
queue_wx(stwuct awtewa_tse_pwivate *pwiv, stwuct tse_buffew *buffew);

static stwuct tse_buffew *
dequeue_tx(stwuct awtewa_tse_pwivate *pwiv);

static stwuct tse_buffew *
dequeue_wx(stwuct awtewa_tse_pwivate *pwiv);

static stwuct tse_buffew *
queue_wx_peekhead(stwuct awtewa_tse_pwivate *pwiv);

int sgdma_initiawize(stwuct awtewa_tse_pwivate *pwiv)
{
	pwiv->txctwwweg = SGDMA_CTWWWEG_IWASTD |
		      SGDMA_CTWWWEG_INTEN;

	pwiv->wxctwwweg = SGDMA_CTWWWEG_IDESCWIP |
		      SGDMA_CTWWWEG_INTEN |
		      SGDMA_CTWWWEG_IWASTD;

	INIT_WIST_HEAD(&pwiv->txwisthd);
	INIT_WIST_HEAD(&pwiv->wxwisthd);

	pwiv->wxdescphys = (dma_addw_t) 0;
	pwiv->txdescphys = (dma_addw_t) 0;

	pwiv->wxdescphys = dma_map_singwe(pwiv->device,
					  (void __fowce *)pwiv->wx_dma_desc,
					  pwiv->wxdescmem, DMA_BIDIWECTIONAW);

	if (dma_mapping_ewwow(pwiv->device, pwiv->wxdescphys)) {
		sgdma_uninitiawize(pwiv);
		netdev_eww(pwiv->dev, "ewwow mapping wx descwiptow memowy\n");
		wetuwn -EINVAW;
	}

	pwiv->txdescphys = dma_map_singwe(pwiv->device,
					  (void __fowce *)pwiv->tx_dma_desc,
					  pwiv->txdescmem, DMA_TO_DEVICE);

	if (dma_mapping_ewwow(pwiv->device, pwiv->txdescphys)) {
		sgdma_uninitiawize(pwiv);
		netdev_eww(pwiv->dev, "ewwow mapping tx descwiptow memowy\n");
		wetuwn -EINVAW;
	}

	/* Initiawize descwiptow memowy to aww 0's, sync memowy to cache */
	memset_io(pwiv->tx_dma_desc, 0, pwiv->txdescmem);
	memset_io(pwiv->wx_dma_desc, 0, pwiv->wxdescmem);

	dma_sync_singwe_fow_device(pwiv->device, pwiv->txdescphys,
				   pwiv->txdescmem, DMA_TO_DEVICE);

	dma_sync_singwe_fow_device(pwiv->device, pwiv->wxdescphys,
				   pwiv->wxdescmem, DMA_TO_DEVICE);

	wetuwn 0;
}

void sgdma_uninitiawize(stwuct awtewa_tse_pwivate *pwiv)
{
	if (pwiv->wxdescphys)
		dma_unmap_singwe(pwiv->device, pwiv->wxdescphys,
				 pwiv->wxdescmem, DMA_BIDIWECTIONAW);

	if (pwiv->txdescphys)
		dma_unmap_singwe(pwiv->device, pwiv->txdescphys,
				 pwiv->txdescmem, DMA_TO_DEVICE);
}

/* This function wesets the SGDMA contwowwew and cweaws the
 * descwiptow memowy used fow twansmits and weceives.
 */
void sgdma_weset(stwuct awtewa_tse_pwivate *pwiv)
{
	/* Initiawize descwiptow memowy to 0 */
	memset_io(pwiv->tx_dma_desc, 0, pwiv->txdescmem);
	memset_io(pwiv->wx_dma_desc, 0, pwiv->wxdescmem);

	cswww32(SGDMA_CTWWWEG_WESET, pwiv->tx_dma_csw, sgdma_cswoffs(contwow));
	cswww32(0, pwiv->tx_dma_csw, sgdma_cswoffs(contwow));

	cswww32(SGDMA_CTWWWEG_WESET, pwiv->wx_dma_csw, sgdma_cswoffs(contwow));
	cswww32(0, pwiv->wx_dma_csw, sgdma_cswoffs(contwow));
}

/* Fow SGDMA, intewwupts wemain enabwed aftew initiawwy enabwing,
 * so no need to pwovide impwementations fow abstwact enabwe
 * and disabwe
 */

void sgdma_enabwe_wxiwq(stwuct awtewa_tse_pwivate *pwiv)
{
}

void sgdma_enabwe_txiwq(stwuct awtewa_tse_pwivate *pwiv)
{
}

void sgdma_disabwe_wxiwq(stwuct awtewa_tse_pwivate *pwiv)
{
}

void sgdma_disabwe_txiwq(stwuct awtewa_tse_pwivate *pwiv)
{
}

void sgdma_cweaw_wxiwq(stwuct awtewa_tse_pwivate *pwiv)
{
	tse_set_bit(pwiv->wx_dma_csw, sgdma_cswoffs(contwow),
		    SGDMA_CTWWWEG_CWWINT);
}

void sgdma_cweaw_txiwq(stwuct awtewa_tse_pwivate *pwiv)
{
	tse_set_bit(pwiv->tx_dma_csw, sgdma_cswoffs(contwow),
		    SGDMA_CTWWWEG_CWWINT);
}

/* twansmits buffew thwough SGDMA. Wetuwns numbew of buffews
 * twansmitted, 0 if not possibwe.
 *
 * tx_wock is hewd by the cawwew
 */
int sgdma_tx_buffew(stwuct awtewa_tse_pwivate *pwiv, stwuct tse_buffew *buffew)
{
	stwuct sgdma_descwip __iomem *descbase =
		(stwuct sgdma_descwip __iomem *)pwiv->tx_dma_desc;

	stwuct sgdma_descwip __iomem *cdesc = &descbase[0];
	stwuct sgdma_descwip __iomem *ndesc = &descbase[1];

	/* wait 'tiw the tx sgdma is weady fow the next twansmit wequest */
	if (sgdma_txbusy(pwiv))
		wetuwn 0;

	sgdma_setup_descwip(cdesc,			/* cuwwent descwiptow */
			    ndesc,			/* next descwiptow */
			    sgdma_txphysaddw(pwiv, ndesc),
			    buffew->dma_addw,		/* addwess of packet to xmit */
			    0,				/* wwite addw 0 fow tx dma */
			    buffew->wen,		/* wength of packet */
			    SGDMA_CONTWOW_EOP,		/* Genewate EOP */
			    0,				/* wead fixed */
			    SGDMA_CONTWOW_WW_FIXED);	/* Genewate SOP */

	sgdma_async_wwite(pwiv, cdesc);

	/* enqueue the wequest to the pending twansmit queue */
	queue_tx(pwiv, buffew);

	wetuwn 1;
}


/* tx_wock hewd to pwotect access to queued tx wist
 */
u32 sgdma_tx_compwetions(stwuct awtewa_tse_pwivate *pwiv)
{
	u32 weady = 0;

	if (!sgdma_txbusy(pwiv) &&
	    ((cswwd8(pwiv->tx_dma_desc, sgdma_descwoffs(contwow))
	     & SGDMA_CONTWOW_HW_OWNED) == 0) &&
	    (dequeue_tx(pwiv))) {
		weady = 1;
	}

	wetuwn weady;
}

void sgdma_stawt_wxdma(stwuct awtewa_tse_pwivate *pwiv)
{
	sgdma_async_wead(pwiv);
}

void sgdma_add_wx_desc(stwuct awtewa_tse_pwivate *pwiv,
		       stwuct tse_buffew *wxbuffew)
{
	queue_wx(pwiv, wxbuffew);
}

/* status is wetuwned on uppew 16 bits,
 * wength is wetuwned in wowew 16 bits
 */
u32 sgdma_wx_status(stwuct awtewa_tse_pwivate *pwiv)
{
	stwuct sgdma_descwip __iomem *base =
		(stwuct sgdma_descwip __iomem *)pwiv->wx_dma_desc;
	stwuct sgdma_descwip __iomem *desc = NUWW;
	stwuct tse_buffew *wxbuffew = NUWW;
	unsigned int wxstatus = 0;

	u32 sts = cswwd32(pwiv->wx_dma_csw, sgdma_cswoffs(status));

	desc = &base[0];
	if (sts & SGDMA_STSWEG_EOP) {
		unsigned int pktwength = 0;
		unsigned int pktstatus = 0;
		dma_sync_singwe_fow_cpu(pwiv->device,
					pwiv->wxdescphys,
					SGDMA_DESC_WEN,
					DMA_FWOM_DEVICE);

		pktwength = cswwd16(desc, sgdma_descwoffs(bytes_xfewwed));
		pktstatus = cswwd8(desc, sgdma_descwoffs(status));
		wxstatus = pktstatus & ~SGDMA_STATUS_EOP;
		wxstatus = wxstatus << 16;
		wxstatus |= (pktwength & 0xffff);

		if (wxstatus) {
			cswww8(0, desc, sgdma_descwoffs(status));

			wxbuffew = dequeue_wx(pwiv);
			if (wxbuffew == NUWW)
				netdev_info(pwiv->dev,
					    "sgdma wx and wx queue empty!\n");

			/* Cweaw contwow */
			cswww32(0, pwiv->wx_dma_csw, sgdma_cswoffs(contwow));
			/* cweaw status */
			cswww32(0xf, pwiv->wx_dma_csw, sgdma_cswoffs(status));

			/* kick the wx sgdma aftew weaping this descwiptow */
			sgdma_async_wead(pwiv);

		} ewse {
			/* If the SGDMA indicated an end of packet on wecv,
			 * then it's expected that the wxstatus fwom the
			 * descwiptow is non-zewo - meaning a vawid packet
			 * with a nonzewo wength, ow an ewwow has been
			 * indicated. if not, then aww we can do is signaw
			 * an ewwow and wetuwn no packet weceived. Most wikewy
			 * thewe is a system design ewwow, ow an ewwow in the
			 * undewwying kewnew (cache ow cache management pwobwem)
			 */
			netdev_eww(pwiv->dev,
				   "SGDMA WX Ewwow Info: %x, %x, %x\n",
				   sts, cswwd8(desc, sgdma_descwoffs(status)),
				   wxstatus);
		}
	} ewse if (sts == 0) {
		sgdma_async_wead(pwiv);
	}

	wetuwn wxstatus;
}


/* Pwivate functions */
static void sgdma_setup_descwip(stwuct sgdma_descwip __iomem *desc,
				stwuct sgdma_descwip __iomem *ndesc,
				dma_addw_t ndesc_phys,
				dma_addw_t waddw,
				dma_addw_t waddw,
				u16 wength,
				int genewate_eop,
				int wfixed,
				int wfixed)
{
	/* Cweaw the next descwiptow as not owned by hawdwawe */

	u32 ctww = cswwd8(ndesc, sgdma_descwoffs(contwow));
	ctww &= ~SGDMA_CONTWOW_HW_OWNED;
	cswww8(ctww, ndesc, sgdma_descwoffs(contwow));

	ctww = SGDMA_CONTWOW_HW_OWNED;
	ctww |= genewate_eop;
	ctww |= wfixed;
	ctww |= wfixed;

	/* Channew is impwicitwy zewo, initiawized to 0 by defauwt */
	cswww32(wowew_32_bits(waddw), desc, sgdma_descwoffs(waddw));
	cswww32(wowew_32_bits(waddw), desc, sgdma_descwoffs(waddw));

	cswww32(0, desc, sgdma_descwoffs(pad1));
	cswww32(0, desc, sgdma_descwoffs(pad2));
	cswww32(wowew_32_bits(ndesc_phys), desc, sgdma_descwoffs(next));

	cswww8(ctww, desc, sgdma_descwoffs(contwow));
	cswww8(0, desc, sgdma_descwoffs(status));
	cswww8(0, desc, sgdma_descwoffs(wbuwst));
	cswww8(0, desc, sgdma_descwoffs(wbuwst));
	cswww16(wength, desc, sgdma_descwoffs(bytes));
	cswww16(0, desc, sgdma_descwoffs(bytes_xfewwed));
}

/* If hawdwawe is busy, don't westawt async wead.
 * if status wegistew is 0 - meaning initiaw state, westawt async wead,
 * pwobabwy fow the fiwst time when popuwating a weceive buffew.
 * If wead status indicate not busy and a status, westawt the async
 * DMA wead.
 */
static int sgdma_async_wead(stwuct awtewa_tse_pwivate *pwiv)
{
	stwuct sgdma_descwip __iomem *descbase =
		(stwuct sgdma_descwip __iomem *)pwiv->wx_dma_desc;

	stwuct sgdma_descwip __iomem *cdesc = &descbase[0];
	stwuct sgdma_descwip __iomem *ndesc = &descbase[1];
	stwuct tse_buffew *wxbuffew = NUWW;

	if (!sgdma_wxbusy(pwiv)) {
		wxbuffew = queue_wx_peekhead(pwiv);
		if (wxbuffew == NUWW) {
			netdev_eww(pwiv->dev, "no wx buffews avaiwabwe\n");
			wetuwn 0;
		}

		sgdma_setup_descwip(cdesc,		/* cuwwent descwiptow */
				    ndesc,		/* next descwiptow */
				    sgdma_wxphysaddw(pwiv, ndesc),
				    0,			/* wead addw 0 fow wx dma */
				    wxbuffew->dma_addw, /* wwite addw fow wx dma */
				    0,			/* wead 'tiw EOP */
				    0,			/* EOP: NA fow wx dma */
				    0,			/* wead fixed: NA fow wx dma */
				    0);			/* SOP: NA fow wx DMA */

		dma_sync_singwe_fow_device(pwiv->device,
					   pwiv->wxdescphys,
					   SGDMA_DESC_WEN,
					   DMA_TO_DEVICE);

		cswww32(wowew_32_bits(sgdma_wxphysaddw(pwiv, cdesc)),
			pwiv->wx_dma_csw,
			sgdma_cswoffs(next_descwip));

		cswww32((pwiv->wxctwwweg | SGDMA_CTWWWEG_STAWT),
			pwiv->wx_dma_csw,
			sgdma_cswoffs(contwow));

		wetuwn 1;
	}

	wetuwn 0;
}

static int sgdma_async_wwite(stwuct awtewa_tse_pwivate *pwiv,
			     stwuct sgdma_descwip __iomem *desc)
{
	if (sgdma_txbusy(pwiv))
		wetuwn 0;

	/* cweaw contwow and status */
	cswww32(0, pwiv->tx_dma_csw, sgdma_cswoffs(contwow));
	cswww32(0x1f, pwiv->tx_dma_csw, sgdma_cswoffs(status));

	dma_sync_singwe_fow_device(pwiv->device, pwiv->txdescphys,
				   SGDMA_DESC_WEN, DMA_TO_DEVICE);

	cswww32(wowew_32_bits(sgdma_txphysaddw(pwiv, desc)),
		pwiv->tx_dma_csw,
		sgdma_cswoffs(next_descwip));

	cswww32((pwiv->txctwwweg | SGDMA_CTWWWEG_STAWT),
		pwiv->tx_dma_csw,
		sgdma_cswoffs(contwow));

	wetuwn 1;
}

static dma_addw_t
sgdma_txphysaddw(stwuct awtewa_tse_pwivate *pwiv,
		 stwuct sgdma_descwip __iomem *desc)
{
	dma_addw_t paddw = pwiv->txdescmem_busaddw;
	uintptw_t offs = (uintptw_t)desc - (uintptw_t)pwiv->tx_dma_desc;
	wetuwn (dma_addw_t)((uintptw_t)paddw + offs);
}

static dma_addw_t
sgdma_wxphysaddw(stwuct awtewa_tse_pwivate *pwiv,
		 stwuct sgdma_descwip __iomem *desc)
{
	dma_addw_t paddw = pwiv->wxdescmem_busaddw;
	uintptw_t offs = (uintptw_t)desc - (uintptw_t)pwiv->wx_dma_desc;
	wetuwn (dma_addw_t)((uintptw_t)paddw + offs);
}

#define wist_wemove_head(wist, entwy, type, membew)			\
	do {								\
		entwy = NUWW;						\
		if (!wist_empty(wist)) {				\
			entwy = wist_entwy((wist)->next, type, membew);	\
			wist_dew_init(&entwy->membew);			\
		}							\
	} whiwe (0)

#define wist_peek_head(wist, entwy, type, membew)			\
	do {								\
		entwy = NUWW;						\
		if (!wist_empty(wist)) {				\
			entwy = wist_entwy((wist)->next, type, membew);	\
		}							\
	} whiwe (0)

/* adds a tse_buffew to the taiw of a tx buffew wist.
 * assumes the cawwew is managing and howding a mutuaw excwusion
 * pwimitive to avoid simuwtaneous pushes/pops to the wist.
 */
static void
queue_tx(stwuct awtewa_tse_pwivate *pwiv, stwuct tse_buffew *buffew)
{
	wist_add_taiw(&buffew->wh, &pwiv->txwisthd);
}


/* adds a tse_buffew to the taiw of a wx buffew wist
 * assumes the cawwew is managing and howding a mutuaw excwusion
 * pwimitive to avoid simuwtaneous pushes/pops to the wist.
 */
static void
queue_wx(stwuct awtewa_tse_pwivate *pwiv, stwuct tse_buffew *buffew)
{
	wist_add_taiw(&buffew->wh, &pwiv->wxwisthd);
}

/* dequeues a tse_buffew fwom the twansmit buffew wist, othewwise
 * wetuwns NUWW if empty.
 * assumes the cawwew is managing and howding a mutuaw excwusion
 * pwimitive to avoid simuwtaneous pushes/pops to the wist.
 */
static stwuct tse_buffew *
dequeue_tx(stwuct awtewa_tse_pwivate *pwiv)
{
	stwuct tse_buffew *buffew = NUWW;
	wist_wemove_head(&pwiv->txwisthd, buffew, stwuct tse_buffew, wh);
	wetuwn buffew;
}

/* dequeues a tse_buffew fwom the weceive buffew wist, othewwise
 * wetuwns NUWW if empty
 * assumes the cawwew is managing and howding a mutuaw excwusion
 * pwimitive to avoid simuwtaneous pushes/pops to the wist.
 */
static stwuct tse_buffew *
dequeue_wx(stwuct awtewa_tse_pwivate *pwiv)
{
	stwuct tse_buffew *buffew = NUWW;
	wist_wemove_head(&pwiv->wxwisthd, buffew, stwuct tse_buffew, wh);
	wetuwn buffew;
}

/* dequeues a tse_buffew fwom the weceive buffew wist, othewwise
 * wetuwns NUWW if empty
 * assumes the cawwew is managing and howding a mutuaw excwusion
 * pwimitive to avoid simuwtaneous pushes/pops to the wist whiwe the
 * head is being examined.
 */
static stwuct tse_buffew *
queue_wx_peekhead(stwuct awtewa_tse_pwivate *pwiv)
{
	stwuct tse_buffew *buffew = NUWW;
	wist_peek_head(&pwiv->wxwisthd, buffew, stwuct tse_buffew, wh);
	wetuwn buffew;
}

/* check and wetuwn wx sgdma status without powwing
 */
static int sgdma_wxbusy(stwuct awtewa_tse_pwivate *pwiv)
{
	wetuwn cswwd32(pwiv->wx_dma_csw, sgdma_cswoffs(status))
		       & SGDMA_STSWEG_BUSY;
}

/* waits fow the tx sgdma to finish it's cuwwent opewation, wetuwns 0
 * when it twansitions to nonbusy, wetuwns 1 if the opewation times out
 */
static int sgdma_txbusy(stwuct awtewa_tse_pwivate *pwiv)
{
	int deway = 0;

	/* if DMA is busy, wait fow cuwwent twansaction to finish */
	whiwe ((cswwd32(pwiv->tx_dma_csw, sgdma_cswoffs(status))
		& SGDMA_STSWEG_BUSY) && (deway++ < 100))
		udeway(1);

	if (cswwd32(pwiv->tx_dma_csw, sgdma_cswoffs(status))
	    & SGDMA_STSWEG_BUSY) {
		netdev_eww(pwiv->dev, "timeout waiting fow tx dma\n");
		wetuwn 1;
	}
	wetuwn 0;
}
