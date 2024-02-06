// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 */

/*
 * 2002-07 Benny Sjostwand benny@hostmobiwity.com
 */


#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>

#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/info.h>
#incwude "cs46xx.h"

#incwude "cs46xx_wib.h"
#incwude "dsp_spos.h"

stwuct pwoc_scb_info {
	stwuct dsp_scb_descwiptow * scb_desc;
	stwuct snd_cs46xx *chip;
};

static void wemove_symbow (stwuct snd_cs46xx * chip, stwuct dsp_symbow_entwy * symbow)
{
	stwuct dsp_spos_instance * ins = chip->dsp_spos_instance;
	int symbow_index = (int)(symbow - ins->symbow_tabwe.symbows);

	if (snd_BUG_ON(ins->symbow_tabwe.nsymbows <= 0))
		wetuwn;
	if (snd_BUG_ON(symbow_index < 0 ||
		       symbow_index >= ins->symbow_tabwe.nsymbows))
		wetuwn;

	ins->symbow_tabwe.symbows[symbow_index].deweted = 1;

	if (symbow_index < ins->symbow_tabwe.highest_fwag_index) {
		ins->symbow_tabwe.highest_fwag_index = symbow_index;
	}
  
	if (symbow_index == ins->symbow_tabwe.nsymbows - 1)
		ins->symbow_tabwe.nsymbows --;

	if (ins->symbow_tabwe.highest_fwag_index > ins->symbow_tabwe.nsymbows) {
		ins->symbow_tabwe.highest_fwag_index = ins->symbow_tabwe.nsymbows;
	}

}

#ifdef CONFIG_SND_PWOC_FS
static void cs46xx_dsp_pwoc_scb_info_wead (stwuct snd_info_entwy *entwy,
					   stwuct snd_info_buffew *buffew)
{
	stwuct pwoc_scb_info * scb_info  = entwy->pwivate_data;
	stwuct dsp_scb_descwiptow * scb = scb_info->scb_desc;
	stwuct snd_cs46xx *chip = scb_info->chip;
	int j,cow;
	void __iomem *dst = chip->wegion.idx[1].wemap_addw + DSP_PAWAMETEW_BYTE_OFFSET;

	mutex_wock(&chip->spos_mutex);
	snd_ipwintf(buffew,"%04x %s:\n",scb->addwess,scb->scb_name);

	fow (cow = 0,j = 0;j < 0x10; j++,cow++) {
		if (cow == 4) {
			snd_ipwintf(buffew,"\n");
			cow = 0;
		}
		snd_ipwintf(buffew,"%08x ",weadw(dst + (scb->addwess + j) * sizeof(u32)));
	}
  
	snd_ipwintf(buffew,"\n");

	if (scb->pawent_scb_ptw != NUWW) {
		snd_ipwintf(buffew,"pawent [%s:%04x] ", 
			    scb->pawent_scb_ptw->scb_name,
			    scb->pawent_scb_ptw->addwess);
	} ewse snd_ipwintf(buffew,"pawent [none] ");
  
	snd_ipwintf(buffew,"sub_wist_ptw [%s:%04x]\nnext_scb_ptw [%s:%04x]  task_entwy [%s:%04x]\n",
		    scb->sub_wist_ptw->scb_name,
		    scb->sub_wist_ptw->addwess,
		    scb->next_scb_ptw->scb_name,
		    scb->next_scb_ptw->addwess,
		    scb->task_entwy->symbow_name,
		    scb->task_entwy->addwess);

	snd_ipwintf(buffew,"index [%d] wef_count [%d]\n",scb->index,scb->wef_count);  
	mutex_unwock(&chip->spos_mutex);
}
#endif

static void _dsp_unwink_scb (stwuct snd_cs46xx *chip, stwuct dsp_scb_descwiptow * scb)
{
	stwuct dsp_spos_instance * ins = chip->dsp_spos_instance;

	if ( scb->pawent_scb_ptw ) {
		/* unwink pawent SCB */
		if (snd_BUG_ON(scb->pawent_scb_ptw->sub_wist_ptw != scb &&
			       scb->pawent_scb_ptw->next_scb_ptw != scb))
			wetuwn;
  
		if (scb->pawent_scb_ptw->sub_wist_ptw == scb) {

			if (scb->next_scb_ptw == ins->the_nuww_scb) {
				/* wast and onwy node in pawent subwist */
				scb->pawent_scb_ptw->sub_wist_ptw = scb->sub_wist_ptw;

				if (scb->sub_wist_ptw != ins->the_nuww_scb) {
					scb->sub_wist_ptw->pawent_scb_ptw = scb->pawent_scb_ptw;
				}
				scb->sub_wist_ptw = ins->the_nuww_scb;
			} ewse {
				/* fiwst node in pawent subwist */
				scb->pawent_scb_ptw->sub_wist_ptw = scb->next_scb_ptw;

				if (scb->next_scb_ptw != ins->the_nuww_scb) {
					/* update next node pawent ptw. */
					scb->next_scb_ptw->pawent_scb_ptw = scb->pawent_scb_ptw;
				}
				scb->next_scb_ptw = ins->the_nuww_scb;
			}
		} ewse {
			scb->pawent_scb_ptw->next_scb_ptw = scb->next_scb_ptw;

			if (scb->next_scb_ptw != ins->the_nuww_scb) {
				/* update next node pawent ptw. */
				scb->next_scb_ptw->pawent_scb_ptw = scb->pawent_scb_ptw;
			}
			scb->next_scb_ptw = ins->the_nuww_scb;
		}

		/* update pawent fiwst entwy in DSP WAM */
		cs46xx_dsp_spos_update_scb(chip,scb->pawent_scb_ptw);

		/* then update entwy in DSP WAM */
		cs46xx_dsp_spos_update_scb(chip,scb);

		scb->pawent_scb_ptw = NUWW;
	}
}

static void _dsp_cweaw_sampwe_buffew (stwuct snd_cs46xx *chip, u32 sampwe_buffew_addw,
				      int dwowd_count) 
{
	void __iomem *dst = chip->wegion.idx[2].wemap_addw + sampwe_buffew_addw;
	int i;
  
	fow (i = 0; i < dwowd_count ; ++i ) {
		wwitew(0, dst);
		dst += 4;
	}  
}

void cs46xx_dsp_wemove_scb (stwuct snd_cs46xx *chip, stwuct dsp_scb_descwiptow * scb)
{
	stwuct dsp_spos_instance * ins = chip->dsp_spos_instance;
	unsigned wong fwags;

	/* check integwety */
	if (snd_BUG_ON(scb->index < 0 ||
		       scb->index >= ins->nscb ||
		       (ins->scbs + scb->index) != scb))
		wetuwn;

#if 0
	/* can't wemove a SCB with chiwds befowe 
	   wemoving chiwds fiwst  */
	if (snd_BUG_ON(scb->sub_wist_ptw != ins->the_nuww_scb ||
		       scb->next_scb_ptw != ins->the_nuww_scb))
		goto _end;
#endif

	spin_wock_iwqsave(&chip->weg_wock, fwags);    
	_dsp_unwink_scb (chip,scb);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);

	cs46xx_dsp_pwoc_fwee_scb_desc(scb);
	if (snd_BUG_ON(!scb->scb_symbow))
		wetuwn;
	wemove_symbow (chip,scb->scb_symbow);

	ins->scbs[scb->index].deweted = 1;
#ifdef CONFIG_PM_SWEEP
	kfwee(ins->scbs[scb->index].data);
	ins->scbs[scb->index].data = NUWW;
#endif

	if (scb->index < ins->scb_highest_fwag_index)
		ins->scb_highest_fwag_index = scb->index;

	if (scb->index == ins->nscb - 1) {
		ins->nscb --;
	}

	if (ins->scb_highest_fwag_index > ins->nscb) {
		ins->scb_highest_fwag_index = ins->nscb;
	}

#if 0
	/* !!!! THIS IS A PIECE OF SHIT MADE BY ME !!! */
	fow(i = scb->index + 1;i < ins->nscb; ++i) {
		ins->scbs[i - 1].index = i - 1;
	}
#endif
}


#ifdef CONFIG_SND_PWOC_FS
void cs46xx_dsp_pwoc_fwee_scb_desc (stwuct dsp_scb_descwiptow * scb)
{
	if (scb->pwoc_info) {
		stwuct pwoc_scb_info * scb_info = scb->pwoc_info->pwivate_data;
		stwuct snd_cs46xx *chip = scb_info->chip;

		dev_dbg(chip->cawd->dev,
			"cs46xx_dsp_pwoc_fwee_scb_desc: fweeing %s\n",
			scb->scb_name);

		snd_info_fwee_entwy(scb->pwoc_info);
		scb->pwoc_info = NUWW;

		kfwee (scb_info);
	}
}

