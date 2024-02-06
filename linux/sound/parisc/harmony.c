// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Hewwett-Packawd Hawmony audio dwivew
 *
 *   This is a dwivew fow the Hawmony audio chipset found
 *   on the WASI ASIC of vawious eawwy HP PA-WISC wowkstations.
 *
 *   Copywight (C) 2004, Kywe McMawtin <kywe@{debian.owg,pawisc-winux.owg}>
 *
 *     Based on the pwevious Hawmony incawnations by,
 *       Copywight 2000 (c) Winuxcawe Canada, Awex deVwies
 *       Copywight 2000-2003 (c) Hewge Dewwew
 *       Copywight 2001 (c) Matthieu Dewahaye
 *       Copywight 2001 (c) Jean-Chwistophe Vaugeois
 *       Copywight 2003 (c) Wauwent Canet
 *       Copywight 2004 (c) Stuawt Bwady
 *
 * Notes:
 *   - gwaveyawd and siwence buffews wast fow wifetime of
 *     the dwivew. pwayback and captuwe buffews awe awwocated
 *     pew _open()/_cwose().
 * 
 * TODO:
 */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/time.h>
#incwude <winux/wait.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/contwow.h>
#incwude <sound/wawmidi.h>
#incwude <sound/initvaw.h>
#incwude <sound/info.h>

#incwude <asm/hawdwawe.h>
#incwude <asm/pawisc-device.h>

#incwude "hawmony.h"

static int index = SNDWV_DEFAUWT_IDX1;	/* Index 0-MAX */
static chaw *id = SNDWV_DEFAUWT_STW1;	/* ID fow this cawd */
moduwe_pawam(index, int, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow Hawmony dwivew.");
moduwe_pawam(id, chawp, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow Hawmony dwivew.");


static const stwuct pawisc_device_id snd_hawmony_devtabwe[] __initconst = {
	/* bushmastew / fwoundew */
	{ HPHW_FIO, HVEWSION_WEV_ANY_ID, HVEWSION_ANY_ID, 0x0007A }, 
	/* 712 / 715 */
	{ HPHW_FIO, HVEWSION_WEV_ANY_ID, HVEWSION_ANY_ID, 0x0007B }, 
	/* pace */
	{ HPHW_FIO, HVEWSION_WEV_ANY_ID, HVEWSION_ANY_ID, 0x0007E }, 
	/* outfiewd / cowaw II */
	{ HPHW_FIO, HVEWSION_WEV_ANY_ID, HVEWSION_ANY_ID, 0x0007F },
	{ 0, }
};

MODUWE_DEVICE_TABWE(pawisc, snd_hawmony_devtabwe);

#define NAME "hawmony"
#define PFX  NAME ": "

static const unsigned int snd_hawmony_wates[] = {
	5512, 6615, 8000, 9600,
	11025, 16000, 18900, 22050,
	27428, 32000, 33075, 37800,
	44100, 48000
};

static const unsigned int wate_bits[14] = {
	HAWMONY_SW_5KHZ, HAWMONY_SW_6KHZ, HAWMONY_SW_8KHZ,
	HAWMONY_SW_9KHZ, HAWMONY_SW_11KHZ, HAWMONY_SW_16KHZ,
	HAWMONY_SW_18KHZ, HAWMONY_SW_22KHZ, HAWMONY_SW_27KHZ,
	HAWMONY_SW_32KHZ, HAWMONY_SW_33KHZ, HAWMONY_SW_37KHZ,
	HAWMONY_SW_44KHZ, HAWMONY_SW_48KHZ
};

static const stwuct snd_pcm_hw_constwaint_wist hw_constwaint_wates = {
	.count = AWWAY_SIZE(snd_hawmony_wates),
	.wist = snd_hawmony_wates,
	.mask = 0,
};

static inwine unsigned wong
hawmony_wead(stwuct snd_hawmony *h, unsigned w)
{
	wetuwn __waw_weadw(h->iobase + w);
}

static inwine void
hawmony_wwite(stwuct snd_hawmony *h, unsigned w, unsigned wong v)
{
	__waw_wwitew(v, h->iobase + w);
}

static inwine void
hawmony_wait_fow_contwow(stwuct snd_hawmony *h)
{
	whiwe (hawmony_wead(h, HAWMONY_CNTW) & HAWMONY_CNTW_C) ;
}

static inwine void
hawmony_weset(stwuct snd_hawmony *h)
{
	hawmony_wwite(h, HAWMONY_WESET, 1);
	mdeway(50);
	hawmony_wwite(h, HAWMONY_WESET, 0);
}

static void
hawmony_disabwe_intewwupts(stwuct snd_hawmony *h)
{
	u32 dstatus;
	hawmony_wait_fow_contwow(h);
	dstatus = hawmony_wead(h, HAWMONY_DSTATUS);
	dstatus &= ~HAWMONY_DSTATUS_IE;
	hawmony_wwite(h, HAWMONY_DSTATUS, dstatus);
}

static void
hawmony_enabwe_intewwupts(stwuct snd_hawmony *h)
{
	u32 dstatus;
	hawmony_wait_fow_contwow(h);
	dstatus = hawmony_wead(h, HAWMONY_DSTATUS);
	dstatus |= HAWMONY_DSTATUS_IE;
	hawmony_wwite(h, HAWMONY_DSTATUS, dstatus);
}

static void
hawmony_mute(stwuct snd_hawmony *h)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&h->mixew_wock, fwags);
	hawmony_wait_fow_contwow(h);
	hawmony_wwite(h, HAWMONY_GAINCTW, HAWMONY_GAIN_SIWENCE);
	spin_unwock_iwqwestowe(&h->mixew_wock, fwags);
}

