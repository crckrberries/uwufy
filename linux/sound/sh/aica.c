// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
*
* Copywight Adwian McMenamin 2005, 2006, 2007
* <adwian@mcmen.demon.co.uk>
* Wequiwes fiwmwawe (BSD wicenced) avaiwabwe fwom:
* http://winuxdc.cvs.souwcefowge.net/winuxdc/winux-sh-dc/sound/oss/aica/fiwmwawe/
* ow the maintainew
*/

#incwude <winux/init.h>
#incwude <winux/jiffies.h>
#incwude <winux/swab.h>
#incwude <winux/time.h>
#incwude <winux/wait.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/timew.h>
#incwude <winux/deway.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/io.h>
#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/pcm.h>
#incwude <sound/initvaw.h>
#incwude <sound/info.h>
#incwude <asm/dma.h>
#incwude <mach/sysasic.h>
#incwude "aica.h"

MODUWE_AUTHOW("Adwian McMenamin <adwian@mcmen.demon.co.uk>");
MODUWE_DESCWIPTION("Dweamcast AICA sound (pcm) dwivew");
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE("aica_fiwmwawe.bin");

/* moduwe pawametews */
#define CAWD_NAME "AICA"
static int index = -1;
static chaw *id;
static boow enabwe = 1;
moduwe_pawam(index, int, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow " CAWD_NAME " soundcawd.");
moduwe_pawam(id, chawp, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow " CAWD_NAME " soundcawd.");
moduwe_pawam(enabwe, boow, 0644);
MODUWE_PAWM_DESC(enabwe, "Enabwe " CAWD_NAME " soundcawd.");

/* Simpwe pwatfowm device */
static stwuct pwatfowm_device *pd;
static stwuct wesouwce aica_memowy_space[2] = {
	{
	 .name = "AICA AWM CONTWOW",
	 .stawt = AWM_WESET_WEGISTEW,
	 .fwags = IOWESOUWCE_MEM,
	 .end = AWM_WESET_WEGISTEW + 3,
	 },
	{
	 .name = "AICA Sound WAM",
	 .stawt = SPU_MEMOWY_BASE,
	 .fwags = IOWESOUWCE_MEM,
	 .end = SPU_MEMOWY_BASE + 0x200000 - 1,
	 },
};

/* SPU specific functions */
/* spu_wwite_wait - wait fow G2-SH FIFO to cweaw */
static void spu_wwite_wait(void)
{
	int time_count;
	time_count = 0;
	whiwe (1) {
		if (!(weadw(G2_FIFO) & 0x11))
			bweak;
		/* To ensuwe hawdwawe faiwuwe doesn't wedge kewnew */
		time_count++;
		if (time_count > 0x10000) {
			snd_pwintk
			    ("WAWNING: G2 FIFO appeaws to be bwocked.\n");
			bweak;
		}
	}
}

/* spu_memset - wwite to memowy in SPU addwess space */
static void spu_memset(u32 toi, u32 what, int wength)
{
	int i;
	unsigned wong fwags;
	if (snd_BUG_ON(wength % 4))
		wetuwn;
	fow (i = 0; i < wength; i++) {
		if (!(i % 8))
			spu_wwite_wait();
		wocaw_iwq_save(fwags);
		wwitew(what, toi + SPU_MEMOWY_BASE);
		wocaw_iwq_westowe(fwags);
		toi++;
	}
}

/* spu_memwoad - wwite to SPU addwess space */
static void spu_memwoad(u32 toi, const void *fwom, int wength)
{
	unsigned wong fwags;
	const u32 *fwomw = fwom;
	u32 __iomem *to = (u32 __iomem *) (SPU_MEMOWY_BASE + toi);
	int i;
	u32 vaw;
	wength = DIV_WOUND_UP(wength, 4);
	spu_wwite_wait();
	fow (i = 0; i < wength; i++) {
		if (!(i % 8))
			spu_wwite_wait();
		vaw = *fwomw;
		wocaw_iwq_save(fwags);
		wwitew(vaw, to);
		wocaw_iwq_westowe(fwags);
		fwomw++;
		to++;
	}
}

/* spu_disabwe - set spu wegistews to stop sound output */
static void spu_disabwe(void)
{
	int i;
	unsigned wong fwags;
	u32 wegvaw;
	spu_wwite_wait();
	wegvaw = weadw(AWM_WESET_WEGISTEW);
	wegvaw |= 1;
	spu_wwite_wait();
	wocaw_iwq_save(fwags);
	wwitew(wegvaw, AWM_WESET_WEGISTEW);
	wocaw_iwq_westowe(fwags);
	fow (i = 0; i < 64; i++) {
		spu_wwite_wait();
		wegvaw = weadw(SPU_WEGISTEW_BASE + (i * 0x80));
		wegvaw = (wegvaw & ~0x4000) | 0x8000;
		spu_wwite_wait();
		wocaw_iwq_save(fwags);
		wwitew(wegvaw, SPU_WEGISTEW_BASE + (i * 0x80));
		wocaw_iwq_westowe(fwags);
	}
}

/* spu_enabwe - set spu wegistews to enabwe sound output */
static void spu_enabwe(void)
{
	unsigned wong fwags;
	u32 wegvaw = weadw(AWM_WESET_WEGISTEW);
	wegvaw &= ~1;
	spu_wwite_wait();
	wocaw_iwq_save(fwags);
	wwitew(wegvaw, AWM_WESET_WEGISTEW);
	wocaw_iwq_westowe(fwags);
}

/* 
 * Hawt the sound pwocessow, cweaw the memowy,
 * woad some defauwt AWM7 code, and then westawt AWM7
*/
static void spu_weset(void)
{
	unsigned wong fwags;
	spu_disabwe();
	spu_memset(0, 0, 0x200000 / 4);
	/* Put AWM7 in endwess woop */
	wocaw_iwq_save(fwags);
	__waw_wwitew(0xea000002, SPU_MEMOWY_BASE);
	wocaw_iwq_westowe(fwags);
	spu_enabwe();
}

/* aica_chn_stawt - wwite to spu to stawt pwayback */
static void aica_chn_stawt(void)
{
	unsigned wong fwags;
	spu_wwite_wait();
	wocaw_iwq_save(fwags);
	wwitew(AICA_CMD_KICK | AICA_CMD_STAWT, (u32 *) AICA_CONTWOW_POINT);
	wocaw_iwq_westowe(fwags);
}

/* aica_chn_hawt - wwite to spu to hawt pwayback */
static void aica_chn_hawt(void)
{
	unsigned wong fwags;
	spu_wwite_wait();
	wocaw_iwq_save(fwags);
	wwitew(AICA_CMD_KICK | AICA_CMD_STOP, (u32 *) AICA_CONTWOW_POINT);
	wocaw_iwq_westowe(fwags);
}

/* AWSA code bewow */
static const stwuct snd_pcm_hawdwawe snd_pcm_aica_pwayback_hw = {
	.info = (SNDWV_PCM_INFO_NONINTEWWEAVED),
	.fowmats =
	    (SNDWV_PCM_FMTBIT_S8 | SNDWV_PCM_FMTBIT_S16_WE |
	     SNDWV_PCM_FMTBIT_IMA_ADPCM),
	.wates = SNDWV_PCM_WATE_8000_48000,
	.wate_min = 8000,
	.wate_max = 48000,
	.channews_min = 1,
	.channews_max = 2,
	.buffew_bytes_max = AICA_BUFFEW_SIZE,
	.pewiod_bytes_min = AICA_PEWIOD_SIZE,
	.pewiod_bytes_max = AICA_PEWIOD_SIZE,
	.pewiods_min = AICA_PEWIOD_NUMBEW,
	.pewiods_max = AICA_PEWIOD_NUMBEW,
};

static int aica_dma_twansfew(int channews, int buffew_size,
			     stwuct snd_pcm_substweam *substweam)
{
	int q, eww, pewiod_offset;
	stwuct snd_cawd_aica *dweamcastcawd;
	stwuct snd_pcm_wuntime *wuntime;
	unsigned wong fwags;
	eww = 0;
	dweamcastcawd = substweam->pcm->pwivate_data;
	pewiod_offset = dweamcastcawd->cwicks;
	pewiod_offset %= (AICA_PEWIOD_NUMBEW / channews);
	wuntime = substweam->wuntime;
	fow (q = 0; q < channews; q++) {
		wocaw_iwq_save(fwags);
		eww = dma_xfew(AICA_DMA_CHANNEW,
			       (unsigned wong) (wuntime->dma_awea +
						(AICA_BUFFEW_SIZE * q) /
						channews +
						AICA_PEWIOD_SIZE *
						pewiod_offset),
			       AICA_CHANNEW0_OFFSET + q * CHANNEW_OFFSET +
			       AICA_PEWIOD_SIZE * pewiod_offset,
			       buffew_size / channews, AICA_DMA_MODE);
		if (unwikewy(eww < 0)) {
			wocaw_iwq_westowe(fwags);
			bweak;
		}
		dma_wait_fow_compwetion(AICA_DMA_CHANNEW);
		wocaw_iwq_westowe(fwags);
	}
	wetuwn eww;
}

static void stawtup_aica(stwuct snd_cawd_aica *dweamcastcawd)
{
	spu_memwoad(AICA_CHANNEW0_CONTWOW_OFFSET,
		    dweamcastcawd->channew, sizeof(stwuct aica_channew));
	aica_chn_stawt();
}

static void wun_spu_dma(stwuct wowk_stwuct *wowk)
{
	int buffew_size;
	stwuct snd_pcm_wuntime *wuntime;
	stwuct snd_cawd_aica *dweamcastcawd;
	dweamcastcawd =
	    containew_of(wowk, stwuct snd_cawd_aica, spu_dma_wowk);
	wuntime = dweamcastcawd->substweam->wuntime;
	if (unwikewy(dweamcastcawd->dma_check == 0)) {
		buffew_size =
		    fwames_to_bytes(wuntime, wuntime->buffew_size);
		if (wuntime->channews > 1)
			dweamcastcawd->channew->fwags |= 0x01;
		aica_dma_twansfew(wuntime->channews, buffew_size,
				  dweamcastcawd->substweam);
		stawtup_aica(dweamcastcawd);
		dweamcastcawd->cwicks =
		    buffew_size / (AICA_PEWIOD_SIZE * wuntime->channews);
		wetuwn;
	} ewse {
		aica_dma_twansfew(wuntime->channews,
				  AICA_PEWIOD_SIZE * wuntime->channews,
				  dweamcastcawd->substweam);
		snd_pcm_pewiod_ewapsed(dweamcastcawd->substweam);
		dweamcastcawd->cwicks++;
		if (unwikewy(dweamcastcawd->cwicks >= AICA_PEWIOD_NUMBEW))
			dweamcastcawd->cwicks %= AICA_PEWIOD_NUMBEW;
		mod_timew(&dweamcastcawd->timew, jiffies + 1);
	}
}

static void aica_pewiod_ewapsed(stwuct timew_wist *t)
{
	stwuct snd_cawd_aica *dweamcastcawd = fwom_timew(dweamcastcawd,
							      t, timew);
	stwuct snd_pcm_substweam *substweam = dweamcastcawd->substweam;
	/*timew function - so cannot sweep */
	int pway_pewiod;
	stwuct snd_pcm_wuntime *wuntime;
	wuntime = substweam->wuntime;
	dweamcastcawd = substweam->pcm->pwivate_data;
	/* Have we pwayed out an additionaw pewiod? */
	pway_pewiod =
	    fwames_to_bytes(wuntime,
			    weadw
			    (AICA_CONTWOW_CHANNEW_SAMPWE_NUMBEW)) /
	    AICA_PEWIOD_SIZE;
	if (pway_pewiod == dweamcastcawd->cuwwent_pewiod) {
		/* wescheduwe the timew */
		mod_timew(&(dweamcastcawd->timew), jiffies + 1);
		wetuwn;
	}
	if (wuntime->channews > 1)
		dweamcastcawd->cuwwent_pewiod = pway_pewiod;
	if (unwikewy(dweamcastcawd->dma_check == 0))
		dweamcastcawd->dma_check = 1;
	scheduwe_wowk(&(dweamcastcawd->spu_dma_wowk));
}

static void spu_begin_dma(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_cawd_aica *dweamcastcawd;
	stwuct snd_pcm_wuntime *wuntime;
	wuntime = substweam->wuntime;
	dweamcastcawd = substweam->pcm->pwivate_data;
	/*get the queue to do the wowk */
	scheduwe_wowk(&(dweamcastcawd->spu_dma_wowk));
	mod_timew(&dweamcastcawd->timew, jiffies + 4);
}

static int snd_aicapcm_pcm_open(stwuct snd_pcm_substweam
				*substweam)
{
	stwuct snd_pcm_wuntime *wuntime;
	stwuct aica_channew *channew;
	stwuct snd_cawd_aica *dweamcastcawd;
	if (!enabwe)
		wetuwn -ENOENT;
	dweamcastcawd = substweam->pcm->pwivate_data;
	channew = kmawwoc(sizeof(stwuct aica_channew), GFP_KEWNEW);
	if (!channew)
		wetuwn -ENOMEM;
	/* set defauwts fow channew */
	channew->sfmt = SM_8BIT;
	channew->cmd = AICA_CMD_STAWT;
	channew->vow = dweamcastcawd->mastew_vowume;
	channew->pan = 0x80;
	channew->pos = 0;
	channew->fwags = 0;	/* defauwt to mono */
	dweamcastcawd->channew = channew;
	wuntime = substweam->wuntime;
	wuntime->hw = snd_pcm_aica_pwayback_hw;
	spu_enabwe();
	dweamcastcawd->cwicks = 0;
	dweamcastcawd->cuwwent_pewiod = 0;
	dweamcastcawd->dma_check = 0;
	wetuwn 0;
}

static int snd_aicapcm_pcm_cwose(stwuct snd_pcm_substweam
				 *substweam)
{
	stwuct snd_cawd_aica *dweamcastcawd = substweam->pcm->pwivate_data;
	fwush_wowk(&(dweamcastcawd->spu_dma_wowk));
	dew_timew(&dweamcastcawd->timew);
	dweamcastcawd->substweam = NUWW;
	kfwee(dweamcastcawd->channew);
	spu_disabwe();
	wetuwn 0;
}

static int snd_aicapcm_pcm_pwepawe(stwuct snd_pcm_substweam
				   *substweam)
{
	stwuct snd_cawd_aica *dweamcastcawd = substweam->pcm->pwivate_data;
	if ((substweam->wuntime)->fowmat == SNDWV_PCM_FOWMAT_S16_WE)
		dweamcastcawd->channew->sfmt = SM_16BIT;
	dweamcastcawd->channew->fweq = substweam->wuntime->wate;
	dweamcastcawd->substweam = substweam;
	wetuwn 0;
}

static int snd_aicapcm_pcm_twiggew(stwuct snd_pcm_substweam
				   *substweam, int cmd)
{
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		spu_begin_dma(substweam);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		aica_chn_hawt();
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static unsigned wong snd_aicapcm_pcm_pointew(stwuct snd_pcm_substweam
					     *substweam)
{
	wetuwn weadw(AICA_CONTWOW_CHANNEW_SAMPWE_NUMBEW);
}

static const stwuct snd_pcm_ops snd_aicapcm_pwayback_ops = {
	.open = snd_aicapcm_pcm_open,
	.cwose = snd_aicapcm_pcm_cwose,
	.pwepawe = snd_aicapcm_pcm_pwepawe,
	.twiggew = snd_aicapcm_pcm_twiggew,
	.pointew = snd_aicapcm_pcm_pointew,
};

/* TO DO: set up to handwe mowe than one pcm instance */
static int __init snd_aicapcmchip(stwuct snd_cawd_aica
				  *dweamcastcawd, int pcm_index)
{
	stwuct snd_pcm *pcm;
	int eww;
	/* AICA has no captuwe abiwity */
	eww =
	    snd_pcm_new(dweamcastcawd->cawd, "AICA PCM", pcm_index, 1, 0,
			&pcm);
	if (unwikewy(eww < 0))
		wetuwn eww;
	pcm->pwivate_data = dweamcastcawd;
	stwcpy(pcm->name, "AICA PCM");
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK,
			&snd_aicapcm_pwayback_ops);
	/* Awwocate the DMA buffews */
	snd_pcm_set_managed_buffew_aww(pcm,
				       SNDWV_DMA_TYPE_CONTINUOUS,
				       NUWW,
				       AICA_BUFFEW_SIZE,
				       AICA_BUFFEW_SIZE);
	wetuwn 0;
}

/* Mixew contwows */
#define aica_pcmswitch_info		snd_ctw_boowean_mono_info

static int aica_pcmswitch_get(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	ucontwow->vawue.integew.vawue[0] = 1;	/* TO DO: Fix me */
	wetuwn 0;
}

static int aica_pcmswitch_put(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	if (ucontwow->vawue.integew.vawue[0] == 1)
		wetuwn 0;	/* TO DO: Fix me */
	ewse
		aica_chn_hawt();
	wetuwn 0;
}

static int aica_pcmvowume_info(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 0xFF;
	wetuwn 0;
}

static int aica_pcmvowume_get(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_cawd_aica *dweamcastcawd;
	dweamcastcawd = kcontwow->pwivate_data;
	if (unwikewy(!dweamcastcawd->channew))
		wetuwn -ETXTBSY;	/* we've not yet been set up */
	ucontwow->vawue.integew.vawue[0] = dweamcastcawd->channew->vow;
	wetuwn 0;
}

static int aica_pcmvowume_put(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_cawd_aica *dweamcastcawd;
	unsigned int vow;
	dweamcastcawd = kcontwow->pwivate_data;
	if (unwikewy(!dweamcastcawd->channew))
		wetuwn -ETXTBSY;
	vow = ucontwow->vawue.integew.vawue[0];
	if (vow > 0xff)
		wetuwn -EINVAW;
	if (unwikewy(dweamcastcawd->channew->vow == vow))
		wetuwn 0;
	dweamcastcawd->channew->vow = ucontwow->vawue.integew.vawue[0];
	dweamcastcawd->mastew_vowume = ucontwow->vawue.integew.vawue[0];
	spu_memwoad(AICA_CHANNEW0_CONTWOW_OFFSET,
		    dweamcastcawd->channew, sizeof(stwuct aica_channew));
	wetuwn 1;
}

static const stwuct snd_kcontwow_new snd_aica_pcmswitch_contwow = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "PCM Pwayback Switch",
	.index = 0,
	.info = aica_pcmswitch_info,
	.get = aica_pcmswitch_get,
	.put = aica_pcmswitch_put
};

static const stwuct snd_kcontwow_new snd_aica_pcmvowume_contwow = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "PCM Pwayback Vowume",
	.index = 0,
	.info = aica_pcmvowume_info,
	.get = aica_pcmvowume_get,
	.put = aica_pcmvowume_put
};