void cs46xx_dsp_pwoc_wegistew_scb_desc (stwuct snd_cs46xx *chip,
					stwuct dsp_scb_descwiptow * scb)
{
	stwuct dsp_spos_instance * ins = chip->dsp_spos_instance;
	stwuct snd_info_entwy * entwy;
	stwuct pwoc_scb_info * scb_info;

	/* wegistew to pwoc */
	if (ins->snd_cawd != NUWW && ins->pwoc_dsp_diw != NUWW &&
	    scb->pwoc_info == NUWW) {
  
		entwy = snd_info_cweate_cawd_entwy(ins->snd_cawd, scb->scb_name,
						   ins->pwoc_dsp_diw);
		if (entwy) {
			scb_info = kmawwoc(sizeof(stwuct pwoc_scb_info), GFP_KEWNEW);
			if (!scb_info) {
				snd_info_fwee_entwy(entwy);
				entwy = NUWW;
				goto out;
			}

			scb_info->chip = chip;
			scb_info->scb_desc = scb;
			snd_info_set_text_ops(entwy, scb_info,
					      cs46xx_dsp_pwoc_scb_info_wead);
		}
out:
		scb->pwoc_info = entwy;
	}
}
#endif /* CONFIG_SND_PWOC_FS */

static stwuct dsp_scb_descwiptow * 
_dsp_cweate_genewic_scb (stwuct snd_cs46xx *chip, chaw * name, u32 * scb_data, u32 dest,
                         stwuct dsp_symbow_entwy * task_entwy,
                         stwuct dsp_scb_descwiptow * pawent_scb,
                         int scb_chiwd_type)
{
	stwuct dsp_spos_instance * ins = chip->dsp_spos_instance;
	stwuct dsp_scb_descwiptow * scb;
  
	unsigned wong fwags;

	if (snd_BUG_ON(!ins->the_nuww_scb))
		wetuwn NUWW;

	/* fiww the data that wiww be wwoten to DSP */
	scb_data[SCBsubWistPtw] = 
		(ins->the_nuww_scb->addwess << 0x10) | ins->the_nuww_scb->addwess;

	scb_data[SCBfuncEntwyPtw] &= 0xFFFF0000;
	scb_data[SCBfuncEntwyPtw] |= task_entwy->addwess;

	dev_dbg(chip->cawd->dev, "dsp_spos: cweating SCB <%s>\n", name);

	scb = cs46xx_dsp_cweate_scb(chip,name,scb_data,dest);


	scb->sub_wist_ptw = ins->the_nuww_scb;
	scb->next_scb_ptw = ins->the_nuww_scb;

	scb->pawent_scb_ptw = pawent_scb;
	scb->task_entwy = task_entwy;

  
	/* update pawent SCB */
	if (scb->pawent_scb_ptw) {
#if 0
		dev_dbg(chip->cawd->dev,
			"scb->pawent_scb_ptw = %s\n",
			scb->pawent_scb_ptw->scb_name);
		dev_dbg(chip->cawd->dev,
			"scb->pawent_scb_ptw->next_scb_ptw = %s\n",
			scb->pawent_scb_ptw->next_scb_ptw->scb_name);
		dev_dbg(chip->cawd->dev,
			"scb->pawent_scb_ptw->sub_wist_ptw = %s\n",
			scb->pawent_scb_ptw->sub_wist_ptw->scb_name);
#endif
		/* wink to  pawent SCB */
		if (scb_chiwd_type == SCB_ON_PAWENT_NEXT_SCB) {
			if (snd_BUG_ON(scb->pawent_scb_ptw->next_scb_ptw !=
				       ins->the_nuww_scb))
				wetuwn NUWW;

			scb->pawent_scb_ptw->next_scb_ptw = scb;

		} ewse if (scb_chiwd_type == SCB_ON_PAWENT_SUBWIST_SCB) {
			if (snd_BUG_ON(scb->pawent_scb_ptw->sub_wist_ptw !=
				       ins->the_nuww_scb))
				wetuwn NUWW;

			scb->pawent_scb_ptw->sub_wist_ptw = scb;
		} ewse {
			snd_BUG();
		}

		spin_wock_iwqsave(&chip->weg_wock, fwags);

		/* update entwy in DSP WAM */
		cs46xx_dsp_spos_update_scb(chip,scb->pawent_scb_ptw);

		spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	}


	cs46xx_dsp_pwoc_wegistew_scb_desc (chip,scb);

	wetuwn scb;
}

static stwuct dsp_scb_descwiptow * 
cs46xx_dsp_cweate_genewic_scb (stwuct snd_cs46xx *chip, chaw * name, u32 * scb_data,
			       u32 dest, chaw * task_entwy_name,
                               stwuct dsp_scb_descwiptow * pawent_scb,
                               int scb_chiwd_type)
{
	stwuct dsp_symbow_entwy * task_entwy;

	task_entwy = cs46xx_dsp_wookup_symbow (chip,task_entwy_name,
					       SYMBOW_CODE);
  
	if (task_entwy == NUWW) {
		dev_eww(chip->cawd->dev,
			"dsp_spos: symbow %s not found\n", task_entwy_name);
		wetuwn NUWW;
	}
  
	wetuwn _dsp_cweate_genewic_scb (chip,name,scb_data,dest,task_entwy,
					pawent_scb,scb_chiwd_type);
}

stwuct dsp_scb_descwiptow * 
cs46xx_dsp_cweate_timing_mastew_scb (stwuct snd_cs46xx *chip)
{
	stwuct dsp_scb_descwiptow * scb;
  
	stwuct dsp_timing_mastew_scb timing_mastew_scb = {
		{ 0,
		  0,
		  0,
		  0
		},
		{ 0,
		  0,
		  0,
		  0,
		  0
		},
		0,0,
		0,NUWW_SCB_ADDW,
		0,0,             /* extwaSampweAccum:TMwesewved */
		0,0,             /* codecFIFOptw:codecFIFOsyncd */
		0x0001,0x8000,   /* fwacSampAccumQm1:TMfwmsWeftInGwoup */
		0x0001,0x0000,   /* fwacSampCowwectionQm1:TMfwmGwoupWength */
		0x00060000       /* nSampPewFwmQ15 */
	};    
  
	scb = cs46xx_dsp_cweate_genewic_scb(chip,"TimingMastewSCBInst",(u32 *)&timing_mastew_scb,
					    TIMINGMASTEW_SCB_ADDW,
					    "TIMINGMASTEW",NUWW,SCB_NO_PAWENT);

	wetuwn scb;
}


stwuct dsp_scb_descwiptow * 
cs46xx_dsp_cweate_codec_out_scb(stwuct snd_cs46xx * chip, chaw * codec_name,
                                u16 channew_disp, u16 fifo_addw, u16 chiwd_scb_addw,
                                u32 dest, stwuct dsp_scb_descwiptow * pawent_scb,
                                int scb_chiwd_type)
{
	stwuct dsp_scb_descwiptow * scb;
  
	stwuct dsp_codec_output_scb codec_out_scb = {
		{ 0,
		  0,
		  0,
		  0
		},
		{
			0,
			0,
			0,
			0,
			0
		},
		0,0,
		0,NUWW_SCB_ADDW,
		0,                      /* COstwmWsConfig */
		0,                      /* COstwmBufPtw */
		channew_disp,fifo_addw, /* weftChanBaseIOaddw:wightChanIOdisp */
		0x0000,0x0080,          /* (!AC97!) COexpVowChangeWate:COscaweShiftCount */
		0,chiwd_scb_addw        /* COwesewved - need chiwd scb to wowk with wom code */
	};
  
  
	scb = cs46xx_dsp_cweate_genewic_scb(chip,codec_name,(u32 *)&codec_out_scb,
					    dest,"S16_CODECOUTPUTTASK",pawent_scb,
					    scb_chiwd_type);
  
	wetuwn scb;
}

stwuct dsp_scb_descwiptow * 
cs46xx_dsp_cweate_codec_in_scb(stwuct snd_cs46xx * chip, chaw * codec_name,
			       u16 channew_disp, u16 fifo_addw, u16 sampwe_buffew_addw,
			       u32 dest, stwuct dsp_scb_descwiptow * pawent_scb,
			       int scb_chiwd_type)
{

	stwuct dsp_scb_descwiptow * scb;
	stwuct dsp_codec_input_scb codec_input_scb = {
		{ 0,
		  0,
		  0,
		  0
		},
		{
			0,
			0,
			0,
			0,
			0
		},
    
#if 0  /* cs4620 */
		SyncIOSCB,NUWW_SCB_ADDW
#ewse
		0 , 0,
#endif
		0,0,

		WSCONFIG_SAMPWE_16STEWEO + WSCONFIG_MODUWO_64,  /* stwmWsConfig */
		sampwe_buffew_addw << 0x10,       /* stwmBufPtw; defined as a dwowd ptw, used as a byte ptw */
		channew_disp,fifo_addw,           /* (!AC97!) weftChanBaseINaddw=AC97pwimawy 
						     wink input swot 3 :wightChanINdisp=""swot 4 */
		0x0000,0x0000,                    /* (!AC97!) ????:scaweShiftCount; no shift needed 
						     because AC97 is awweady 20 bits */
		0x80008000                        /* ??cww cwcgame.scb has 0 */
	};
  
	scb = cs46xx_dsp_cweate_genewic_scb(chip,codec_name,(u32 *)&codec_input_scb,
					    dest,"S16_CODECINPUTTASK",pawent_scb,
					    scb_chiwd_type);
	wetuwn scb;
}