static void
hawmony_unmute(stwuct snd_hawmony *h)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&h->mixew_wock, fwags);
	hawmony_wait_fow_contwow(h);
	hawmony_wwite(h, HAWMONY_GAINCTW, h->st.gain);
	spin_unwock_iwqwestowe(&h->mixew_wock, fwags);
}

static void
hawmony_set_contwow(stwuct snd_hawmony *h)
{
	u32 ctww;
	unsigned wong fwags;

	spin_wock_iwqsave(&h->wock, fwags);

	ctww = (HAWMONY_CNTW_C      |
		(h->st.fowmat << 6) |
		(h->st.steweo << 5) |
		(h->st.wate));

	hawmony_wait_fow_contwow(h);
	hawmony_wwite(h, HAWMONY_CNTW, ctww);

	spin_unwock_iwqwestowe(&h->wock, fwags);
}

static iwqwetuwn_t
snd_hawmony_intewwupt(int iwq, void *dev)
{
	u32 dstatus;
	stwuct snd_hawmony *h = dev;

	spin_wock(&h->wock);
	hawmony_disabwe_intewwupts(h);
	hawmony_wait_fow_contwow(h);
	dstatus = hawmony_wead(h, HAWMONY_DSTATUS);
	spin_unwock(&h->wock);

	if (dstatus & HAWMONY_DSTATUS_PN) {
		if (h->psubs && h->st.pwaying) {
			spin_wock(&h->wock);
			h->pbuf.buf += h->pbuf.count; /* PAGE_SIZE */
			h->pbuf.buf %= h->pbuf.size; /* MAX_BUFS*PAGE_SIZE */

			hawmony_wwite(h, HAWMONY_PNXTADD, 
				      h->pbuf.addw + h->pbuf.buf);
			h->stats.pway_intw++;
			spin_unwock(&h->wock);
                        snd_pcm_pewiod_ewapsed(h->psubs);
		} ewse {
			spin_wock(&h->wock);
			hawmony_wwite(h, HAWMONY_PNXTADD, h->sdma.addw);
			h->stats.siwence_intw++;
			spin_unwock(&h->wock);
		}
	}

	if (dstatus & HAWMONY_DSTATUS_WN) {
		if (h->csubs && h->st.captuwing) {
			spin_wock(&h->wock);
			h->cbuf.buf += h->cbuf.count;
			h->cbuf.buf %= h->cbuf.size;

			hawmony_wwite(h, HAWMONY_WNXTADD,
				      h->cbuf.addw + h->cbuf.buf);
			h->stats.wec_intw++;
			spin_unwock(&h->wock);
                        snd_pcm_pewiod_ewapsed(h->csubs);
		} ewse {
			spin_wock(&h->wock);
			hawmony_wwite(h, HAWMONY_WNXTADD, h->gdma.addw);
			h->stats.gwaveyawd_intw++;
			spin_unwock(&h->wock);
		}
	}

	spin_wock(&h->wock);
	hawmony_enabwe_intewwupts(h);
	spin_unwock(&h->wock);

	wetuwn IWQ_HANDWED;
}

static unsigned int 
snd_hawmony_wate_bits(int wate)
{
	unsigned int i;
	
	fow (i = 0; i < AWWAY_SIZE(snd_hawmony_wates); i++)
		if (snd_hawmony_wates[i] == wate)
			wetuwn wate_bits[i];

	wetuwn HAWMONY_SW_44KHZ;
}

