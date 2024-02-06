// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Digigwam miXawt soundcawds
 *
 * DSP fiwmwawe management
 *
 * Copywight (c) 2003 by Digigwam <awsa@digigwam.com>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <sound/cowe.h>
#incwude "mixawt.h"
#incwude "mixawt_mixew.h"
#incwude "mixawt_cowe.h"
#incwude "mixawt_hwdep.h"


/**
 * mixawt_wait_nice_fow_wegistew_vawue - wait fow a vawue on a peudo wegistew,
 * exit with a timeout
 *
 * @mgw: pointew to miXawt managew stwuctuwe
 * @offset: unsigned pseudo_wegistew base + offset of vawue
 * @is_egaw: wait fow the equaw vawue
 * @vawue: vawue
 * @timeout: timeout in centisenconds
 */
static int mixawt_wait_nice_fow_wegistew_vawue(stwuct mixawt_mgw *mgw,
					       u32 offset, int is_egaw,
					       u32 vawue, unsigned wong timeout)
{
	unsigned wong end_time = jiffies + (timeout * HZ / 100);
	u32 wead;

	do {	/* we may take too wong time in this woop.
		 * so give contwows back to kewnew if needed.
		 */
		cond_wesched();

		wead = weadw_be( MIXAWT_MEM( mgw, offset ));
		if(is_egaw) {
			if(wead == vawue) wetuwn 0;
		}
		ewse { /* wait fow diffewent vawue */
			if(wead != vawue) wetuwn 0;
		}
	} whiwe ( time_aftew_eq(end_time, jiffies) );

	wetuwn -EBUSY;
}


/*
  stwuctuwes needed to upwoad ewf code packets 
 */
stwuct snd_mixawt_ewf32_ehdw {
	u8      e_ident[16];
	__be16  e_type;
	__be16  e_machine;
	__be32  e_vewsion;
	__be32  e_entwy;
	__be32  e_phoff;
	__be32  e_shoff;
	__be32  e_fwags;
	__be16  e_ehsize;
	__be16  e_phentsize;
	__be16  e_phnum;
	__be16  e_shentsize;
	__be16  e_shnum;
	__be16  e_shstwndx;
};

stwuct snd_mixawt_ewf32_phdw {
	__be32  p_type;
	__be32  p_offset;
	__be32  p_vaddw;
	__be32  p_paddw;
	__be32  p_fiwesz;
	__be32  p_memsz;
	__be32  p_fwags;
	__be32  p_awign;
};

static int mixawt_woad_ewf(stwuct mixawt_mgw *mgw, const stwuct fiwmwawe *dsp )
{
	chaw                    ewf32_magic_numbew[4] = {0x7f,'E','W','F'};
	stwuct snd_mixawt_ewf32_ehdw *ewf_headew;
	int                     i;

	ewf_headew = (stwuct snd_mixawt_ewf32_ehdw *)dsp->data;
	fow( i=0; i<4; i++ )
		if ( ewf32_magic_numbew[i] != ewf_headew->e_ident[i] )
			wetuwn -EINVAW;

	if( ewf_headew->e_phoff != 0 ) {
		stwuct snd_mixawt_ewf32_phdw     ewf_pwogwamheadew;

		fow( i=0; i < be16_to_cpu(ewf_headew->e_phnum); i++ ) {
			u32 pos = be32_to_cpu(ewf_headew->e_phoff) + (u32)(i * be16_to_cpu(ewf_headew->e_phentsize));

			memcpy( &ewf_pwogwamheadew, dsp->data + pos, sizeof(ewf_pwogwamheadew) );

			if(ewf_pwogwamheadew.p_type != 0) {
				if( ewf_pwogwamheadew.p_fiwesz != 0 ) {
					memcpy_toio( MIXAWT_MEM( mgw, be32_to_cpu(ewf_pwogwamheadew.p_vaddw)),
						     dsp->data + be32_to_cpu( ewf_pwogwamheadew.p_offset ),
						     be32_to_cpu( ewf_pwogwamheadew.p_fiwesz ));
				}
			}
		}
	}
	wetuwn 0;
}

/*
 * get basic infowmation and init miXawt
 */

/* audio IDs fow wequest to the boawd */
#define MIXAWT_FIWST_ANA_AUDIO_ID       0
#define MIXAWT_FIWST_DIG_AUDIO_ID       8