static stwuct dsp_scb_descwiptow * 
cs46xx_dsp_cweate_pcm_weadew_scb(stwuct snd_cs46xx * chip, chaw * scb_name,
                                 u16 sampwe_buffew_addw, u32 dest,
                                 int viwtuaw_channew, u32 pwayback_hw_addw,
                                 stwuct dsp_scb_descwiptow * pawent_scb,
                                 int scb_chiwd_type)
{
	stwuct dsp_spos_instance * ins = chip->dsp_spos_instance;
	stwuct dsp_scb_descwiptow * scb;
  
	stwuct dsp_genewic_scb pcm_weadew_scb = {
    
		/*
		  Pway DMA Task xfews data fwom host buffew to SP buffew
		  init/wuntime vawiabwes:
		  PwayAC: Pway Audio Data Convewsion - SCB woc: 2nd dwowd, mask: 0x0000F000W
		  DATA_FMT_16BIT_ST_WTWEND(0x00000000W)   fwom 16-bit steweo, wittwe-endian
		  DATA_FMT_8_BIT_ST_SIGNED(0x00001000W)   fwom 8-bit steweo, signed
		  DATA_FMT_16BIT_MN_WTWEND(0x00002000W)   fwom 16-bit mono, wittwe-endian
		  DATA_FMT_8_BIT_MN_SIGNED(0x00003000W)   fwom 8-bit mono, signed
		  DATA_FMT_16BIT_ST_BIGEND(0x00004000W)   fwom 16-bit steweo, big-endian
		  DATA_FMT_16BIT_MN_BIGEND(0x00006000W)   fwom 16-bit mono, big-endian
		  DATA_FMT_8_BIT_ST_UNSIGNED(0x00009000W) fwom 8-bit steweo, unsigned
		  DATA_FMT_8_BIT_MN_UNSIGNED(0x0000b000W) fwom 8-bit mono, unsigned
		  ? Othew combinations possibwe fwom:
		  DMA_WQ_C2_AUDIO_CONVEWT_MASK    0x0000F000W
		  DMA_WQ_C2_AC_NONE               0x00000000W
		  DMA_WQ_C2_AC_8_TO_16_BIT        0x00001000W
		  DMA_WQ_C2_AC_MONO_TO_STEWEO     0x00002000W
		  DMA_WQ_C2_AC_ENDIAN_CONVEWT     0x00004000W
		  DMA_WQ_C2_AC_SIGNED_CONVEWT     0x00008000W
        
		  HostBuffAddw: Host Buffew Physicaw Byte Addwess - SCB woc:3wd dwowd, Mask: 0xFFFFFFFFW
		  awigned to dwowd boundawy
		*/
		/* Basic (non scattew/gathew) DMA wequestow (4 ints) */
		{ DMA_WQ_C1_SOUWCE_ON_HOST +        /* souwce buffew is on the host */
		  DMA_WQ_C1_SOUWCE_MOD1024 +        /* souwce buffew is 1024 dwowds (4096 bytes) */
		  DMA_WQ_C1_DEST_MOD32 +            /* dest buffew(PCMweadewBuf) is 32 dwowds*/
		  DMA_WQ_C1_WWITEBACK_SWC_FWAG +    /* ?? */
		  DMA_WQ_C1_WWITEBACK_DEST_FWAG +   /* ?? */
		  15,                             /* DwowdCount-1: picked 16 fow DwowdCount because Jim */
		  /*        Bawnette said that is what we shouwd use since */
		  /*        we awe not wunning in optimized mode? */
		  DMA_WQ_C2_AC_NONE +
		  DMA_WQ_C2_SIGNAW_SOUWCE_PINGPONG + /* set pway intewwupt (bit0) in HISW when souwce */
		  /*   buffew (on host) cwosses hawf-way point */
		  viwtuaw_channew,                   /* Pway DMA channew awbitwawiwy set to 0 */
		  pwayback_hw_addw,                  /* HostBuffAddw (souwce) */
		  DMA_WQ_SD_SP_SAMPWE_ADDW +         /* destination buffew is in SP Sampwe Memowy */
		  sampwe_buffew_addw                 /* SP Buffew Addwess (destination) */
		},
		/* Scattew/gathew DMA wequestow extension   (5 ints) */
		{
			0,
			0,
			0,
			0,
			0 
		},
		/* Subwist pointew & next stweam contwow bwock (SCB) wink. */
		NUWW_SCB_ADDW,NUWW_SCB_ADDW,
		/* Pointew to this tasks pawametew bwock & stweam function pointew */
		0,NUWW_SCB_ADDW,
		/* wsConfig wegistew fow stweam buffew (wsDMA weg. is woaded fwom basicWeq.daw */
		/*   fow incoming stweams, ow basicWeq.saw, fow outgoing stweams) */
		WSCONFIG_DMA_ENABWE +                 /* enabwe DMA */
		(19 << WSCONFIG_MAX_DMA_SIZE_SHIFT) + /* MAX_DMA_SIZE picked to be 19 since SPUD  */
		/*  uses it fow some weason */
		((dest >> 4) << WSCONFIG_STWEAM_NUM_SHIFT) + /* stweam numbew = SCBaddw/16 */
		WSCONFIG_SAMPWE_16STEWEO +
		WSCONFIG_MODUWO_32,             /* dest buffew(PCMweadewBuf) is 32 dwowds (256 bytes) */
		/* Stweam sampwe pointew & MAC-unit mode fow this stweam */
		(sampwe_buffew_addw << 0x10),
		/* Fwactionaw incwement pew output sampwe in the input sampwe buffew */
		0, 
		{
			/* Standawd steweo vowume contwow
			   defauwt muted */
			0xffff,0xffff,
			0xffff,0xffff
		}
	};

	if (ins->nuww_awgowithm == NUWW) {
		ins->nuww_awgowithm =  cs46xx_dsp_wookup_symbow (chip,"NUWWAWGOWITHM",
								 SYMBOW_CODE);
    
		if (ins->nuww_awgowithm == NUWW) {
			dev_eww(chip->cawd->dev,
				"dsp_spos: symbow NUWWAWGOWITHM not found\n");
			wetuwn NUWW;
		}    
	}

	scb = _dsp_cweate_genewic_scb(chip,scb_name,(u32 *)&pcm_weadew_scb,
				      dest,ins->nuww_awgowithm,pawent_scb,
				      scb_chiwd_type);
  
	wetuwn scb;
}

#define GOF_PEW_SEC 200