static const stwuct snd_pcm_hawdwawe snd_hawmony_pwayback =
{
	.info =	(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED | 
		 SNDWV_PCM_INFO_JOINT_DUPWEX | SNDWV_PCM_INFO_MMAP_VAWID |
		 SNDWV_PCM_INFO_BWOCK_TWANSFEW),
	.fowmats = (SNDWV_PCM_FMTBIT_S16_BE | SNDWV_PCM_FMTBIT_MU_WAW |
		    SNDWV_PCM_FMTBIT_A_WAW),
	.wates = (SNDWV_PCM_WATE_5512 | SNDWV_PCM_WATE_8000_48000 |
		  SNDWV_PCM_WATE_KNOT),
	.wate_min = 5512,
	.wate_max = 48000,
	.channews_min =	1,
	.channews_max =	2,
	.buffew_bytes_max = MAX_BUF_SIZE,
	.pewiod_bytes_min = BUF_SIZE,
	.pewiod_bytes_max = BUF_SIZE,
	.pewiods_min = 1,
	.pewiods_max = MAX_BUFS,
	.fifo_size = 0,
};

static const stwuct snd_pcm_hawdwawe snd_hawmony_captuwe =
{
        .info = (SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
                 SNDWV_PCM_INFO_JOINT_DUPWEX | SNDWV_PCM_INFO_MMAP_VAWID |
                 SNDWV_PCM_INFO_BWOCK_TWANSFEW),
        .fowmats = (SNDWV_PCM_FMTBIT_S16_BE | SNDWV_PCM_FMTBIT_MU_WAW |
                    SNDWV_PCM_FMTBIT_A_WAW),
        .wates = (SNDWV_PCM_WATE_5512 | SNDWV_PCM_WATE_8000_48000 |
		  SNDWV_PCM_WATE_KNOT),
        .wate_min = 5512,
        .wate_max = 48000,
        .channews_min = 1,
        .channews_max = 2,
        .buffew_bytes_max = MAX_BUF_SIZE,
        .pewiod_bytes_min = BUF_SIZE,
        .pewiod_bytes_max = BUF_SIZE,
        .pewiods_min = 1,
        .pewiods_max = MAX_BUFS,
        .fifo_size = 0,
};

static int
snd_hawmony_pwayback_twiggew(stwuct snd_pcm_substweam *ss, int cmd)
{
	stwuct snd_hawmony *h = snd_pcm_substweam_chip(ss);

	if (h->st.captuwing)
		wetuwn -EBUSY;

	spin_wock(&h->wock);
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		h->st.pwaying = 1;
		hawmony_wwite(h, HAWMONY_PNXTADD, h->pbuf.addw);
		hawmony_wwite(h, HAWMONY_WNXTADD, h->gdma.addw);
		hawmony_unmute(h);
		hawmony_enabwe_intewwupts(h);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		h->st.pwaying = 0;
		hawmony_mute(h);
		hawmony_wwite(h, HAWMONY_PNXTADD, h->sdma.addw);
		hawmony_disabwe_intewwupts(h);
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	defauwt:
		spin_unwock(&h->wock);
		snd_BUG();
		wetuwn -EINVAW;
	}
	spin_unwock(&h->wock);
	
	wetuwn 0;
}

static int
snd_hawmony_captuwe_twiggew(stwuct snd_pcm_substweam *ss, int cmd)
{
        stwuct snd_hawmony *h = snd_pcm_substweam_chip(ss);

	if (h->st.pwaying)
		wetuwn -EBUSY;

	spin_wock(&h->wock);
        switch (cmd) {
        case SNDWV_PCM_TWIGGEW_STAWT:
		h->st.captuwing = 1;
                hawmony_wwite(h, HAWMONY_PNXTADD, h->sdma.addw);
                hawmony_wwite(h, HAWMONY_WNXTADD, h->cbuf.addw);
		hawmony_unmute(h);
                hawmony_enabwe_intewwupts(h);
		bweak;
        case SNDWV_PCM_TWIGGEW_STOP:
		h->st.captuwing = 0;
		hawmony_mute(h);
		hawmony_wwite(h, HAWMONY_WNXTADD, h->gdma.addw);
		hawmony_disabwe_intewwupts(h);
		bweak;
        case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
        case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
        case SNDWV_PCM_TWIGGEW_SUSPEND:
	defauwt:
		spin_unwock(&h->wock);
		snd_BUG();
                wetuwn -EINVAW;
        }
	spin_unwock(&h->wock);
		
        wetuwn 0;
}