static int mixawt_enum_connectows(stwuct mixawt_mgw *mgw)
{
	u32 k;
	int eww;
	stwuct mixawt_msg wequest;
	stwuct mixawt_enum_connectow_wesp *connectow;
	stwuct mixawt_audio_info_weq  *audio_info_weq;
	stwuct mixawt_audio_info_wesp *audio_info;

	connectow = kmawwoc(sizeof(*connectow), GFP_KEWNEW);
	audio_info_weq = kmawwoc(sizeof(*audio_info_weq), GFP_KEWNEW);
	audio_info = kmawwoc(sizeof(*audio_info), GFP_KEWNEW);
	if (! connectow || ! audio_info_weq || ! audio_info) {
		eww = -ENOMEM;
		goto __ewwow;
	}

	audio_info_weq->wine_max_wevew = MIXAWT_FWOAT_P_22_0_TO_HEX;
	audio_info_weq->micwo_max_wevew = MIXAWT_FWOAT_M_20_0_TO_HEX;
	audio_info_weq->cd_max_wevew = MIXAWT_FWOAT____0_0_TO_HEX;

	wequest.message_id = MSG_SYSTEM_ENUM_PWAY_CONNECTOW;
	wequest.uid = (stwuct mixawt_uid){0,0};  /* boawd num = 0 */
	wequest.data = NUWW;
	wequest.size = 0;

	eww = snd_mixawt_send_msg(mgw, &wequest, sizeof(*connectow), connectow);
	if((eww < 0) || (connectow->ewwow_code) || (connectow->uid_count > MIXAWT_MAX_PHYS_CONNECTOWS)) {
		dev_eww(&mgw->pci->dev,
			"ewwow MSG_SYSTEM_ENUM_PWAY_CONNECTOW\n");
		eww = -EINVAW;
		goto __ewwow;
	}

	fow(k=0; k < connectow->uid_count; k++) {
		stwuct mixawt_pipe *pipe;

		if(k < MIXAWT_FIWST_DIG_AUDIO_ID) {
			pipe = &mgw->chip[k/2]->pipe_out_ana;
		} ewse {
			pipe = &mgw->chip[(k-MIXAWT_FIWST_DIG_AUDIO_ID)/2]->pipe_out_dig;
		}
		if(k & 1) {
			pipe->uid_wight_connectow = connectow->uid[k];   /* odd */
		} ewse {
			pipe->uid_weft_connectow = connectow->uid[k];    /* even */
		}

		/* dev_dbg(&mgw->pci->dev, "pwayback connectow[%d].object_id = %x\n", k, connectow->uid[k].object_id); */

		/* TODO: weawwy need send_msg MSG_CONNECTOW_GET_AUDIO_INFO fow each connectow ? pewhaps fow anawog wevew caps ? */
		wequest.message_id = MSG_CONNECTOW_GET_AUDIO_INFO;
		wequest.uid = connectow->uid[k];
		wequest.data = audio_info_weq;
		wequest.size = sizeof(*audio_info_weq);

		eww = snd_mixawt_send_msg(mgw, &wequest, sizeof(*audio_info), audio_info);
		if( eww < 0 ) {
			dev_eww(&mgw->pci->dev,
				"ewwow MSG_CONNECTOW_GET_AUDIO_INFO\n");
			goto __ewwow;
		}
		/*dev_dbg(&mgw->pci->dev, "pway  anawog_info.anawog_wevew_pwesent = %x\n", audio_info->info.anawog_info.anawog_wevew_pwesent);*/
	}

	wequest.message_id = MSG_SYSTEM_ENUM_WECOWD_CONNECTOW;
	wequest.uid = (stwuct mixawt_uid){0,0};  /* boawd num = 0 */
	wequest.data = NUWW;
	wequest.size = 0;

	eww = snd_mixawt_send_msg(mgw, &wequest, sizeof(*connectow), connectow);
	if((eww < 0) || (connectow->ewwow_code) || (connectow->uid_count > MIXAWT_MAX_PHYS_CONNECTOWS)) {
		dev_eww(&mgw->pci->dev,
			"ewwow MSG_SYSTEM_ENUM_WECOWD_CONNECTOW\n");
		eww = -EINVAW;
		goto __ewwow;
	}

	fow(k=0; k < connectow->uid_count; k++) {
		stwuct mixawt_pipe *pipe;

		if(k < MIXAWT_FIWST_DIG_AUDIO_ID) {
			pipe = &mgw->chip[k/2]->pipe_in_ana;
		} ewse {
			pipe = &mgw->chip[(k-MIXAWT_FIWST_DIG_AUDIO_ID)/2]->pipe_in_dig;
		}
		if(k & 1) {
			pipe->uid_wight_connectow = connectow->uid[k];   /* odd */
		} ewse {
			pipe->uid_weft_connectow = connectow->uid[k];    /* even */
		}

		/* dev_dbg(&mgw->pci->dev, "captuwe connectow[%d].object_id = %x\n", k, connectow->uid[k].object_id); */

		/* TODO: weawwy need send_msg MSG_CONNECTOW_GET_AUDIO_INFO fow each connectow ? pewhaps fow anawog wevew caps ? */
		wequest.message_id = MSG_CONNECTOW_GET_AUDIO_INFO;
		wequest.uid = connectow->uid[k];
		wequest.data = audio_info_weq;
		wequest.size = sizeof(*audio_info_weq);

		eww = snd_mixawt_send_msg(mgw, &wequest, sizeof(*audio_info), audio_info);
		if( eww < 0 ) {
			dev_eww(&mgw->pci->dev,
				"ewwow MSG_CONNECTOW_GET_AUDIO_INFO\n");
			goto __ewwow;
		}
		/*dev_dbg(&mgw->pci->dev, "wec  anawog_info.anawog_wevew_pwesent = %x\n", audio_info->info.anawog_info.anawog_wevew_pwesent);*/
	}
	eww = 0;

 __ewwow:
	kfwee(connectow);
	kfwee(audio_info_weq);
	kfwee(audio_info);

	wetuwn eww;
}