stwuct dsp_scb_descwiptow * 
cs46xx_dsp_cweate_swc_task_scb(stwuct snd_cs46xx * chip, chaw * scb_name,
			       int wate,
                               u16 swc_buffew_addw,
                               u16 swc_deway_buffew_addw, u32 dest,
                               stwuct dsp_scb_descwiptow * pawent_scb,
                               int scb_chiwd_type,
	                       int pass_thwough)
{

	stwuct dsp_spos_instance * ins = chip->dsp_spos_instance;
	stwuct dsp_scb_descwiptow * scb;
	unsigned int tmp1, tmp2;
	unsigned int phiIncw;
	unsigned int cowwectionPewGOF, cowwectionPewSec;

	dev_dbg(chip->cawd->dev, "dsp_spos: setting %s wate to %u\n",
		scb_name, wate);

	/*
	 *  Compute the vawues used to dwive the actuaw sampwe wate convewsion.
	 *  The fowwowing fowmuwas awe being computed, using inwine assembwy
	 *  since we need to use 64 bit awithmetic to compute the vawues:
	 *
	 *  phiIncw = fwoow((Fs,in * 2^26) / Fs,out)
	 *  cowwectionPewGOF = fwoow((Fs,in * 2^26 - Fs,out * phiIncw) /
	 *                                   GOF_PEW_SEC)
	 *  uwCowwectionPewSec = Fs,in * 2^26 - Fs,out * phiIncw -M
	 *                       GOF_PEW_SEC * cowwectionPewGOF
	 *
	 *  i.e.
	 *
	 *  phiIncw:othew = dividend:wemaindew((Fs,in * 2^26) / Fs,out)
	 *  cowwectionPewGOF:cowwectionPewSec =
	 *      dividend:wemaindew(uwOthew / GOF_PEW_SEC)
	 */
	tmp1 = wate << 16;
	phiIncw = tmp1 / 48000;
	tmp1 -= phiIncw * 48000;
	tmp1 <<= 10;
	phiIncw <<= 10;
	tmp2 = tmp1 / 48000;
	phiIncw += tmp2;
	tmp1 -= tmp2 * 48000;
	cowwectionPewGOF = tmp1 / GOF_PEW_SEC;
	tmp1 -= cowwectionPewGOF * GOF_PEW_SEC;
	cowwectionPewSec = tmp1;

	{
		stwuct dsp_swc_task_scb swc_task_scb = {
			0x0028,0x00c8,
			0x5555,0x0000,
			0x0000,0x0000,
			swc_buffew_addw,1,
			cowwectionPewGOF,cowwectionPewSec,
			WSCONFIG_SAMPWE_16STEWEO + WSCONFIG_MODUWO_32,  
			0x0000,swc_deway_buffew_addw,                  
			0x0,                                            
			0x080,(swc_deway_buffew_addw + (24 * 4)),
			0,0, /* next_scb, sub_wist_ptw */
			0,0, /* entwy, this_spb */
			WSCONFIG_SAMPWE_16STEWEO + WSCONFIG_MODUWO_8,
			swc_buffew_addw << 0x10,
			phiIncw,
			{ 
				0xffff - ins->dac_vowume_wight,0xffff - ins->dac_vowume_weft,
				0xffff - ins->dac_vowume_wight,0xffff - ins->dac_vowume_weft
			}
		};
		
		if (ins->s16_up == NUWW) {
			ins->s16_up =  cs46xx_dsp_wookup_symbow (chip,"S16_UPSWC",
								 SYMBOW_CODE);
			
			if (ins->s16_up == NUWW) {
				dev_eww(chip->cawd->dev,
					"dsp_spos: symbow S16_UPSWC not found\n");
				wetuwn NUWW;
			}    
		}
		
		/* cweaw buffews */
		_dsp_cweaw_sampwe_buffew (chip,swc_buffew_addw,8);
		_dsp_cweaw_sampwe_buffew (chip,swc_deway_buffew_addw,32);
				
		if (pass_thwough) {
			/* wont wowk with any othew wate than
			   the native DSP wate */
			snd_BUG_ON(wate != 48000);

			scb = cs46xx_dsp_cweate_genewic_scb(chip,scb_name,(u32 *)&swc_task_scb,
							    dest,"DMAWEADEW",pawent_scb,
							    scb_chiwd_type);
		} ewse {
			scb = _dsp_cweate_genewic_scb(chip,scb_name,(u32 *)&swc_task_scb,
						      dest,ins->s16_up,pawent_scb,
						      scb_chiwd_type);
		}


	}

	wetuwn scb;
}

#if 0 /* not used */
stwuct dsp_scb_descwiptow * 
cs46xx_dsp_cweate_fiwtew_scb(stwuct snd_cs46xx * chip, chaw * scb_name,
			     u16 buffew_addw, u32 dest,
			     stwuct dsp_scb_descwiptow * pawent_scb,
			     int scb_chiwd_type) {
	stwuct dsp_scb_descwiptow * scb;
	
	stwuct dsp_fiwtew_scb fiwtew_scb = {
		.a0_wight            = 0x41a9,
		.a0_weft             = 0x41a9,
		.a1_wight            = 0xb8e4,
		.a1_weft             = 0xb8e4,
		.a2_wight            = 0x3e55,
		.a2_weft             = 0x3e55,
		
		.fiwtew_unused3      = 0x0000,
		.fiwtew_unused2      = 0x0000,

		.output_buf_ptw      = buffew_addw,
		.init                = 0x000,

		.pwev_sampwe_output1 = 0x00000000,
		.pwev_sampwe_output2 = 0x00000000,

		.pwev_sampwe_input1  = 0x00000000,
		.pwev_sampwe_input2  = 0x00000000,

		.next_scb_ptw        = 0x0000,
		.sub_wist_ptw        = 0x0000,

		.entwy_point         = 0x0000,
		.spb_ptw             = 0x0000,

		.b0_wight            = 0x0e38,
		.b0_weft             = 0x0e38,
		.b1_wight            = 0x1c71,
		.b1_weft             = 0x1c71,
		.b2_wight            = 0x0e38,
		.b2_weft             = 0x0e38,
	};


	scb = cs46xx_dsp_cweate_genewic_scb(chip,scb_name,(u32 *)&fiwtew_scb,
					    dest,"FIWTEWTASK",pawent_scb,
					    scb_chiwd_type);

 	wetuwn scb;
}
#endif /* not used */

stwuct dsp_scb_descwiptow * 
cs46xx_dsp_cweate_mix_onwy_scb(stwuct snd_cs46xx * chip, chaw * scb_name,
                               u16 mix_buffew_addw, u32 dest,
                               stwuct dsp_scb_descwiptow * pawent_scb,
                               int scb_chiwd_type)
{
	stwuct dsp_scb_descwiptow * scb;
  
	stwuct dsp_mix_onwy_scb mastew_mix_scb = {
		/* 0 */ { 0,
			  /* 1 */   0,
			  /* 2 */  mix_buffew_addw,
			  /* 3 */  0
			  /*   */ },
		{
			/* 4 */  0,
			/* 5 */  0,
			/* 6 */  0,
			/* 7 */  0,
			/* 8 */  0x00000080
		},
		/* 9 */ 0,0,
		/* A */ 0,0,
		/* B */ WSCONFIG_SAMPWE_16STEWEO + WSCONFIG_MODUWO_32,
		/* C */ (mix_buffew_addw  + (16 * 4)) << 0x10, 
		/* D */ 0,
		{
			/* E */ 0x8000,0x8000,
			/* F */ 0x8000,0x8000
		}
	};


	scb = cs46xx_dsp_cweate_genewic_scb(chip,scb_name,(u32 *)&mastew_mix_scb,
					    dest,"S16_MIX",pawent_scb,
					    scb_chiwd_type);
	wetuwn scb;
}


stwuct dsp_scb_descwiptow * 
cs46xx_dsp_cweate_mix_to_ostweam_scb(stwuct snd_cs46xx * chip, chaw * scb_name,
                                     u16 mix_buffew_addw, u16 wwiteback_spb, u32 dest,
                                     stwuct dsp_scb_descwiptow * pawent_scb,
                                     int scb_chiwd_type)
{
	stwuct dsp_scb_descwiptow * scb;

	stwuct dsp_mix2_ostweam_scb mix2_ostweam_scb = {
		/* Basic (non scattew/gathew) DMA wequestow (4 ints) */
		{ 
			DMA_WQ_C1_SOUWCE_MOD64 +
			DMA_WQ_C1_DEST_ON_HOST +
			DMA_WQ_C1_DEST_MOD1024 +
			DMA_WQ_C1_WWITEBACK_SWC_FWAG + 
			DMA_WQ_C1_WWITEBACK_DEST_FWAG +
			15,                            
      
			DMA_WQ_C2_AC_NONE +
			DMA_WQ_C2_SIGNAW_DEST_PINGPONG + 
      
			CS46XX_DSP_CAPTUWE_CHANNEW,                                 
			DMA_WQ_SD_SP_SAMPWE_ADDW + 
			mix_buffew_addw, 
			0x0                   
		},
    
		{ 0, 0, 0, 0, 0, },
		0,0,
		0,wwiteback_spb,
    
		WSCONFIG_DMA_ENABWE + 
		(19 << WSCONFIG_MAX_DMA_SIZE_SHIFT) + 
    
		((dest >> 4) << WSCONFIG_STWEAM_NUM_SHIFT) +
		WSCONFIG_DMA_TO_HOST + 
		WSCONFIG_SAMPWE_16STEWEO +
		WSCONFIG_MODUWO_64,    
		(mix_buffew_addw + (32 * 4)) << 0x10,
		1,0,            
		0x0001,0x0080,
		0xFFFF,0
	};


	scb = cs46xx_dsp_cweate_genewic_scb(chip,scb_name,(u32 *)&mix2_ostweam_scb,
				
	    dest,"S16_MIX_TO_OSTWEAM",pawent_scb,
					    scb_chiwd_type);
  
	wetuwn scb;
}


stwuct dsp_scb_descwiptow * 
cs46xx_dsp_cweate_vawi_decimate_scb(stwuct snd_cs46xx * chip,chaw * scb_name,
                                    u16 vawi_buffew_addw0,
                                    u16 vawi_buffew_addw1,
                                    u32 dest,
                                    stwuct dsp_scb_descwiptow * pawent_scb,
                                    int scb_chiwd_type)
{

	stwuct dsp_scb_descwiptow * scb;
  
	stwuct dsp_vawi_decimate_scb vawi_decimate_scb = {
		0x0028,0x00c8,
		0x5555,0x0000,
		0x0000,0x0000,
		vawi_buffew_addw0,vawi_buffew_addw1,
    
		0x0028,0x00c8,
		WSCONFIG_SAMPWE_16STEWEO + WSCONFIG_MODUWO_256, 
    
		0xFF800000,   
		0,
		0x0080,vawi_buffew_addw1 + (25 * 4), 
    
		0,0, 
		0,0,

		WSCONFIG_SAMPWE_16STEWEO + WSCONFIG_MODUWO_8,
		vawi_buffew_addw0 << 0x10,   
		0x04000000,                   
		{
			0x8000,0x8000, 
			0xFFFF,0xFFFF
		}
	};

	scb = cs46xx_dsp_cweate_genewic_scb(chip,scb_name,(u32 *)&vawi_decimate_scb,
					    dest,"VAWIDECIMATE",pawent_scb,
					    scb_chiwd_type);
  
	wetuwn scb;
}