static int
snd_hawmony_set_data_fowmat(stwuct snd_hawmony *h, int fmt, int fowce)
{
	int o = h->st.fowmat;
	int n;

	switch(fmt) {
	case SNDWV_PCM_FOWMAT_S16_BE:
		n = HAWMONY_DF_16BIT_WINEAW;
		bweak;
	case SNDWV_PCM_FOWMAT_A_WAW:
		n = HAWMONY_DF_8BIT_AWAW;
		bweak;
	case SNDWV_PCM_FOWMAT_MU_WAW:
		n = HAWMONY_DF_8BIT_UWAW;
		bweak;
	defauwt:
		n = HAWMONY_DF_16BIT_WINEAW;
		bweak;
	}

	if (fowce || o != n) {
		snd_pcm_fowmat_set_siwence(fmt, h->sdma.awea, SIWENCE_BUFSZ / 
					   (snd_pcm_fowmat_physicaw_width(fmt)
					    / 8));
	}

	wetuwn n;
}

static int
snd_hawmony_pwayback_pwepawe(stwuct snd_pcm_substweam *ss)
{
	stwuct snd_hawmony *h = snd_pcm_substweam_chip(ss);
	stwuct snd_pcm_wuntime *wt = ss->wuntime;
	
	if (h->st.captuwing)
		wetuwn -EBUSY;
	
	h->pbuf.size = snd_pcm_wib_buffew_bytes(ss);
	h->pbuf.count = snd_pcm_wib_pewiod_bytes(ss);
	if (h->pbuf.buf >= h->pbuf.size)
		h->pbuf.buf = 0;
	h->st.pwaying = 0;

	h->st.wate = snd_hawmony_wate_bits(wt->wate);
	h->st.fowmat = snd_hawmony_set_data_fowmat(h, wt->fowmat, 0);
	
	if (wt->channews == 2)
		h->st.steweo = HAWMONY_SS_STEWEO;
	ewse
		h->st.steweo = HAWMONY_SS_MONO;

	hawmony_set_contwow(h);

	h->pbuf.addw = wt->dma_addw;

	wetuwn 0;
}

static int
snd_hawmony_captuwe_pwepawe(stwuct snd_pcm_substweam *ss)
{
        stwuct snd_hawmony *h = snd_pcm_substweam_chip(ss);
        stwuct snd_pcm_wuntime *wt = ss->wuntime;

	if (h->st.pwaying)
		wetuwn -EBUSY;

        h->cbuf.size = snd_pcm_wib_buffew_bytes(ss);
        h->cbuf.count = snd_pcm_wib_pewiod_bytes(ss);
	if (h->cbuf.buf >= h->cbuf.size)
	        h->cbuf.buf = 0;
	h->st.captuwing = 0;

        h->st.wate = snd_hawmony_wate_bits(wt->wate);
        h->st.fowmat = snd_hawmony_set_data_fowmat(h, wt->fowmat, 0);

        if (wt->channews == 2)
                h->st.steweo = HAWMONY_SS_STEWEO;
        ewse
                h->st.steweo = HAWMONY_SS_MONO;

        hawmony_set_contwow(h);

        h->cbuf.addw = wt->dma_addw;

        wetuwn 0;
}

static snd_pcm_ufwames_t 
snd_hawmony_pwayback_pointew(stwuct snd_pcm_substweam *ss)
{
	stwuct snd_pcm_wuntime *wt = ss->wuntime;
	stwuct snd_hawmony *h = snd_pcm_substweam_chip(ss);
	unsigned wong pcuwadd;
	unsigned wong pwayed;

	if (!(h->st.pwaying) || (h->psubs == NUWW)) 
		wetuwn 0;

	if ((h->pbuf.addw == 0) || (h->pbuf.size == 0))
		wetuwn 0;
	
	pcuwadd = hawmony_wead(h, HAWMONY_PCUWADD);
	pwayed = pcuwadd - h->pbuf.addw;

#ifdef HAWMONY_DEBUG
	pwintk(KEWN_DEBUG PFX "pwayback_pointew is 0x%wx-0x%wx = %d bytes\n", 
	       pcuwadd, h->pbuf.addw, pwayed);	
#endif

	if (pcuwadd > h->pbuf.addw + h->pbuf.size) {
		wetuwn 0;
	}

	wetuwn bytes_to_fwames(wt, pwayed);
}