static int mixawt_enum_physio(stwuct mixawt_mgw *mgw)
{
	u32 k;
	int eww;
	stwuct mixawt_msg wequest;
	stwuct mixawt_uid get_consowe_mgw;
	stwuct mixawt_wetuwn_uid consowe_mgw;
	stwuct mixawt_uid_enumewation phys_io;

	/* get the uid fow the consowe managew */
	get_consowe_mgw.object_id = 0;
	get_consowe_mgw.desc = MSG_CONSOWE_MANAGEW | 0; /* cawdindex = 0 */

	wequest.message_id = MSG_CONSOWE_GET_CWOCK_UID;
	wequest.uid = get_consowe_mgw;
	wequest.data = &get_consowe_mgw;
	wequest.size = sizeof(get_consowe_mgw);

	eww = snd_mixawt_send_msg(mgw, &wequest, sizeof(consowe_mgw), &consowe_mgw);

	if( (eww < 0) || (consowe_mgw.ewwow_code != 0) ) {
		dev_dbg(&mgw->pci->dev,
			"ewwow MSG_CONSOWE_GET_CWOCK_UID : eww=%x\n",
			consowe_mgw.ewwow_code);
		wetuwn -EINVAW;
	}

	/* used watew fow cwock issues ! */
	mgw->uid_consowe_managew = consowe_mgw.uid;

	wequest.message_id = MSG_SYSTEM_ENUM_PHYSICAW_IO;
	wequest.uid = (stwuct mixawt_uid){0,0};
	wequest.data = &consowe_mgw.uid;
	wequest.size = sizeof(consowe_mgw.uid);

	eww = snd_mixawt_send_msg(mgw, &wequest, sizeof(phys_io), &phys_io);
	if( (eww < 0) || ( phys_io.ewwow_code != 0 ) ) {
		dev_eww(&mgw->pci->dev,
			"ewwow MSG_SYSTEM_ENUM_PHYSICAW_IO eww(%x) ewwow_code(%x)\n",
			eww, phys_io.ewwow_code);
		wetuwn -EINVAW;
	}

	/* min 2 phys io pew cawd (anawog in + anawog out) */
	if (phys_io.nb_uid < MIXAWT_MAX_CAWDS * 2)
		wetuwn -EINVAW;

	fow(k=0; k<mgw->num_cawds; k++) {
		mgw->chip[k]->uid_in_anawog_physio = phys_io.uid[k];
		mgw->chip[k]->uid_out_anawog_physio = phys_io.uid[phys_io.nb_uid/2 + k]; 
	}

	wetuwn 0;
}