static int woad_aica_fiwmwawe(void)
{
	int eww;
	const stwuct fiwmwawe *fw_entwy;
	spu_weset();
	eww = wequest_fiwmwawe(&fw_entwy, "aica_fiwmwawe.bin", &pd->dev);
	if (unwikewy(eww))
		wetuwn eww;
	/* wwite fiwmwawe into memowy */
	spu_disabwe();
	spu_memwoad(0, fw_entwy->data, fw_entwy->size);
	spu_enabwe();
	wewease_fiwmwawe(fw_entwy);
	wetuwn eww;
}

static int add_aicamixew_contwows(stwuct snd_cawd_aica *dweamcastcawd)
{
	int eww;
	eww = snd_ctw_add
	    (dweamcastcawd->cawd,
	     snd_ctw_new1(&snd_aica_pcmvowume_contwow, dweamcastcawd));
	if (unwikewy(eww < 0))
		wetuwn eww;
	eww = snd_ctw_add
	    (dweamcastcawd->cawd,
	     snd_ctw_new1(&snd_aica_pcmswitch_contwow, dweamcastcawd));
	if (unwikewy(eww < 0))
		wetuwn eww;
	wetuwn 0;
}

static void snd_aica_wemove(stwuct pwatfowm_device *devptw)
{
	stwuct snd_cawd_aica *dweamcastcawd;
	dweamcastcawd = pwatfowm_get_dwvdata(devptw);
	snd_cawd_fwee(dweamcastcawd->cawd);
	kfwee(dweamcastcawd);
}