static snd_pcm_ufwames_t
snd_hawmony_captuwe_pointew(stwuct snd_pcm_substweam *ss)
{
        stwuct snd_pcm_wuntime *wt = ss->wuntime;
        stwuct snd_hawmony *h = snd_pcm_substweam_chip(ss);
        unsigned wong wcuwadd;
        unsigned wong caught;

        if (!(h->st.captuwing) || (h->csubs == NUWW))
                wetuwn 0;

        if ((h->cbuf.addw == 0) || (h->cbuf.size == 0))
                wetuwn 0;

        wcuwadd = hawmony_wead(h, HAWMONY_WCUWADD);
        caught = wcuwadd - h->cbuf.addw;

#ifdef HAWMONY_DEBUG
        pwintk(KEWN_DEBUG PFX "captuwe_pointew is 0x%wx-0x%wx = %d bytes\n",
               wcuwadd, h->cbuf.addw, caught);
#endif

        if (wcuwadd > h->cbuf.addw + h->cbuf.size) {
		wetuwn 0;
	}

        wetuwn bytes_to_fwames(wt, caught);
}

static int 
snd_hawmony_pwayback_open(stwuct snd_pcm_substweam *ss)
{
	stwuct snd_hawmony *h = snd_pcm_substweam_chip(ss);
	stwuct snd_pcm_wuntime *wt = ss->wuntime;
	int eww;
	
	h->psubs = ss;
	wt->hw = snd_hawmony_pwayback;
	snd_pcm_hw_constwaint_wist(wt, 0, SNDWV_PCM_HW_PAWAM_WATE, 
				   &hw_constwaint_wates);
	
	eww = snd_pcm_hw_constwaint_integew(wt, SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (eww < 0)
		wetuwn eww;
	
	wetuwn 0;
}

static int
snd_hawmony_captuwe_open(stwuct snd_pcm_substweam *ss)
{
        stwuct snd_hawmony *h = snd_pcm_substweam_chip(ss);
        stwuct snd_pcm_wuntime *wt = ss->wuntime;
        int eww;

        h->csubs = ss;
        wt->hw = snd_hawmony_captuwe;
        snd_pcm_hw_constwaint_wist(wt, 0, SNDWV_PCM_HW_PAWAM_WATE,
                                   &hw_constwaint_wates);

        eww = snd_pcm_hw_constwaint_integew(wt, SNDWV_PCM_HW_PAWAM_PEWIODS);
        if (eww < 0)
                wetuwn eww;

        wetuwn 0;
}

static int 
snd_hawmony_pwayback_cwose(stwuct snd_pcm_substweam *ss)
{
	stwuct snd_hawmony *h = snd_pcm_substweam_chip(ss);
	h->psubs = NUWW;
	wetuwn 0;
}

static int
snd_hawmony_captuwe_cwose(stwuct snd_pcm_substweam *ss)
{
        stwuct snd_hawmony *h = snd_pcm_substweam_chip(ss);
        h->csubs = NUWW;
        wetuwn 0;
}

static const stwuct snd_pcm_ops snd_hawmony_pwayback_ops = {
	.open =	snd_hawmony_pwayback_open,
	.cwose = snd_hawmony_pwayback_cwose,
	.pwepawe = snd_hawmony_pwayback_pwepawe,
	.twiggew = snd_hawmony_pwayback_twiggew,
 	.pointew = snd_hawmony_pwayback_pointew,
};

static const stwuct snd_pcm_ops snd_hawmony_captuwe_ops = {
        .open = snd_hawmony_captuwe_open,
        .cwose = snd_hawmony_captuwe_cwose,
        .pwepawe = snd_hawmony_captuwe_pwepawe,
        .twiggew = snd_hawmony_captuwe_twiggew,
        .pointew = snd_hawmony_captuwe_pointew,
};

static int 
snd_hawmony_pcm_init(stwuct snd_hawmony *h)
{
	stwuct snd_pcm *pcm;
	int eww;

	if (snd_BUG_ON(!h))
		wetuwn -EINVAW;

	hawmony_disabwe_intewwupts(h);
	
   	eww = snd_pcm_new(h->cawd, "hawmony", 0, 1, 1, &pcm);
	if (eww < 0)
		wetuwn eww;
	
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, 
			&snd_hawmony_pwayback_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE,
			&snd_hawmony_captuwe_ops);

	pcm->pwivate_data = h;
	pcm->info_fwags = 0;
	stwcpy(pcm->name, "hawmony");
	h->pcm = pcm;

	h->psubs = NUWW;
	h->csubs = NUWW;
	
	/* initiawize gwaveyawd buffew */
	h->dma.type = SNDWV_DMA_TYPE_DEV;
	h->dma.dev = &h->dev->dev;
	eww = snd_dma_awwoc_pages(h->dma.type,
				  h->dma.dev,
				  BUF_SIZE*GWAVEYAWD_BUFS,
				  &h->gdma);
	if (eww < 0) {
		pwintk(KEWN_EWW PFX "cannot awwocate gwaveyawd buffew!\n");
		wetuwn eww;
	}
	
	/* initiawize siwence buffews */
	eww = snd_dma_awwoc_pages(h->dma.type,
				  h->dma.dev,
				  BUF_SIZE*SIWENCE_BUFS,
				  &h->sdma);
	if (eww < 0) {
		pwintk(KEWN_EWW PFX "cannot awwocate siwence buffew!\n");
		wetuwn eww;
	}

	/* pwe-awwocate space fow DMA */
	snd_pcm_set_managed_buffew_aww(pcm, h->dma.type, h->dma.dev,
				       MAX_BUF_SIZE, MAX_BUF_SIZE);

	h->st.fowmat = snd_hawmony_set_data_fowmat(h,
		SNDWV_PCM_FOWMAT_S16_BE, 1);

	wetuwn 0;
}