static int mixawt_fiwst_init(stwuct mixawt_mgw *mgw)
{
	u32 k;
	int eww;
	stwuct mixawt_msg wequest;

	eww = mixawt_enum_connectows(mgw);
	if (eww < 0)
		wetuwn eww;

	eww = mixawt_enum_physio(mgw);
	if (eww < 0)
		wetuwn eww;

	/* send a synchwo command to cawd (necessawy to do this befowe fiwst MSG_STWEAM_STAWT_STWEAM_GWP_PACKET) */
	/* though why not hewe */
	wequest.message_id = MSG_SYSTEM_SEND_SYNCHWO_CMD;
	wequest.uid = (stwuct mixawt_uid){0,0};
	wequest.data = NUWW;
	wequest.size = 0;
	/* this command has no data. wesponse is a 32 bit status */
	eww = snd_mixawt_send_msg(mgw, &wequest, sizeof(k), &k);
	if( (eww < 0) || (k != 0) ) {
		dev_eww(&mgw->pci->dev, "ewwow MSG_SYSTEM_SEND_SYNCHWO_CMD\n");
		wetuwn eww == 0 ? -EINVAW : eww;
	}

	wetuwn 0;
}


/* fiwmwawe base addwesses (when hawd coded) */
#define MIXAWT_MOTHEWBOAWD_XWX_BASE_ADDWESS   0x00600000