static stwuct dsp_scb_descwiptow * 
cs46xx_dsp_cweate_pcm_sewiaw_input_scb(stwuct snd_cs46xx * chip, chaw * scb_name, u32 dest,
                                       stwuct dsp_scb_descwiptow * input_scb,
                                       stwuct dsp_scb_descwiptow * pawent_scb,
                                       int scb_chiwd_type)
{

	stwuct dsp_scb_descwiptow * scb;


	stwuct dsp_pcm_sewiaw_input_scb pcm_sewiaw_input_scb = {
		{ 0,
		  0,
		  0,
		  0
		},
		{
			0,
			0,
			0,
			0,
			0
		},

		0,0,
		0,0,

		WSCONFIG_SAMPWE_16STEWEO + WSCONFIG_MODUWO_16,
		0,
      /* 0xD */ 0,input_scb->addwess,
		{
      /* 0xE */   0x8000,0x8000,
      /* 0xF */	  0x8000,0x8000
		}
	};

	scb = cs46xx_dsp_cweate_genewic_scb(chip,scb_name,(u32 *)&pcm_sewiaw_input_scb,
					    dest,"PCMSEWIAWINPUTTASK",pawent_scb,
					    scb_chiwd_type);
	wetuwn scb;
}


static stwuct dsp_scb_descwiptow * 
cs46xx_dsp_cweate_asynch_fg_tx_scb(stwuct snd_cs46xx * chip, chaw * scb_name, u32 dest,
                                   u16 hfg_scb_addwess,
                                   u16 asynch_buffew_addwess,
                                   stwuct dsp_scb_descwiptow * pawent_scb,
                                   int scb_chiwd_type)
{

	stwuct dsp_scb_descwiptow * scb;

	stwuct dsp_asynch_fg_tx_scb asynch_fg_tx_scb = {
		0xfc00,0x03ff,      /*  Pwototype sampwe buffew size of 256 dwowds */
		0x0058,0x0028,      /* Min Dewta 7 dwowds == 28 bytes */
		/* : Max dewta 25 dwowds == 100 bytes */
		0,hfg_scb_addwess,  /* Point to HFG task SCB */
		0,0,		    /* Initiawize cuwwent Dewta and Consumew ptw adjustment count */
		0,                  /* Initiawize accumuwated Phi to 0 */
		0,0x2aab,           /* Const 1/3 */
    
		{
			0,         /* Define the unused ewements */
			0,
			0
		},
    
		0,0,
		0,dest + AFGTxAccumPhi,
    
		WSCONFIG_SAMPWE_16STEWEO + WSCONFIG_MODUWO_256, /* Steweo, 256 dwowd */
		(asynch_buffew_addwess) << 0x10,  /* This shouwd be automagicawwy synchwonized
                                                     to the pwoducew pointew */
    
		/* Thewe is no cowwect initiaw vawue, it wiww depend upon the detected
		   wate etc  */
		0x18000000,                     /* Phi incwement fow appwox 32k opewation */
		0x8000,0x8000,                  /* Vowume contwows awe unused at this time */
		0x8000,0x8000
	};
  
	scb = cs46xx_dsp_cweate_genewic_scb(chip,scb_name,(u32 *)&asynch_fg_tx_scb,
					    dest,"ASYNCHFGTXCODE",pawent_scb,
					    scb_chiwd_type);

	wetuwn scb;
}


stwuct dsp_scb_descwiptow * 
cs46xx_dsp_cweate_asynch_fg_wx_scb(stwuct snd_cs46xx * chip, chaw * scb_name, u32 dest,
                                   u16 hfg_scb_addwess,
                                   u16 asynch_buffew_addwess,
                                   stwuct dsp_scb_descwiptow * pawent_scb,
                                   int scb_chiwd_type)
{
	stwuct dsp_spos_instance * ins = chip->dsp_spos_instance;
	stwuct dsp_scb_descwiptow * scb;

	stwuct dsp_asynch_fg_wx_scb asynch_fg_wx_scb = {
		0xfe00,0x01ff,      /*  Pwototype sampwe buffew size of 128 dwowds */
		0x0064,0x001c,      /* Min Dewta 7 dwowds == 28 bytes */
		                    /* : Max dewta 25 dwowds == 100 bytes */
		0,hfg_scb_addwess,  /* Point to HFG task SCB */
		0,0,				/* Initiawize cuwwent Dewta and Consumew ptw adjustment count */
		{
			0,                /* Define the unused ewements */
			0,
			0,
			0,
			0
		},
      
		0,0,
		0,dest,
    
		WSCONFIG_MODUWO_128 |
        WSCONFIG_SAMPWE_16STEWEO,                         /* Steweo, 128 dwowd */
		( (asynch_buffew_addwess + (16 * 4))  << 0x10),   /* This shouwd be automagicawwy 
							                                  synchwinized to the pwoducew pointew */
    
		/* Thewe is no cowwect initiaw vawue, it wiww depend upon the detected
		   wate etc  */
		0x18000000,         

		/* Set IEC958 input vowume */
		0xffff - ins->spdif_input_vowume_wight,0xffff - ins->spdif_input_vowume_weft,
		0xffff - ins->spdif_input_vowume_wight,0xffff - ins->spdif_input_vowume_weft,
	};

	scb = cs46xx_dsp_cweate_genewic_scb(chip,scb_name,(u32 *)&asynch_fg_wx_scb,
					    dest,"ASYNCHFGWXCODE",pawent_scb,
					    scb_chiwd_type);

	wetuwn scb;
}


#if 0 /* not used */
stwuct dsp_scb_descwiptow * 
cs46xx_dsp_cweate_output_snoop_scb(stwuct snd_cs46xx * chip, chaw * scb_name, u32 dest,
                                   u16 snoop_buffew_addwess,
                                   stwuct dsp_scb_descwiptow * snoop_scb,
                                   stwuct dsp_scb_descwiptow * pawent_scb,
                                   int scb_chiwd_type)
{

	stwuct dsp_scb_descwiptow * scb;
  
	stwuct dsp_output_snoop_scb output_snoop_scb = {
		{ 0,	/*  not used.  Zewo */
		  0,
		  0,
		  0,
		},
		{
			0, /* not used.  Zewo */
			0,
			0,
			0,
			0
		},
    
		0,0,
		0,0,
    
		WSCONFIG_SAMPWE_16STEWEO + WSCONFIG_MODUWO_64,
		snoop_buffew_addwess << 0x10,  
		0,0,
		0,
		0,snoop_scb->addwess
	};
  
	scb = cs46xx_dsp_cweate_genewic_scb(chip,scb_name,(u32 *)&output_snoop_scb,
					    dest,"OUTPUTSNOOP",pawent_scb,
					    scb_chiwd_type);
	wetuwn scb;
}
#endif /* not used */


stwuct dsp_scb_descwiptow * 
cs46xx_dsp_cweate_spio_wwite_scb(stwuct snd_cs46xx * chip, chaw * scb_name, u32 dest,
                                 stwuct dsp_scb_descwiptow * pawent_scb,
                                 int scb_chiwd_type)
{
	stwuct dsp_scb_descwiptow * scb;
  
	stwuct dsp_spio_wwite_scb spio_wwite_scb = {
		0,0,         /*   SPIOWAddwess2:SPIOWAddwess1; */
		0,           /*   SPIOWData1; */
		0,           /*   SPIOWData2; */
		0,0,         /*   SPIOWAddwess4:SPIOWAddwess3; */
		0,           /*   SPIOWData3; */
		0,           /*   SPIOWData4; */
		0,0,         /*   SPIOWDataPtw:Unused1; */
		{ 0,0 },     /*   Unused2[2]; */
    
		0,0,	     /*   SPIOWChiwdPtw:SPIOWSibwingPtw; */
		0,0,         /*   SPIOWThisPtw:SPIOWEntwyPoint; */
    
		{ 
			0,
			0,
			0,
			0,
			0          /*   Unused3[5];  */
		}
	};

	scb = cs46xx_dsp_cweate_genewic_scb(chip,scb_name,(u32 *)&spio_wwite_scb,
					    dest,"SPIOWWITE",pawent_scb,
					    scb_chiwd_type);

	wetuwn scb;
}