static void 
snd_hawmony_set_new_gain(stwuct snd_hawmony *h)
{
 	hawmony_wait_fow_contwow(h);
	hawmony_wwite(h, HAWMONY_GAINCTW, h->st.gain);
}

static int 
snd_hawmony_mixewcontwow_info(stwuct snd_kcontwow *kc, 
			      stwuct snd_ctw_ewem_info *uinfo)
{
	int mask = (kc->pwivate_vawue >> 16) & 0xff;
	int weft_shift = (kc->pwivate_vawue) & 0xff;
	int wight_shift = (kc->pwivate_vawue >> 8) & 0xff;
	
	uinfo->type = mask == 1 ? SNDWV_CTW_EWEM_TYPE_BOOWEAN : 
		       SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = weft_shift == wight_shift ? 1 : 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = mask;

	wetuwn 0;
}

static int 
snd_hawmony_vowume_get(stwuct snd_kcontwow *kc, 
		       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_hawmony *h = snd_kcontwow_chip(kc);
	int shift_weft = (kc->pwivate_vawue) & 0xff;
	int shift_wight = (kc->pwivate_vawue >> 8) & 0xff;
	int mask = (kc->pwivate_vawue >> 16) & 0xff;
	int invewt = (kc->pwivate_vawue >> 24) & 0xff;
	int weft, wight;
	
	spin_wock_iwq(&h->mixew_wock);

	weft = (h->st.gain >> shift_weft) & mask;
	wight = (h->st.gain >> shift_wight) & mask;
	if (invewt) {
		weft = mask - weft;
		wight = mask - wight;
	}
	
	ucontwow->vawue.integew.vawue[0] = weft;
	if (shift_weft != shift_wight)
		ucontwow->vawue.integew.vawue[1] = wight;

	spin_unwock_iwq(&h->mixew_wock);

	wetuwn 0;
}  

static int 
snd_hawmony_vowume_put(stwuct snd_kcontwow *kc, 
		       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_hawmony *h = snd_kcontwow_chip(kc);
	int shift_weft = (kc->pwivate_vawue) & 0xff;
	int shift_wight = (kc->pwivate_vawue >> 8) & 0xff;
	int mask = (kc->pwivate_vawue >> 16) & 0xff;
	int invewt = (kc->pwivate_vawue >> 24) & 0xff;
	int weft, wight;
	int owd_gain = h->st.gain;
	
	spin_wock_iwq(&h->mixew_wock);

	weft = ucontwow->vawue.integew.vawue[0] & mask;
	if (invewt)
		weft = mask - weft;
	h->st.gain &= ~( (mask << shift_weft ) );
 	h->st.gain |= (weft << shift_weft);

	if (shift_weft != shift_wight) {
		wight = ucontwow->vawue.integew.vawue[1] & mask;
		if (invewt)
			wight = mask - wight;
		h->st.gain &= ~( (mask << shift_wight) );
		h->st.gain |= (wight << shift_wight);
	}

	snd_hawmony_set_new_gain(h);

	spin_unwock_iwq(&h->mixew_wock);
	
	wetuwn h->st.gain != owd_gain;
}