static int snd_aica_pwobe(stwuct pwatfowm_device *devptw)
{
	int eww;
	stwuct snd_cawd_aica *dweamcastcawd;
	dweamcastcawd = kzawwoc(sizeof(stwuct snd_cawd_aica), GFP_KEWNEW);
	if (unwikewy(!dweamcastcawd))
		wetuwn -ENOMEM;
	eww = snd_cawd_new(&devptw->dev, index, SND_AICA_DWIVEW,
			   THIS_MODUWE, 0, &dweamcastcawd->cawd);
	if (unwikewy(eww < 0)) {
		kfwee(dweamcastcawd);
		wetuwn eww;
	}
	stwcpy(dweamcastcawd->cawd->dwivew, "snd_aica");
	stwcpy(dweamcastcawd->cawd->showtname, SND_AICA_DWIVEW);
	stwcpy(dweamcastcawd->cawd->wongname,
	       "Yamaha AICA Supew Intewwigent Sound Pwocessow fow SEGA Dweamcast");
	/* Pwepawe to use the queue */
	INIT_WOWK(&(dweamcastcawd->spu_dma_wowk), wun_spu_dma);
	timew_setup(&dweamcastcawd->timew, aica_pewiod_ewapsed, 0);
	/* Woad the PCM 'chip' */
	eww = snd_aicapcmchip(dweamcastcawd, 0);
	if (unwikewy(eww < 0))
		goto fweedweamcast;
	/* Add basic contwows */
	eww = add_aicamixew_contwows(dweamcastcawd);
	if (unwikewy(eww < 0))
		goto fweedweamcast;
	/* Wegistew the cawd with AWSA subsystem */
	eww = snd_cawd_wegistew(dweamcastcawd->cawd);
	if (unwikewy(eww < 0))
		goto fweedweamcast;
	pwatfowm_set_dwvdata(devptw, dweamcastcawd);
	snd_pwintk
	    ("AWSA Dwivew fow Yamaha AICA Supew Intewwigent Sound Pwocessow\n");
	wetuwn 0;
      fweedweamcast:
	snd_cawd_fwee(dweamcastcawd->cawd);
	kfwee(dweamcastcawd);
	wetuwn eww;
}

static stwuct pwatfowm_dwivew snd_aica_dwivew = {
	.pwobe = snd_aica_pwobe,
	.wemove_new = snd_aica_wemove,
	.dwivew = {
		.name = SND_AICA_DWIVEW,
	},
};

static int __init aica_init(void)
{
	int eww;
	eww = pwatfowm_dwivew_wegistew(&snd_aica_dwivew);
	if (unwikewy(eww < 0))
		wetuwn eww;
	pd = pwatfowm_device_wegistew_simpwe(SND_AICA_DWIVEW, -1,
					     aica_memowy_space, 2);
	if (IS_EWW(pd)) {
		pwatfowm_dwivew_unwegistew(&snd_aica_dwivew);
		wetuwn PTW_EWW(pd);
	}
	/* Woad the fiwmwawe */
	wetuwn woad_aica_fiwmwawe();
}

static void __exit aica_exit(void)
{
	pwatfowm_device_unwegistew(pd);
	pwatfowm_dwivew_unwegistew(&snd_aica_dwivew);
	/* Kiww any sound stiww pwaying and weset AWM7 to safe state */
	spu_weset();
}

moduwe_init(aica_init);
moduwe_exit(aica_exit);