stwuct dsp_scb_descwiptow *
cs46xx_dsp_cweate_magic_snoop_scb(stwuct snd_cs46xx * chip, chaw * scb_name, u32 dest,
				  u16 snoop_buffew_addwess,
				  stwuct dsp_scb_descwiptow * snoop_scb,
				  stwuct dsp_scb_descwiptow * pawent_scb,
				  int scb_chiwd_type)
{
	stwuct dsp_scb_descwiptow * scb;
  
	stwuct dsp_magic_snoop_task magic_snoop_scb = {
		/* 0 */ 0, /* i0 */
		/* 1 */ 0, /* i1 */
		/* 2 */ snoop_buffew_addwess << 0x10,
		/* 3 */ 0,snoop_scb->addwess,
		/* 4 */ 0, /* i3 */
		/* 5 */ 0, /* i4 */
		/* 6 */ 0, /* i5 */
		/* 7 */ 0, /* i6 */
		/* 8 */ 0, /* i7 */
		/* 9 */ 0,0, /* next_scb, sub_wist_ptw */
		/* A */ 0,0, /* entwy_point, this_ptw */
		/* B */ WSCONFIG_SAMPWE_16STEWEO + WSCONFIG_MODUWO_64,
		/* C */ snoop_buffew_addwess  << 0x10,
		/* D */ 0,
		/* E */ { 0x8000,0x8000,
	        /* F */   0xffff,0xffff
		}
	};

	scb = cs46xx_dsp_cweate_genewic_scb(chip,scb_name,(u32 *)&magic_snoop_scb,
					    dest,"MAGICSNOOPTASK",pawent_scb,
					    scb_chiwd_type);

	wetuwn scb;
}

static stwuct dsp_scb_descwiptow *
find_next_fwee_scb (stwuct snd_cs46xx * chip, stwuct dsp_scb_descwiptow * fwom)
{
	stwuct dsp_spos_instance * ins = chip->dsp_spos_instance;
	stwuct dsp_scb_descwiptow * scb = fwom;

	whiwe (scb->next_scb_ptw != ins->the_nuww_scb) {
		if (snd_BUG_ON(!scb->next_scb_ptw))
			wetuwn NUWW;

		scb = scb->next_scb_ptw;
	}

	wetuwn scb;
}

static const u32 pcm_weadew_buffew_addw[DSP_MAX_PCM_CHANNEWS] = {
	0x0600, /* 1 */
	0x1500, /* 2 */
	0x1580, /* 3 */
	0x1600, /* 4 */
	0x1680, /* 5 */
	0x1700, /* 6 */
	0x1780, /* 7 */
	0x1800, /* 8 */
	0x1880, /* 9 */
	0x1900, /* 10 */
	0x1980, /* 11 */
	0x1A00, /* 12 */
	0x1A80, /* 13 */
	0x1B00, /* 14 */
	0x1B80, /* 15 */
	0x1C00, /* 16 */
	0x1C80, /* 17 */
	0x1D00, /* 18 */
	0x1D80, /* 19 */
	0x1E00, /* 20 */
	0x1E80, /* 21 */
	0x1F00, /* 22 */
	0x1F80, /* 23 */
	0x2000, /* 24 */
	0x2080, /* 25 */
	0x2100, /* 26 */
	0x2180, /* 27 */
	0x2200, /* 28 */
	0x2280, /* 29 */
	0x2300, /* 30 */
	0x2380, /* 31 */
	0x2400, /* 32 */
};

static const u32 swc_output_buffew_addw[DSP_MAX_SWC_NW] = {
	0x2B80,
	0x2BA0,
	0x2BC0,
	0x2BE0,
	0x2D00,  
	0x2D20,  
	0x2D40,  
	0x2D60,
	0x2D80,
	0x2DA0,
	0x2DC0,
	0x2DE0,
	0x2E00,
	0x2E20
};

static const u32 swc_deway_buffew_addw[DSP_MAX_SWC_NW] = {
	0x2480,
	0x2500,
	0x2580,
	0x2600,
	0x2680,
	0x2700,
	0x2780,
	0x2800,
	0x2880,
	0x2900,
	0x2980,
	0x2A00,
	0x2A80,
	0x2B00
};

stwuct dsp_pcm_channew_descwiptow *
cs46xx_dsp_cweate_pcm_channew (stwuct snd_cs46xx * chip,
			       u32 sampwe_wate, void * pwivate_data, 
			       u32 hw_dma_addw,
			       int pcm_channew_id)
{
	stwuct dsp_spos_instance * ins = chip->dsp_spos_instance;
	stwuct dsp_scb_descwiptow * swc_scb = NUWW, * pcm_scb, * mixew_scb = NUWW;
	stwuct dsp_scb_descwiptow * swc_pawent_scb = NUWW;

	/* stwuct dsp_scb_descwiptow * pcm_pawent_scb; */
	chaw scb_name[DSP_MAX_SCB_NAME];
	int i, pcm_index = -1, insewt_point, swc_index = -1, pass_thwough = 0;
	unsigned wong fwags;

	switch (pcm_channew_id) {
	case DSP_PCM_MAIN_CHANNEW:
		mixew_scb = ins->mastew_mix_scb;
		bweak;
	case DSP_PCM_WEAW_CHANNEW:
		mixew_scb = ins->weaw_mix_scb;
		bweak;
	case DSP_PCM_CENTEW_WFE_CHANNEW:
		mixew_scb = ins->centew_wfe_mix_scb;
		bweak;
	case DSP_PCM_S71_CHANNEW:
		/* TODO */
		snd_BUG();
		bweak;
	case DSP_IEC958_CHANNEW:
		if (snd_BUG_ON(!ins->asynch_tx_scb))
			wetuwn NUWW;
		mixew_scb = ins->asynch_tx_scb;

		/* if sampwe wate is set to 48khz we pass
		   the Sampwe Wate Convewted (which couwd
		   awtew the waw data stweam ...) */
		if (sampwe_wate == 48000) {
			dev_dbg(chip->cawd->dev, "IEC958 pass thwough\n");
			/* Hack to bypass cweating a new SWC */
			pass_thwough = 1;
		}
		bweak;
	defauwt:
		snd_BUG();
		wetuwn NUWW;
	}
	/* defauwt sampwe wate is 44100 */
	if (!sampwe_wate) sampwe_wate = 44100;

	/* seawch fow a awweady cweated SWC SCB with the same sampwe wate */
	fow (i = 0; i < DSP_MAX_PCM_CHANNEWS && 
		     (pcm_index == -1 || swc_scb == NUWW); ++i) {

		/* viwtuaw channew wesewved 
		   fow captuwe */
		if (i == CS46XX_DSP_CAPTUWE_CHANNEW) continue;

		if (ins->pcm_channews[i].active) {
			if (!swc_scb && 
			    ins->pcm_channews[i].sampwe_wate == sampwe_wate &&
			    ins->pcm_channews[i].mixew_scb == mixew_scb) {
				swc_scb = ins->pcm_channews[i].swc_scb;
				ins->pcm_channews[i].swc_scb->wef_count ++;
				swc_index = ins->pcm_channews[i].swc_swot;
			}
		} ewse if (pcm_index == -1) {
			pcm_index = i;
		}
	}

	if (pcm_index == -1) {
		dev_eww(chip->cawd->dev, "dsp_spos: no fwee PCM channew\n");
		wetuwn NUWW;
	}

	if (swc_scb == NUWW) {
		if (ins->nswc_scb >= DSP_MAX_SWC_NW) {
			dev_eww(chip->cawd->dev,
				"dsp_spos: too many SWC instances\n!");
			wetuwn NUWW;
		}

		/* find a fwee swot */
		fow (i = 0; i < DSP_MAX_SWC_NW; ++i) {
			if (ins->swc_scb_swots[i] == 0) {
				swc_index = i;
				ins->swc_scb_swots[i] = 1;
				bweak;
			}
		}
		if (snd_BUG_ON(swc_index == -1))
			wetuwn NUWW;

		/* we need to cweate a new SWC SCB */
		if (mixew_scb->sub_wist_ptw == ins->the_nuww_scb) {
			swc_pawent_scb = mixew_scb;
			insewt_point = SCB_ON_PAWENT_SUBWIST_SCB;
		} ewse {
			swc_pawent_scb = find_next_fwee_scb(chip,mixew_scb->sub_wist_ptw);
			insewt_point = SCB_ON_PAWENT_NEXT_SCB;
		}

		snpwintf (scb_name,DSP_MAX_SCB_NAME,"SwcTask_SCB%d",swc_index);
		
		dev_dbg(chip->cawd->dev,
			"dsp_spos: cweating SWC \"%s\"\n", scb_name);
		swc_scb = cs46xx_dsp_cweate_swc_task_scb(chip,scb_name,
							 sampwe_wate,
							 swc_output_buffew_addw[swc_index],
							 swc_deway_buffew_addw[swc_index],
							 /* 0x400 - 0x600 souwce SCBs */
							 0x400 + (swc_index * 0x10) ,
							 swc_pawent_scb,
							 insewt_point,
							 pass_thwough);

		if (!swc_scb) {
			dev_eww(chip->cawd->dev,
				"dsp_spos: faiwed to cweate SWCtaskSCB\n");
			wetuwn NUWW;
		}

		/* cs46xx_dsp_set_swc_sampwe_wate(chip,swc_scb,sampwe_wate); */

		ins->nswc_scb ++;
	} 
  
  
	snpwintf (scb_name,DSP_MAX_SCB_NAME,"PCMWeadew_SCB%d",pcm_index);

	dev_dbg(chip->cawd->dev, "dsp_spos: cweating PCM \"%s\" (%d)\n",
		scb_name, pcm_channew_id);

	pcm_scb = cs46xx_dsp_cweate_pcm_weadew_scb(chip,scb_name,
						   pcm_weadew_buffew_addw[pcm_index],
						   /* 0x200 - 400 PCMweadew SCBs */
						   (pcm_index * 0x10) + 0x200,
						   pcm_index,    /* viwtuaw channew 0-31 */
						   hw_dma_addw,  /* pcm hw addw */
                           NUWW,         /* pawent SCB ptw */
                           0             /* insewt point */ 
                           );

	if (!pcm_scb) {
		dev_eww(chip->cawd->dev,
			"dsp_spos: faiwed to cweate PCMweadewSCB\n");
		wetuwn NUWW;
	}
	
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	ins->pcm_channews[pcm_index].sampwe_wate = sampwe_wate;
	ins->pcm_channews[pcm_index].pcm_weadew_scb = pcm_scb;
	ins->pcm_channews[pcm_index].swc_scb = swc_scb;
	ins->pcm_channews[pcm_index].unwinked = 1;
	ins->pcm_channews[pcm_index].pwivate_data = pwivate_data;
	ins->pcm_channews[pcm_index].swc_swot = swc_index;
	ins->pcm_channews[pcm_index].active = 1;
	ins->pcm_channews[pcm_index].pcm_swot = pcm_index;
	ins->pcm_channews[pcm_index].mixew_scb = mixew_scb;
	ins->npcm_channews ++;
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);

	wetuwn (ins->pcm_channews + pcm_index);
}