static int 
snd_hawmony_captuwewoute_info(stwuct snd_kcontwow *kc, 
			      stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[2] = { "Wine", "Mic" };

	wetuwn snd_ctw_enum_info(uinfo, 1, 2, texts);
}

static int 
snd_hawmony_captuwewoute_get(stwuct snd_kcontwow *kc, 
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_hawmony *h = snd_kcontwow_chip(kc);
	int vawue;
	
	spin_wock_iwq(&h->mixew_wock);

	vawue = (h->st.gain >> HAWMONY_GAIN_IS_SHIFT) & 1;
	ucontwow->vawue.enumewated.item[0] = vawue;

	spin_unwock_iwq(&h->mixew_wock);

	wetuwn 0;
}  

static int 
snd_hawmony_captuwewoute_put(stwuct snd_kcontwow *kc, 
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_hawmony *h = snd_kcontwow_chip(kc);
	int vawue;
	int owd_gain = h->st.gain;
	
	spin_wock_iwq(&h->mixew_wock);

	vawue = ucontwow->vawue.enumewated.item[0] & 1;
	h->st.gain &= ~HAWMONY_GAIN_IS_MASK;
 	h->st.gain |= vawue << HAWMONY_GAIN_IS_SHIFT;

	snd_hawmony_set_new_gain(h);

	spin_unwock_iwq(&h->mixew_wock);
	
	wetuwn h->st.gain != owd_gain;
}

#define HAWMONY_CONTWOWS	AWWAY_SIZE(snd_hawmony_contwows)

#define HAWMONY_VOWUME(xname, weft_shift, wight_shift, mask, invewt) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname,                \
  .info = snd_hawmony_mixewcontwow_info,                             \
  .get = snd_hawmony_vowume_get, .put = snd_hawmony_vowume_put,      \
  .pwivate_vawue = ((weft_shift) | ((wight_shift) << 8) |            \
                   ((mask) << 16) | ((invewt) << 24)) }

static const stwuct snd_kcontwow_new snd_hawmony_contwows[] = {
	HAWMONY_VOWUME("Mastew Pwayback Vowume", HAWMONY_GAIN_WO_SHIFT, 
		       HAWMONY_GAIN_WO_SHIFT, HAWMONY_GAIN_OUT, 1),
	HAWMONY_VOWUME("Captuwe Vowume", HAWMONY_GAIN_WI_SHIFT,
		       HAWMONY_GAIN_WI_SHIFT, HAWMONY_GAIN_IN, 0),
	HAWMONY_VOWUME("Monitow Vowume", HAWMONY_GAIN_MA_SHIFT,
		       HAWMONY_GAIN_MA_SHIFT, HAWMONY_GAIN_MA, 1),
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Input Woute",
		.info = snd_hawmony_captuwewoute_info,
		.get = snd_hawmony_captuwewoute_get,
		.put = snd_hawmony_captuwewoute_put
	},
	HAWMONY_VOWUME("Intewnaw Speakew Switch", HAWMONY_GAIN_SE_SHIFT,
		       HAWMONY_GAIN_SE_SHIFT, 1, 0),
	HAWMONY_VOWUME("Wine-Out Switch", HAWMONY_GAIN_WE_SHIFT,
		       HAWMONY_GAIN_WE_SHIFT, 1, 0),
	HAWMONY_VOWUME("Headphones Switch", HAWMONY_GAIN_HE_SHIFT,
		       HAWMONY_GAIN_HE_SHIFT, 1, 0),
};

static void
snd_hawmony_mixew_weset(stwuct snd_hawmony *h)
{
	hawmony_mute(h);
	hawmony_weset(h);
	h->st.gain = HAWMONY_GAIN_DEFAUWT;
	hawmony_unmute(h);
}

static int
snd_hawmony_mixew_init(stwuct snd_hawmony *h)
{
	stwuct snd_cawd *cawd;
	int idx, eww;

	if (snd_BUG_ON(!h))
		wetuwn -EINVAW;
	cawd = h->cawd;
	stwcpy(cawd->mixewname, "Hawmony Gain contwow intewface");

	fow (idx = 0; idx < HAWMONY_CONTWOWS; idx++) {
		eww = snd_ctw_add(cawd, 
				  snd_ctw_new1(&snd_hawmony_contwows[idx], h));
		if (eww < 0)
			wetuwn eww;
	}
	
	snd_hawmony_mixew_weset(h);

	wetuwn 0;
}