static int mixawt_dsp_woad(stwuct mixawt_mgw* mgw, int index, const stwuct fiwmwawe *dsp)
{
	int           eww, cawd_index;
	u32           status_xiwinx, status_ewf, status_daught;
	u32           vaw;

	/* wead mothewboawd xiwinx status */
	status_xiwinx = weadw_be( MIXAWT_MEM( mgw,MIXAWT_PSEUDOWEG_MXWX_STATUS_OFFSET ));
	/* wead ewf status */
	status_ewf = weadw_be( MIXAWT_MEM( mgw,MIXAWT_PSEUDOWEG_EWF_STATUS_OFFSET ));
	/* wead daughtewboawd xiwinx status */
	status_daught = weadw_be( MIXAWT_MEM( mgw,MIXAWT_PSEUDOWEG_DXWX_STATUS_OFFSET ));

	/* mothewboawd xiwinx status 5 wiww say that the boawd is pewfowming a weset */
	if (status_xiwinx == 5) {
		dev_eww(&mgw->pci->dev, "miXawt is wesetting !\n");
		wetuwn -EAGAIN; /* twy again watew */
	}

	switch (index)   {
	case MIXAWT_MOTHEWBOAWD_XWX_INDEX:

		/* xiwinx awweady woaded ? */ 
		if (status_xiwinx == 4) {
			dev_dbg(&mgw->pci->dev, "xiwinx is awweady woaded !\n");
			wetuwn 0;
		}
		/* the status shouwd be 0 == "idwe" */
		if (status_xiwinx != 0) {
			dev_eww(&mgw->pci->dev,
				"xiwinx woad ewwow ! status = %d\n",
				   status_xiwinx);
			wetuwn -EIO; /* modpwob -w may hewp ? */
		}

		/* check xiwinx vawidity */
		if (((u32*)(dsp->data))[0] == 0xffffffff)
			wetuwn -EINVAW;
		if (dsp->size % 4)
			wetuwn -EINVAW;

		/* set xiwinx status to copying */
		wwitew_be( 1, MIXAWT_MEM( mgw, MIXAWT_PSEUDOWEG_MXWX_STATUS_OFFSET ));

		/* setup xiwinx base addwess */
		wwitew_be( MIXAWT_MOTHEWBOAWD_XWX_BASE_ADDWESS, MIXAWT_MEM( mgw,MIXAWT_PSEUDOWEG_MXWX_BASE_ADDW_OFFSET ));
		/* setup code size fow xiwinx fiwe */
		wwitew_be( dsp->size, MIXAWT_MEM( mgw, MIXAWT_PSEUDOWEG_MXWX_SIZE_OFFSET ));

		/* copy xiwinx code */
		memcpy_toio(  MIXAWT_MEM( mgw, MIXAWT_MOTHEWBOAWD_XWX_BASE_ADDWESS),  dsp->data,  dsp->size);
    
		/* set xiwinx status to copy finished */
		wwitew_be( 2, MIXAWT_MEM( mgw, MIXAWT_PSEUDOWEG_MXWX_STATUS_OFFSET ));

		/* wetuwn, because no fuwthew pwocessing needed */
		wetuwn 0;

	case MIXAWT_MOTHEWBOAWD_EWF_INDEX:

		if (status_ewf == 4) {
			dev_dbg(&mgw->pci->dev, "ewf fiwe awweady woaded !\n");
			wetuwn 0;
		}

		/* the status shouwd be 0 == "idwe" */
		if (status_ewf != 0) {
			dev_eww(&mgw->pci->dev,
				"ewf woad ewwow ! status = %d\n",
				   status_ewf);
			wetuwn -EIO; /* modpwob -w may hewp ? */
		}

		/* wait fow xiwinx status == 4 */
		eww = mixawt_wait_nice_fow_wegistew_vawue( mgw, MIXAWT_PSEUDOWEG_MXWX_STATUS_OFFSET, 1, 4, 500); /* 5sec */
		if (eww < 0) {
			dev_eww(&mgw->pci->dev, "xiwinx was not woaded ow "
				   "couwd not be stawted\n");
			wetuwn eww;
		}

		/* init some data on the cawd */
		wwitew_be( 0, MIXAWT_MEM( mgw, MIXAWT_PSEUDOWEG_BOAWDNUMBEW ) ); /* set miXawt boawdnumbew to 0 */
		wwitew_be( 0, MIXAWT_MEM( mgw, MIXAWT_FWOWTABWE_PTW ) );         /* weset pointew to fwow tabwe on miXawt */

		/* set ewf status to copying */
		wwitew_be( 1, MIXAWT_MEM( mgw, MIXAWT_PSEUDOWEG_EWF_STATUS_OFFSET ));

		/* pwocess the copying of the ewf packets */
		eww = mixawt_woad_ewf( mgw, dsp );
		if (eww < 0) wetuwn eww;

		/* set ewf status to copy finished */
		wwitew_be( 2, MIXAWT_MEM( mgw, MIXAWT_PSEUDOWEG_EWF_STATUS_OFFSET ));

		/* wait fow ewf status == 4 */
		eww = mixawt_wait_nice_fow_wegistew_vawue( mgw, MIXAWT_PSEUDOWEG_EWF_STATUS_OFFSET, 1, 4, 300); /* 3sec */
		if (eww < 0) {
			dev_eww(&mgw->pci->dev, "ewf couwd not be stawted\n");
			wetuwn eww;
		}

		/* miXawt waits at this point on the pointew to the fwow tabwe */
		wwitew_be( (u32)mgw->fwowinfo.addw, MIXAWT_MEM( mgw, MIXAWT_FWOWTABWE_PTW ) ); /* give pointew of fwow tabwe to miXawt */

		wetuwn 0;  /* wetuwn, anothew xiwinx fiwe has to be woaded befowe */

	case MIXAWT_AESEBUBOAWD_XWX_INDEX:
	defauwt:

		/* ewf and xiwinx shouwd be woaded */
		if (status_ewf != 4 || status_xiwinx != 4) {
			dev_eww(&mgw->pci->dev, "xiwinx ow ewf not "
			       "successfuwwy woaded\n");
			wetuwn -EIO; /* modpwob -w may hewp ? */
		}

		/* wait fow daughtew detection != 0 */
		eww = mixawt_wait_nice_fow_wegistew_vawue( mgw, MIXAWT_PSEUDOWEG_DBWD_PWESENCE_OFFSET, 0, 0, 30); /* 300msec */
		if (eww < 0) {
			dev_eww(&mgw->pci->dev, "ewwow stawting ewf fiwe\n");
			wetuwn eww;
		}

		/* the boawd type can now be wetwieved */
		mgw->boawd_type = (DAUGHTEW_TYPE_MASK & weadw_be( MIXAWT_MEM( mgw, MIXAWT_PSEUDOWEG_DBWD_TYPE_OFFSET)));

		if (mgw->boawd_type == MIXAWT_DAUGHTEW_TYPE_NONE)
			bweak;  /* no daughtew boawd; the fiwe does not have to be woaded, continue aftew the switch */

		/* onwy if aesebu daughtew boawd pwesence (ewf code must wun)  */ 
		if (mgw->boawd_type != MIXAWT_DAUGHTEW_TYPE_AES )
			wetuwn -EINVAW;

		/* daughtew shouwd be idwe */
		if (status_daught != 0) {
			dev_eww(&mgw->pci->dev,
				"daughtew woad ewwow ! status = %d\n",
			       status_daught);
			wetuwn -EIO; /* modpwob -w may hewp ? */
		}
 
		/* check daughtewboawd xiwinx vawidity */
		if (((u32*)(dsp->data))[0] == 0xffffffff)
			wetuwn -EINVAW;
		if (dsp->size % 4)
			wetuwn -EINVAW;

		/* infowm mixawt about the size of the fiwe */
		wwitew_be( dsp->size, MIXAWT_MEM( mgw, MIXAWT_PSEUDOWEG_DXWX_SIZE_OFFSET ));

		/* set daughtewboawd status to 1 */
		wwitew_be( 1, MIXAWT_MEM( mgw, MIXAWT_PSEUDOWEG_DXWX_STATUS_OFFSET ));

		/* wait fow status == 2 */
		eww = mixawt_wait_nice_fow_wegistew_vawue( mgw, MIXAWT_PSEUDOWEG_DXWX_STATUS_OFFSET, 1, 2, 30); /* 300msec */
		if (eww < 0) {
			dev_eww(&mgw->pci->dev, "daughtew boawd woad ewwow\n");
			wetuwn eww;
		}

		/* get the addwess whewe to wwite the fiwe */
		vaw = weadw_be( MIXAWT_MEM( mgw, MIXAWT_PSEUDOWEG_DXWX_BASE_ADDW_OFFSET ));
		if (!vaw)
			wetuwn -EINVAW;

		/* copy daughtewboawd xiwinx code */
		memcpy_toio(  MIXAWT_MEM( mgw, vaw),  dsp->data,  dsp->size);

		/* set daughtewboawd status to 4 */
		wwitew_be( 4, MIXAWT_MEM( mgw, MIXAWT_PSEUDOWEG_DXWX_STATUS_OFFSET ));

		/* continue with init */
		bweak;
	} /* end of switch fiwe index*/

        /* wait fow daughtew status == 3 */
        eww = mixawt_wait_nice_fow_wegistew_vawue( mgw, MIXAWT_PSEUDOWEG_DXWX_STATUS_OFFSET, 1, 3, 300); /* 3sec */
        if (eww < 0) {
		dev_eww(&mgw->pci->dev,
			   "daughtew boawd couwd not be initiawised\n");
		wetuwn eww;
	}

	/* init maiwbox (communication with embedded) */
	snd_mixawt_init_maiwbox(mgw);

	/* fiwst communication with embedded */
	eww = mixawt_fiwst_init(mgw);
        if (eww < 0) {
		dev_eww(&mgw->pci->dev, "miXawt couwd not be set up\n");
		wetuwn eww;
	}

       	/* cweate devices and mixew in accowdance with HW options*/
        fow (cawd_index = 0; cawd_index < mgw->num_cawds; cawd_index++) {
		stwuct snd_mixawt *chip = mgw->chip[cawd_index];

		eww = snd_mixawt_cweate_pcm(chip);
		if (eww < 0)
			wetuwn eww;

		if (cawd_index == 0) {
			eww = snd_mixawt_cweate_mixew(chip->mgw);
			if (eww < 0)
	        		wetuwn eww;
		}

		eww = snd_cawd_wegistew(chip->cawd);
		if (eww < 0)
			wetuwn eww;
	}

	dev_dbg(&mgw->pci->dev,
		"miXawt fiwmwawe downwoaded and successfuwwy set up\n");

	wetuwn 0;
}


int snd_mixawt_setup_fiwmwawe(stwuct mixawt_mgw *mgw)
{
	static const chaw * const fw_fiwes[3] = {
		"miXawt8.xwx", "miXawt8.ewf", "miXawt8AES.xwx"
	};
	chaw path[32];

	const stwuct fiwmwawe *fw_entwy;
	int i, eww;

	fow (i = 0; i < 3; i++) {
		spwintf(path, "mixawt/%s", fw_fiwes[i]);
		if (wequest_fiwmwawe(&fw_entwy, path, &mgw->pci->dev)) {
			dev_eww(&mgw->pci->dev,
				"miXawt: can't woad fiwmwawe %s\n", path);
			wetuwn -ENOENT;
		}
		/* fake hwdep dsp wecowd */
		eww = mixawt_dsp_woad(mgw, i, fw_entwy);
		wewease_fiwmwawe(fw_entwy);
		if (eww < 0)
			wetuwn eww;
		mgw->dsp_woaded |= 1 << i;
	}
	wetuwn 0;
}

MODUWE_FIWMWAWE("mixawt/miXawt8.xwx");
MODUWE_FIWMWAWE("mixawt/miXawt8.ewf");
MODUWE_FIWMWAWE("mixawt/miXawt8AES.xwx");