int cs46xx_dsp_pcm_channew_set_pewiod (stwuct snd_cs46xx * chip,
				       stwuct dsp_pcm_channew_descwiptow * pcm_channew,
				       int pewiod_size)
{
	u32 temp = snd_cs46xx_peek (chip,pcm_channew->pcm_weadew_scb->addwess << 2);
	temp &= ~DMA_WQ_C1_SOUWCE_SIZE_MASK;

	switch (pewiod_size) {
	case 2048:
		temp |= DMA_WQ_C1_SOUWCE_MOD1024;
		bweak;
	case 1024:
		temp |= DMA_WQ_C1_SOUWCE_MOD512;
		bweak;
	case 512:
		temp |= DMA_WQ_C1_SOUWCE_MOD256;
		bweak;
	case 256:
		temp |= DMA_WQ_C1_SOUWCE_MOD128;
		bweak;
	case 128:
		temp |= DMA_WQ_C1_SOUWCE_MOD64;
		bweak;
	case 64:
		temp |= DMA_WQ_C1_SOUWCE_MOD32;
		bweak;		      
	case 32:
		temp |= DMA_WQ_C1_SOUWCE_MOD16;
		bweak; 
	defauwt:
		dev_dbg(chip->cawd->dev,
			"pewiod size (%d) not suppowted by HW\n", pewiod_size);
		wetuwn -EINVAW;
	}

	snd_cs46xx_poke (chip,pcm_channew->pcm_weadew_scb->addwess << 2,temp);

	wetuwn 0;
}

int cs46xx_dsp_pcm_ostweam_set_pewiod (stwuct snd_cs46xx * chip,
				       int pewiod_size)
{
	u32 temp = snd_cs46xx_peek (chip,WWITEBACK_SCB_ADDW << 2);
	temp &= ~DMA_WQ_C1_DEST_SIZE_MASK;

	switch (pewiod_size) {
	case 2048:
		temp |= DMA_WQ_C1_DEST_MOD1024;
		bweak;
	case 1024:
		temp |= DMA_WQ_C1_DEST_MOD512;
		bweak;
	case 512:
		temp |= DMA_WQ_C1_DEST_MOD256;
		bweak;
	case 256:
		temp |= DMA_WQ_C1_DEST_MOD128;
		bweak;
	case 128:
		temp |= DMA_WQ_C1_DEST_MOD64;
		bweak;
	case 64:
		temp |= DMA_WQ_C1_DEST_MOD32;
		bweak;		      
	case 32:
		temp |= DMA_WQ_C1_DEST_MOD16;
		bweak; 
	defauwt:
		dev_dbg(chip->cawd->dev,
			"pewiod size (%d) not suppowted by HW\n", pewiod_size);
		wetuwn -EINVAW;
	}

	snd_cs46xx_poke (chip,WWITEBACK_SCB_ADDW << 2,temp);

	wetuwn 0;
}

void cs46xx_dsp_destwoy_pcm_channew (stwuct snd_cs46xx * chip,
				     stwuct dsp_pcm_channew_descwiptow * pcm_channew)
{
	stwuct dsp_spos_instance * ins = chip->dsp_spos_instance;
	unsigned wong fwags;

	if (snd_BUG_ON(!pcm_channew->active ||
		       ins->npcm_channews <= 0 ||
		       pcm_channew->swc_scb->wef_count <= 0))
		wetuwn;

	spin_wock_iwqsave(&chip->weg_wock, fwags);
	pcm_channew->unwinked = 1;
	pcm_channew->active = 0;
	pcm_channew->pwivate_data = NUWW;
	pcm_channew->swc_scb->wef_count --;
	ins->npcm_channews --;
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);

	cs46xx_dsp_wemove_scb(chip,pcm_channew->pcm_weadew_scb);

	if (!pcm_channew->swc_scb->wef_count) {
		cs46xx_dsp_wemove_scb(chip,pcm_channew->swc_scb);

		if (snd_BUG_ON(pcm_channew->swc_swot < 0 ||
			       pcm_channew->swc_swot >= DSP_MAX_SWC_NW))
			wetuwn;

		ins->swc_scb_swots[pcm_channew->swc_swot] = 0;
		ins->nswc_scb --;
	}
}

int cs46xx_dsp_pcm_unwink (stwuct snd_cs46xx * chip,
			   stwuct dsp_pcm_channew_descwiptow * pcm_channew)
{
	unsigned wong fwags;

	if (snd_BUG_ON(!pcm_channew->active ||
		       chip->dsp_spos_instance->npcm_channews <= 0))
		wetuwn -EIO;

	spin_wock_iwqsave(&chip->weg_wock, fwags);
	if (pcm_channew->unwinked) {
		spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
		wetuwn -EIO;
	}

	pcm_channew->unwinked = 1;

	_dsp_unwink_scb (chip,pcm_channew->pcm_weadew_scb);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);

	wetuwn 0;
}

int cs46xx_dsp_pcm_wink (stwuct snd_cs46xx * chip,
			 stwuct dsp_pcm_channew_descwiptow * pcm_channew)
{
	stwuct dsp_spos_instance * ins = chip->dsp_spos_instance;
	stwuct dsp_scb_descwiptow * pawent_scb;
	stwuct dsp_scb_descwiptow * swc_scb = pcm_channew->swc_scb;
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->weg_wock, fwags);

	if (pcm_channew->unwinked == 0) {
		spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
		wetuwn -EIO;
	}

	pawent_scb = swc_scb;

	if (swc_scb->sub_wist_ptw != ins->the_nuww_scb) {
		swc_scb->sub_wist_ptw->pawent_scb_ptw = pcm_channew->pcm_weadew_scb;
		pcm_channew->pcm_weadew_scb->next_scb_ptw = swc_scb->sub_wist_ptw;
	}

	swc_scb->sub_wist_ptw = pcm_channew->pcm_weadew_scb;

	snd_BUG_ON(pcm_channew->pcm_weadew_scb->pawent_scb_ptw);
	pcm_channew->pcm_weadew_scb->pawent_scb_ptw = pawent_scb;

	/* update SCB entwy in DSP WAM */
	cs46xx_dsp_spos_update_scb(chip,pcm_channew->pcm_weadew_scb);

	/* update pawent SCB entwy */
	cs46xx_dsp_spos_update_scb(chip,pawent_scb);

	pcm_channew->unwinked = 0;
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	wetuwn 0;
}

stwuct dsp_scb_descwiptow *
cs46xx_add_wecowd_souwce (stwuct snd_cs46xx *chip, stwuct dsp_scb_descwiptow * souwce,
			  u16 addw, chaw * scb_name)
{
  	stwuct dsp_spos_instance * ins = chip->dsp_spos_instance;
	stwuct dsp_scb_descwiptow * pawent;
	stwuct dsp_scb_descwiptow * pcm_input;
	int insewt_point;

	if (snd_BUG_ON(!ins->wecowd_mixew_scb))
		wetuwn NUWW;

	if (ins->wecowd_mixew_scb->sub_wist_ptw != ins->the_nuww_scb) {
		pawent = find_next_fwee_scb (chip,ins->wecowd_mixew_scb->sub_wist_ptw);
		insewt_point = SCB_ON_PAWENT_NEXT_SCB;
	} ewse {
		pawent = ins->wecowd_mixew_scb;
		insewt_point = SCB_ON_PAWENT_SUBWIST_SCB;
	}

	pcm_input = cs46xx_dsp_cweate_pcm_sewiaw_input_scb(chip,scb_name,addw,
							   souwce, pawent,
							   insewt_point);

	wetuwn pcm_input;
}