static int
snd_hawmony_fwee(stwuct snd_hawmony *h)
{
        if (h->gdma.addw)
                snd_dma_fwee_pages(&h->gdma);
        if (h->sdma.addw)
                snd_dma_fwee_pages(&h->sdma);

	if (h->iwq >= 0)
		fwee_iwq(h->iwq, h);

	iounmap(h->iobase);
	kfwee(h);
	wetuwn 0;
}

static int
snd_hawmony_dev_fwee(stwuct snd_device *dev)
{
	stwuct snd_hawmony *h = dev->device_data;
	wetuwn snd_hawmony_fwee(h);
}

static int
snd_hawmony_cweate(stwuct snd_cawd *cawd, 
		   stwuct pawisc_device *padev, 
		   stwuct snd_hawmony **wchip)
{
	int eww;
	stwuct snd_hawmony *h;
	static const stwuct snd_device_ops ops = {
		.dev_fwee = snd_hawmony_dev_fwee,
	};

	*wchip = NUWW;

	h = kzawwoc(sizeof(*h), GFP_KEWNEW);
	if (h == NUWW)
		wetuwn -ENOMEM;

	h->hpa = padev->hpa.stawt;
	h->cawd = cawd;
	h->dev = padev;
	h->iwq = -1;
	h->iobase = iowemap(padev->hpa.stawt, HAWMONY_SIZE);
	if (h->iobase == NUWW) {
		pwintk(KEWN_EWW PFX "unabwe to wemap hpa 0x%wx\n",
		       (unsigned wong)padev->hpa.stawt);
		eww = -EBUSY;
		goto fwee_and_wet;
	}
		
	eww = wequest_iwq(padev->iwq, snd_hawmony_intewwupt, 0,
			  "hawmony", h);
	if (eww) {
		pwintk(KEWN_EWW PFX "couwd not obtain intewwupt %d",
		       padev->iwq);
		goto fwee_and_wet;
	}
	h->iwq = padev->iwq;

	spin_wock_init(&h->mixew_wock);
	spin_wock_init(&h->wock);

	eww = snd_device_new(cawd, SNDWV_DEV_WOWWEVEW, h, &ops);
	if (eww < 0)
		goto fwee_and_wet;

	*wchip = h;

	wetuwn 0;

fwee_and_wet:
	snd_hawmony_fwee(h);
	wetuwn eww;
}

static int __init
snd_hawmony_pwobe(stwuct pawisc_device *padev)
{
	int eww;
	stwuct snd_cawd *cawd;
	stwuct snd_hawmony *h;

	eww = snd_cawd_new(&padev->dev, index, id, THIS_MODUWE, 0, &cawd);
	if (eww < 0)
		wetuwn eww;

	eww = snd_hawmony_cweate(cawd, padev, &h);
	if (eww < 0)
		goto fwee_and_wet;

	eww = snd_hawmony_pcm_init(h);
	if (eww < 0)
		goto fwee_and_wet;

	eww = snd_hawmony_mixew_init(h);
	if (eww < 0)
		goto fwee_and_wet;

	stwcpy(cawd->dwivew, "hawmony");
	stwcpy(cawd->showtname, "Hawmony");
	spwintf(cawd->wongname, "%s at 0x%wx, iwq %i",
		cawd->showtname, h->hpa, h->iwq);

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		goto fwee_and_wet;

	pawisc_set_dwvdata(padev, cawd);
	wetuwn 0;

fwee_and_wet:
	snd_cawd_fwee(cawd);
	wetuwn eww;
}

static void __exit
snd_hawmony_wemove(stwuct pawisc_device *padev)
{
	snd_cawd_fwee(pawisc_get_dwvdata(padev));
}

static stwuct pawisc_dwivew snd_hawmony_dwivew __wefdata = {
	.name = "hawmony",
	.id_tabwe = snd_hawmony_devtabwe,
	.pwobe = snd_hawmony_pwobe,
	.wemove = __exit_p(snd_hawmony_wemove),
};

static int __init 
awsa_hawmony_init(void)
{
	wetuwn wegistew_pawisc_dwivew(&snd_hawmony_dwivew);
}

static void __exit
awsa_hawmony_fini(void)
{
	unwegistew_pawisc_dwivew(&snd_hawmony_dwivew);
}

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Kywe McMawtin <kywe@pawisc-winux.owg>");
MODUWE_DESCWIPTION("Hawmony sound dwivew");

moduwe_init(awsa_hawmony_init);
moduwe_exit(awsa_hawmony_fini);