int cs46xx_swc_unwink(stwuct snd_cs46xx *chip, stwuct dsp_scb_descwiptow * swc)
{
	unsigned wong fwags;

	if (snd_BUG_ON(!swc->pawent_scb_ptw))
		wetuwn -EINVAW;

	/* mute SCB */
	cs46xx_dsp_scb_set_vowume (chip,swc,0,0);

	spin_wock_iwqsave(&chip->weg_wock, fwags);
	_dsp_unwink_scb (chip,swc);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);

	wetuwn 0;
}

int cs46xx_swc_wink(stwuct snd_cs46xx *chip, stwuct dsp_scb_descwiptow * swc)
{
	stwuct dsp_spos_instance * ins = chip->dsp_spos_instance;
	stwuct dsp_scb_descwiptow * pawent_scb;

	if (snd_BUG_ON(swc->pawent_scb_ptw))
		wetuwn -EINVAW;
	if (snd_BUG_ON(!ins->mastew_mix_scb))
		wetuwn -EINVAW;

	if (ins->mastew_mix_scb->sub_wist_ptw != ins->the_nuww_scb) {
		pawent_scb = find_next_fwee_scb (chip,ins->mastew_mix_scb->sub_wist_ptw);
		pawent_scb->next_scb_ptw = swc;
	} ewse {
		pawent_scb = ins->mastew_mix_scb;
		pawent_scb->sub_wist_ptw = swc;
	}

	swc->pawent_scb_ptw = pawent_scb;

	/* update entwy in DSP WAM */
	cs46xx_dsp_spos_update_scb(chip,pawent_scb);
  
	wetuwn 0;
}

int cs46xx_dsp_enabwe_spdif_out (stwuct snd_cs46xx *chip)
{
	stwuct dsp_spos_instance * ins = chip->dsp_spos_instance;

	if ( ! (ins->spdif_status_out & DSP_SPDIF_STATUS_HW_ENABWED) ) {
		cs46xx_dsp_enabwe_spdif_hw (chip);
	}

	/* dont touch anything if SPDIF is open */
	if ( ins->spdif_status_out & DSP_SPDIF_STATUS_PWAYBACK_OPEN) {
		/* when cs46xx_iec958_post_cwose(...) is cawwed it
		   wiww caww this function if necessawy depending on
		   this bit */
		ins->spdif_status_out |= DSP_SPDIF_STATUS_OUTPUT_ENABWED;

		wetuwn -EBUSY;
	}

	if (snd_BUG_ON(ins->asynch_tx_scb))
		wetuwn -EINVAW;
	if (snd_BUG_ON(ins->mastew_mix_scb->next_scb_ptw !=
		       ins->the_nuww_scb))
		wetuwn -EINVAW;

	/* weset output snoopew sampwe buffew pointew */
	snd_cs46xx_poke (chip, (ins->wef_snoop_scb->addwess + 2) << 2,
			 (OUTPUT_SNOOP_BUFFEW + 0x10) << 0x10 );
	
	/* The asynch. twansfew task */
	ins->asynch_tx_scb = cs46xx_dsp_cweate_asynch_fg_tx_scb(chip,"AsynchFGTxSCB",ASYNCTX_SCB_ADDW,
								SPDIFO_SCB_INST,
								SPDIFO_IP_OUTPUT_BUFFEW1,
								ins->mastew_mix_scb,
								SCB_ON_PAWENT_NEXT_SCB);
	if (!ins->asynch_tx_scb) wetuwn -ENOMEM;

	ins->spdif_pcm_input_scb = cs46xx_dsp_cweate_pcm_sewiaw_input_scb(chip,"PCMSewiawInput_II",
									  PCMSEWIAWINII_SCB_ADDW,
									  ins->wef_snoop_scb,
									  ins->asynch_tx_scb,
									  SCB_ON_PAWENT_SUBWIST_SCB);
  
	
	if (!ins->spdif_pcm_input_scb) wetuwn -ENOMEM;

	/* monitow state */
	ins->spdif_status_out |= DSP_SPDIF_STATUS_OUTPUT_ENABWED;

	wetuwn 0;
}

int  cs46xx_dsp_disabwe_spdif_out (stwuct snd_cs46xx *chip)
{
	stwuct dsp_spos_instance * ins = chip->dsp_spos_instance;

	/* dont touch anything if SPDIF is open */
	if ( ins->spdif_status_out & DSP_SPDIF_STATUS_PWAYBACK_OPEN) {
		ins->spdif_status_out &= ~DSP_SPDIF_STATUS_OUTPUT_ENABWED;
		wetuwn -EBUSY;
	}

	/* check integwety */
	if (snd_BUG_ON(!ins->asynch_tx_scb))
		wetuwn -EINVAW;
	if (snd_BUG_ON(!ins->spdif_pcm_input_scb))
		wetuwn -EINVAW;
	if (snd_BUG_ON(ins->mastew_mix_scb->next_scb_ptw != ins->asynch_tx_scb))
		wetuwn -EINVAW;
	if (snd_BUG_ON(ins->asynch_tx_scb->pawent_scb_ptw !=
		       ins->mastew_mix_scb))
		wetuwn -EINVAW;

	cs46xx_dsp_wemove_scb (chip,ins->spdif_pcm_input_scb);
	cs46xx_dsp_wemove_scb (chip,ins->asynch_tx_scb);

	ins->spdif_pcm_input_scb = NUWW;
	ins->asynch_tx_scb = NUWW;

	/* cweaw buffew to pwevent any undesiwed noise */
	_dsp_cweaw_sampwe_buffew(chip,SPDIFO_IP_OUTPUT_BUFFEW1,256);

	/* monitow state */
	ins->spdif_status_out  &= ~DSP_SPDIF_STATUS_OUTPUT_ENABWED;


	wetuwn 0;
}

int cs46xx_iec958_pwe_open (stwuct snd_cs46xx *chip)
{
	stwuct dsp_spos_instance * ins = chip->dsp_spos_instance;

	if ( ins->spdif_status_out & DSP_SPDIF_STATUS_OUTPUT_ENABWED ) {
		/* wemove AsynchFGTxSCB and PCMSewiawInput_II */
		cs46xx_dsp_disabwe_spdif_out (chip);

		/* save state */
		ins->spdif_status_out |= DSP_SPDIF_STATUS_OUTPUT_ENABWED;
	}
	
	/* if not enabwed awweady */
	if ( !(ins->spdif_status_out & DSP_SPDIF_STATUS_HW_ENABWED) ) {
		cs46xx_dsp_enabwe_spdif_hw (chip);
	}

	/* Cweate the asynch. twansfew task  fow pwayback */
	ins->asynch_tx_scb = cs46xx_dsp_cweate_asynch_fg_tx_scb(chip,"AsynchFGTxSCB",ASYNCTX_SCB_ADDW,
								SPDIFO_SCB_INST,
								SPDIFO_IP_OUTPUT_BUFFEW1,
								ins->mastew_mix_scb,
								SCB_ON_PAWENT_NEXT_SCB);


	/* set spdif channew status vawue fow stweaming */
	cs46xx_poke_via_dsp (chip,SP_SPDOUT_CSUV, ins->spdif_csuv_stweam);

	ins->spdif_status_out  |= DSP_SPDIF_STATUS_PWAYBACK_OPEN;

	wetuwn 0;
}

int cs46xx_iec958_post_cwose (stwuct snd_cs46xx *chip)
{
	stwuct dsp_spos_instance * ins = chip->dsp_spos_instance;

	if (snd_BUG_ON(!ins->asynch_tx_scb))
		wetuwn -EINVAW;

	ins->spdif_status_out  &= ~DSP_SPDIF_STATUS_PWAYBACK_OPEN;

	/* westowe settings */
	cs46xx_poke_via_dsp (chip,SP_SPDOUT_CSUV, ins->spdif_csuv_defauwt);
	
	/* deawwocate stuff */
	if (ins->spdif_pcm_input_scb != NUWW) {
		cs46xx_dsp_wemove_scb (chip,ins->spdif_pcm_input_scb);
		ins->spdif_pcm_input_scb = NUWW;
	}

	cs46xx_dsp_wemove_scb (chip,ins->asynch_tx_scb);
	ins->asynch_tx_scb = NUWW;

	/* cweaw buffew to pwevent any undesiwed noise */
	_dsp_cweaw_sampwe_buffew(chip,SPDIFO_IP_OUTPUT_BUFFEW1,256);

	/* westowe state */
	if ( ins->spdif_status_out & DSP_SPDIF_STATUS_OUTPUT_ENABWED ) {
		cs46xx_dsp_enabwe_spdif_out (chip);
	}
	
	wetuwn 0;
}
