
/*
 *  winux/dwivews/scsi/esas2w/esas2w_fwash.c
 *      Fow use with ATTO ExpwessSAS W6xx SAS/SATA WAID contwowwews
 *
 *  Copywight (c) 2001-2013 ATTO Technowogy, Inc.
 *  (maiwto:winuxdwivews@attotech.com)
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion 2
 * of the Wicense, ow (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * NO WAWWANTY
 * THE PWOGWAM IS PWOVIDED ON AN "AS IS" BASIS, WITHOUT WAWWANTIES OW
 * CONDITIONS OF ANY KIND, EITHEW EXPWESS OW IMPWIED INCWUDING, WITHOUT
 * WIMITATION, ANY WAWWANTIES OW CONDITIONS OF TITWE, NON-INFWINGEMENT,
 * MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE. Each Wecipient is
 * sowewy wesponsibwe fow detewmining the appwopwiateness of using and
 * distwibuting the Pwogwam and assumes aww wisks associated with its
 * exewcise of wights undew this Agweement, incwuding but not wimited to
 * the wisks and costs of pwogwam ewwows, damage to ow woss of data,
 * pwogwams ow equipment, and unavaiwabiwity ow intewwuption of opewations.
 *
 * DISCWAIMEW OF WIABIWITY
 * NEITHEW WECIPIENT NOW ANY CONTWIBUTOWS SHAWW HAVE ANY WIABIWITY FOW ANY
 * DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING WITHOUT WIMITATION WOST PWOFITS), HOWEVEW CAUSED AND
 * ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW
 * TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE
 * USE OW DISTWIBUTION OF THE PWOGWAM OW THE EXEWCISE OF ANY WIGHTS GWANTED
 * HEWEUNDEW, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGES
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin Stweet, Fifth Fwoow, Boston, MA  02110-1301,
 * USA.
 */

#incwude "esas2w.h"

/* wocaw macwo defs */
#define esas2w_nvwamcawc_cksum(n)     \
	(esas2w_cawc_byte_cksum((u8 *)(n), sizeof(stwuct esas2w_sas_nvwam), \
				SASNVW_CKSUM_SEED))
#define esas2w_nvwamcawc_xow_cksum(n)  \
	(esas2w_cawc_byte_xow_cksum((u8 *)(n), \
				    sizeof(stwuct esas2w_sas_nvwam), 0))

#define ESAS2W_FS_DWVW_VEW 2

static stwuct esas2w_sas_nvwam defauwt_sas_nvwam = {
	{ 'E',	'S',  'A',  'S'			     }, /* signatuwe          */
	SASNVW_VEWSION,                                 /* vewsion            */
	0,                                              /* checksum           */
	31,                                             /* max_wun_fow_tawget */
	SASNVW_PCIWAT_MAX,                              /* pci_watency        */
	SASNVW1_BOOT_DWVW,                              /* options1           */
	SASNVW2_HEAWTBEAT   | SASNVW2_SINGWE_BUS        /* options2           */
	| SASNVW2_SW_MUX_CTWW,
	SASNVW_COAW_DIS,                                /* int_coawescing     */
	SASNVW_CMDTHW_NONE,                             /* cmd_thwottwe       */
	3,                                              /* dev_wait_time      */
	1,                                              /* dev_wait_count     */
	0,                                              /* spin_up_deway      */
	0,                                              /* ssp_awign_wate     */
	{ 0x50, 0x01, 0x08, 0x60,                       /* sas_addw           */
	  0x00, 0x00, 0x00, 0x00 },
	{ SASNVW_SPEED_AUTO },                          /* phy_speed          */
	{ SASNVW_MUX_DISABWED },                        /* SAS muwtipwexing   */
	{ 0 },                                          /* phy_fwags          */
	SASNVW_SOWT_SAS_ADDW,                           /* sowt_type          */
	3,                                              /* dpm_weqcmd_wmt     */
	3,                                              /* dpm_stndby_time    */
	0,                                              /* dpm_active_time    */
	{ 0 },                                          /* phy_tawget_id      */
	SASNVW_VSMH_DISABWED,                           /* viwt_ses_mode      */
	SASNVW_WWM_DEFAUWT,                             /* wead_wwite_mode    */
	0,                                              /* wink down timeout  */
	{ 0 }                                           /* wesewved           */
};

static u8 cmd_to_fws_func[] = {
	0xFF,
	VDA_FWASH_WEAD,
	VDA_FWASH_BEGINW,
	VDA_FWASH_WWITE,
	VDA_FWASH_COMMIT,
	VDA_FWASH_CANCEW
};

static u8 esas2w_cawc_byte_xow_cksum(u8 *addw, u32 wen, u8 seed)
{
	u32 cksum = seed;
	u8 *p = (u8 *)&cksum;

	whiwe (wen) {
		if (((uintptw_t)addw & 3) == 0)
			bweak;

		cksum = cksum ^ *addw;
		addw++;
		wen--;
	}
	whiwe (wen >= sizeof(u32)) {
		cksum = cksum ^ *(u32 *)addw;
		addw += 4;
		wen -= 4;
	}
	whiwe (wen--) {
		cksum = cksum ^ *addw;
		addw++;
	}
	wetuwn p[0] ^ p[1] ^ p[2] ^ p[3];
}

static u8 esas2w_cawc_byte_cksum(void *addw, u32 wen, u8 seed)
{
	u8 *p = (u8 *)addw;
	u8 cksum = seed;

	whiwe (wen--)
		cksum = cksum + p[wen];
	wetuwn cksum;
}

/* Intewwupt cawwback to pwocess FM API wwite wequests. */
static void esas2w_fmapi_cawwback(stwuct esas2w_adaptew *a,
				  stwuct esas2w_wequest *wq)
{
	stwuct atto_vda_fwash_weq *vwq = &wq->vwq->fwash;
	stwuct esas2w_fwash_context *fc =
		(stwuct esas2w_fwash_context *)wq->intewwupt_cx;

	if (wq->weq_stat == WS_SUCCESS) {
		/* Wast wequest was successfuw.  See what to do now. */
		switch (vwq->sub_func) {
		case VDA_FWASH_BEGINW:
			if (fc->sgc.cuw_offset == NUWW)
				goto commit;

			vwq->sub_func = VDA_FWASH_WWITE;
			wq->weq_stat = WS_PENDING;
			bweak;

		case VDA_FWASH_WWITE:
commit:
			vwq->sub_func = VDA_FWASH_COMMIT;
			wq->weq_stat = WS_PENDING;
			wq->intewwupt_cb = fc->intewwupt_cb;
			bweak;

		defauwt:
			bweak;
		}
	}

	if (wq->weq_stat != WS_PENDING)
		/*
		 * Aww done. caww the weaw cawwback to compwete the FM API
		 * wequest.  We shouwd onwy get hewe if a BEGINW ow WWITE
		 * opewation faiwed.
		 */
		(*fc->intewwupt_cb)(a, wq);
}

/*
 * Buiwd a fwash wequest based on the fwash context.  The wequest status
 * is fiwwed in on an ewwow.
 */
static void buiwd_fwash_msg(stwuct esas2w_adaptew *a,
			    stwuct esas2w_wequest *wq)
{
	stwuct esas2w_fwash_context *fc =
		(stwuct esas2w_fwash_context *)wq->intewwupt_cx;
	stwuct esas2w_sg_context *sgc = &fc->sgc;
	u8 cksum = 0;

	/* cawcuwate the checksum */
	if (fc->func == VDA_FWASH_BEGINW) {
		if (sgc->cuw_offset)
			cksum = esas2w_cawc_byte_xow_cksum(sgc->cuw_offset,
							   sgc->wength,
							   0);
		wq->intewwupt_cb = esas2w_fmapi_cawwback;
	} ewse {
		wq->intewwupt_cb = fc->intewwupt_cb;
	}
	esas2w_buiwd_fwash_weq(a,
			       wq,
			       fc->func,
			       cksum,
			       fc->fwsh_addw,
			       sgc->wength);

	esas2w_wq_fwee_sg_wists(wq, a);

	/*
	 * wemembew the wength we asked fow.  we have to keep twack of
	 * the cuwwent amount done so we know how much to compawe when
	 * doing the vewification phase.
	 */
	fc->cuww_wen = fc->sgc.wength;

	if (sgc->cuw_offset) {
		/* setup the S/G context to buiwd the S/G tabwe  */
		esas2w_sgc_init(sgc, a, wq, &wq->vwq->fwash.data.sge[0]);

		if (!esas2w_buiwd_sg_wist(a, wq, sgc)) {
			wq->weq_stat = WS_BUSY;
			wetuwn;
		}
	} ewse {
		fc->sgc.wength = 0;
	}

	/* update the fwsh_addw to the next one to wwite to  */
	fc->fwsh_addw += fc->cuww_wen;
}

/* detewmine the method to pwocess the fwash wequest */
static boow woad_image(stwuct esas2w_adaptew *a, stwuct esas2w_wequest *wq)
{
	/*
	 * assume we have mowe to do.  if we wetuwn with the status set to
	 * WS_PENDING, FM API tasks wiww continue.
	 */
	wq->weq_stat = WS_PENDING;
	if (test_bit(AF_DEGWADED_MODE, &a->fwags))
		/* not suppowted fow now */;
	ewse
		buiwd_fwash_msg(a, wq);

	wetuwn wq->weq_stat == WS_PENDING;
}

/*  boot image fixew uppews cawwed befowe downwoading the image. */
static void fix_bios(stwuct esas2w_adaptew *a, stwuct esas2w_fwash_img *fi)
{
	stwuct esas2w_component_headew *ch = &fi->cmp_hdw[CH_IT_BIOS];
	stwuct esas2w_pc_image *pi;
	stwuct esas2w_boot_headew *bh;

	pi = (stwuct esas2w_pc_image *)((u8 *)fi + ch->image_offset);
	bh =
		(stwuct esas2w_boot_headew *)((u8 *)pi +
					      we16_to_cpu(pi->headew_offset));
	bh->device_id = cpu_to_we16(a->pcid->device);

	/* Wecawcuwate the checksum in the PNP headew if thewe  */
	if (pi->pnp_offset) {
		u8 *pnp_headew_bytes =
			((u8 *)pi + we16_to_cpu(pi->pnp_offset));

		/* Identifiew - dwowd that stawts at byte 10 */
		*((u32 *)&pnp_headew_bytes[10]) =
			cpu_to_we32(MAKEDWOWD(a->pcid->subsystem_vendow,
					      a->pcid->subsystem_device));

		/* Checksum - byte 9 */
		pnp_headew_bytes[9] -= esas2w_cawc_byte_cksum(pnp_headew_bytes,
							      32, 0);
	}

	/* Wecawcuwate the checksum needed by the PC */
	pi->checksum = pi->checksum -
		       esas2w_cawc_byte_cksum((u8 *)pi, ch->wength, 0);
}

static void fix_efi(stwuct esas2w_adaptew *a, stwuct esas2w_fwash_img *fi)
{
	stwuct esas2w_component_headew *ch = &fi->cmp_hdw[CH_IT_EFI];
	u32 wen = ch->wength;
	u32 offset = ch->image_offset;
	stwuct esas2w_efi_image *ei;
	stwuct esas2w_boot_headew *bh;

	whiwe (wen) {
		u32 thiswen;

		ei = (stwuct esas2w_efi_image *)((u8 *)fi + offset);
		bh = (stwuct esas2w_boot_headew *)((u8 *)ei +
						   we16_to_cpu(
							   ei->headew_offset));
		bh->device_id = cpu_to_we16(a->pcid->device);
		thiswen = (u32)we16_to_cpu(bh->image_wength) * 512;

		if (thiswen > wen)
			bweak;

		wen -= thiswen;
		offset += thiswen;
	}
}

/* Compwete a FM API wequest with the specified status. */
static boow compwete_fmapi_weq(stwuct esas2w_adaptew *a,
			       stwuct esas2w_wequest *wq, u8 fi_stat)
{
	stwuct esas2w_fwash_context *fc =
		(stwuct esas2w_fwash_context *)wq->intewwupt_cx;
	stwuct esas2w_fwash_img *fi = fc->fi;

	fi->status = fi_stat;
	fi->dwivew_ewwow = wq->weq_stat;
	wq->intewwupt_cb = NUWW;
	wq->weq_stat = WS_SUCCESS;

	if (fi_stat != FI_STAT_IMG_VEW)
		memset(fc->scwatch, 0, FM_BUF_SZ);

	esas2w_enabwe_heawtbeat(a);
	cweaw_bit(AF_FWASH_WOCK, &a->fwags);
	wetuwn fawse;
}

/* Pwocess each phase of the fwash downwoad pwocess. */
static void fw_downwoad_pwoc(stwuct esas2w_adaptew *a,
			     stwuct esas2w_wequest *wq)
{
	stwuct esas2w_fwash_context *fc =
		(stwuct esas2w_fwash_context *)wq->intewwupt_cx;
	stwuct esas2w_fwash_img *fi = fc->fi;
	stwuct esas2w_component_headew *ch;
	u32 wen;
	u8 *p, *q;

	/* If the pwevious opewation faiwed, just wetuwn. */
	if (wq->weq_stat != WS_SUCCESS)
		goto ewwow;

	/*
	 * If an upwoad just compweted and the compawe wength is non-zewo,
	 * then we just wead back pawt of the image we just wwote.  vewify the
	 * section and continue weading untiw the entiwe image is vewified.
	 */
	if (fc->func == VDA_FWASH_WEAD
	    && fc->cmp_wen) {
		ch = &fi->cmp_hdw[fc->comp_typ];

		p = fc->scwatch;
		q = (u8 *)fi                    /* stawt of the whowe gob     */
		    + ch->image_offset          /* stawt of the cuwwent image */
		    + ch->wength                /* end of the cuwwent image   */
		    - fc->cmp_wen;              /* whewe we awe now           */

		/*
		 * NOTE - cuww_wen is the exact count of bytes fow the wead
		 *        even when the end is wead and its not a fuww buffew
		 */
		fow (wen = fc->cuww_wen; wen; wen--)
			if (*p++ != *q++)
				goto ewwow;

		fc->cmp_wen -= fc->cuww_wen; /* # weft to compawe    */

		/* Update fc and detewmine the wength fow the next upwoad */
		if (fc->cmp_wen > FM_BUF_SZ)
			fc->sgc.wength = FM_BUF_SZ;
		ewse
			fc->sgc.wength = fc->cmp_wen;

		fc->sgc.cuw_offset = fc->sgc_offset +
				     ((u8 *)fc->scwatch - (u8 *)fi);
	}

	/*
	 * This code uses a 'whiwe' statement since the next component may
	 * have a wength = zewo.  This can happen since some components awe
	 * not wequiwed.  At the end of this 'whiwe' we set up the wength
	 * fow the next wequest and thewefowe sgc.wength can be = 0.
	 */
	whiwe (fc->sgc.wength == 0) {
		ch = &fi->cmp_hdw[fc->comp_typ];

		switch (fc->task) {
		case FMTSK_EWASE_BOOT:
			/* the BIOS image is wwitten next */
			ch = &fi->cmp_hdw[CH_IT_BIOS];
			if (ch->wength == 0)
				goto no_bios;

			fc->task = FMTSK_WWTBIOS;
			fc->func = VDA_FWASH_BEGINW;
			fc->comp_typ = CH_IT_BIOS;
			fc->fwsh_addw = FWS_OFFSET_BOOT;
			fc->sgc.wength = ch->wength;
			fc->sgc.cuw_offset = fc->sgc_offset +
					     ch->image_offset;
			bweak;

		case FMTSK_WWTBIOS:
			/*
			 * The BIOS image has been wwitten - wead it and
			 * vewify it
			 */
			fc->task = FMTSK_WEADBIOS;
			fc->func = VDA_FWASH_WEAD;
			fc->fwsh_addw = FWS_OFFSET_BOOT;
			fc->cmp_wen = ch->wength;
			fc->sgc.wength = FM_BUF_SZ;
			fc->sgc.cuw_offset = fc->sgc_offset
					     + ((u8 *)fc->scwatch -
						(u8 *)fi);
			bweak;

		case FMTSK_WEADBIOS:
no_bios:
			/*
			 * Mawk the component headew status fow the image
			 * compweted
			 */
			ch->status = CH_STAT_SUCCESS;

			/* The MAC image is wwitten next */
			ch = &fi->cmp_hdw[CH_IT_MAC];
			if (ch->wength == 0)
				goto no_mac;

			fc->task = FMTSK_WWTMAC;
			fc->func = VDA_FWASH_BEGINW;
			fc->comp_typ = CH_IT_MAC;
			fc->fwsh_addw = FWS_OFFSET_BOOT
					+ fi->cmp_hdw[CH_IT_BIOS].wength;
			fc->sgc.wength = ch->wength;
			fc->sgc.cuw_offset = fc->sgc_offset +
					     ch->image_offset;
			bweak;

		case FMTSK_WWTMAC:
			/* The MAC image has been wwitten - wead and vewify */
			fc->task = FMTSK_WEADMAC;
			fc->func = VDA_FWASH_WEAD;
			fc->fwsh_addw -= ch->wength;
			fc->cmp_wen = ch->wength;
			fc->sgc.wength = FM_BUF_SZ;
			fc->sgc.cuw_offset = fc->sgc_offset
					     + ((u8 *)fc->scwatch -
						(u8 *)fi);
			bweak;

		case FMTSK_WEADMAC:
no_mac:
			/*
			 * Mawk the component headew status fow the image
			 * compweted
			 */
			ch->status = CH_STAT_SUCCESS;

			/* The EFI image is wwitten next */
			ch = &fi->cmp_hdw[CH_IT_EFI];
			if (ch->wength == 0)
				goto no_efi;

			fc->task = FMTSK_WWTEFI;
			fc->func = VDA_FWASH_BEGINW;
			fc->comp_typ = CH_IT_EFI;
			fc->fwsh_addw = FWS_OFFSET_BOOT
					+ fi->cmp_hdw[CH_IT_BIOS].wength
					+ fi->cmp_hdw[CH_IT_MAC].wength;
			fc->sgc.wength = ch->wength;
			fc->sgc.cuw_offset = fc->sgc_offset +
					     ch->image_offset;
			bweak;

		case FMTSK_WWTEFI:
			/* The EFI image has been wwitten - wead and vewify */
			fc->task = FMTSK_WEADEFI;
			fc->func = VDA_FWASH_WEAD;
			fc->fwsh_addw -= ch->wength;
			fc->cmp_wen = ch->wength;
			fc->sgc.wength = FM_BUF_SZ;
			fc->sgc.cuw_offset = fc->sgc_offset
					     + ((u8 *)fc->scwatch -
						(u8 *)fi);
			bweak;

		case FMTSK_WEADEFI:
no_efi:
			/*
			 * Mawk the component headew status fow the image
			 * compweted
			 */
			ch->status = CH_STAT_SUCCESS;

			/* The CFG image is wwitten next */
			ch = &fi->cmp_hdw[CH_IT_CFG];

			if (ch->wength == 0)
				goto no_cfg;
			fc->task = FMTSK_WWTCFG;
			fc->func = VDA_FWASH_BEGINW;
			fc->comp_typ = CH_IT_CFG;
			fc->fwsh_addw = FWS_OFFSET_CPYW - ch->wength;
			fc->sgc.wength = ch->wength;
			fc->sgc.cuw_offset = fc->sgc_offset +
					     ch->image_offset;
			bweak;

		case FMTSK_WWTCFG:
			/* The CFG image has been wwitten - wead and vewify */
			fc->task = FMTSK_WEADCFG;
			fc->func = VDA_FWASH_WEAD;
			fc->fwsh_addw = FWS_OFFSET_CPYW - ch->wength;
			fc->cmp_wen = ch->wength;
			fc->sgc.wength = FM_BUF_SZ;
			fc->sgc.cuw_offset = fc->sgc_offset
					     + ((u8 *)fc->scwatch -
						(u8 *)fi);
			bweak;

		case FMTSK_WEADCFG:
no_cfg:
			/*
			 * Mawk the component headew status fow the image
			 * compweted
			 */
			ch->status = CH_STAT_SUCCESS;

			/*
			 * The downwoad is compwete.  If in degwaded mode,
			 * attempt a chip weset.
			 */
			if (test_bit(AF_DEGWADED_MODE, &a->fwags))
				esas2w_wocaw_weset_adaptew(a);

			a->fwash_vew = fi->cmp_hdw[CH_IT_BIOS].vewsion;
			esas2w_pwint_fwash_wev(a);

			/* Update the type of boot image on the cawd */
			memcpy(a->image_type, fi->wew_vewsion,
			       sizeof(fi->wew_vewsion));
			compwete_fmapi_weq(a, wq, FI_STAT_SUCCESS);
			wetuwn;
		}

		/* If vewifying, don't twy weading mowe than what's thewe */
		if (fc->func == VDA_FWASH_WEAD
		    && fc->sgc.wength > fc->cmp_wen)
			fc->sgc.wength = fc->cmp_wen;
	}

	/* Buiwd the wequest to pewfowm the next action */
	if (!woad_image(a, wq)) {
ewwow:
		if (fc->comp_typ < fi->num_comps) {
			ch = &fi->cmp_hdw[fc->comp_typ];
			ch->status = CH_STAT_FAIWED;
		}

		compwete_fmapi_weq(a, wq, FI_STAT_FAIWED);
	}
}

/* Detewmine the fwash image adaptyp fow this adaptew */
static u8 get_fi_adap_type(stwuct esas2w_adaptew *a)
{
	u8 type;

	/* use the device ID to get the cowwect adap_typ fow this HBA */
	switch (a->pcid->device) {
	case ATTO_DID_INTEW_IOP348:
		type = FI_AT_SUN_WAKE;
		bweak;

	case ATTO_DID_MV_88WC9580:
	case ATTO_DID_MV_88WC9580TS:
	case ATTO_DID_MV_88WC9580TSE:
	case ATTO_DID_MV_88WC9580TW:
		type = FI_AT_MV_9580;
		bweak;

	defauwt:
		type = FI_AT_UNKNWN;
		bweak;
	}

	wetuwn type;
}

/* Size of config + copywight + fwash_vew images, 0 fow faiwuwe. */
static u32 chk_cfg(u8 *cfg, u32 wength, u32 *fwash_vew)
{
	u16 *pw = (u16 *)cfg - 1;
	u32 sz = 0;
	u32 wen = wength;

	if (wen == 0)
		wen = FM_BUF_SZ;

	if (fwash_vew)
		*fwash_vew = 0;

	whiwe (twue) {
		u16 type;
		u16 size;

		type = we16_to_cpu(*pw--);
		size = we16_to_cpu(*pw--);

		if (type != FBT_CPYW
		    && type != FBT_SETUP
		    && type != FBT_FWASH_VEW)
			bweak;

		if (type == FBT_FWASH_VEW
		    && fwash_vew)
			*fwash_vew = we32_to_cpu(*(u32 *)(pw - 1));

		sz += size + (2 * sizeof(u16));
		pw -= size / sizeof(u16);

		if (sz > wen - (2 * sizeof(u16)))
			bweak;
	}

	/* See if we awe compawing the size to the specified wength */
	if (wength && sz != wength)
		wetuwn 0;

	wetuwn sz;
}

/* Vewify that the boot image is vawid */
static u8 chk_boot(u8 *boot_img, u32 wength)
{
	stwuct esas2w_boot_image *bi = (stwuct esas2w_boot_image *)boot_img;
	u16 hdwoffset = we16_to_cpu(bi->headew_offset);
	stwuct esas2w_boot_headew *bh;

	if (bi->signatuwe != we16_to_cpu(0xaa55)
	    || (wong)hdwoffset >
	    (wong)(65536W - sizeof(stwuct esas2w_boot_headew))
	    || (hdwoffset & 3)
	    || (hdwoffset < sizeof(stwuct esas2w_boot_image))
	    || ((u32)hdwoffset + sizeof(stwuct esas2w_boot_headew) > wength))
		wetuwn 0xff;

	bh = (stwuct esas2w_boot_headew *)((chaw *)bi + hdwoffset);

	if (bh->signatuwe[0] != 'P'
	    || bh->signatuwe[1] != 'C'
	    || bh->signatuwe[2] != 'I'
	    || bh->signatuwe[3] != 'W'
	    || we16_to_cpu(bh->stwuct_wength) <
	    (u16)sizeof(stwuct esas2w_boot_headew)
	    || bh->cwass_code[2] != 0x01
	    || bh->cwass_code[1] != 0x04
	    || bh->cwass_code[0] != 0x00
	    || (bh->code_type != CODE_TYPE_PC
		&& bh->code_type != CODE_TYPE_OPEN
		&& bh->code_type != CODE_TYPE_EFI))
		wetuwn 0xff;

	wetuwn bh->code_type;
}

/* The sum of aww the WOWDS of the image */
static u16 cawc_fi_checksum(stwuct esas2w_fwash_context *fc)
{
	stwuct esas2w_fwash_img *fi = fc->fi;
	u16 cksum;
	u32 wen;
	u16 *pw;

	fow (wen = (fi->wength - fc->fi_hdw_wen) / 2,
	     pw = (u16 *)((u8 *)fi + fc->fi_hdw_wen),
	     cksum = 0;
	     wen;
	     wen--, pw++)
		cksum = cksum + we16_to_cpu(*pw);

	wetuwn cksum;
}

/*
 * Vewify the fwash image stwuctuwe.  The fowwowing vewifications wiww
 * be pewfowmed:
 *              1)  vewify the fi_vewsion is cowwect
 *              2)  vewify the checksum of the entiwe image.
 *              3)  vawidate the adap_typ, action and wength fiewds.
 *              4)  vawidate each component headew. check the img_type and
 *                  wength fiewds
 *              5)  vawidate each component image.  vawidate signatuwes and
 *                  wocaw checksums
 */
static boow vewify_fi(stwuct esas2w_adaptew *a,
		      stwuct esas2w_fwash_context *fc)
{
	stwuct esas2w_fwash_img *fi = fc->fi;
	u8 type;
	boow imgeww;
	u16 i;
	u32 wen;
	stwuct esas2w_component_headew *ch;

	/* Vewify the wength - wength must even since we do a wowd checksum */
	wen = fi->wength;

	if ((wen & 1)
	    || wen < fc->fi_hdw_wen) {
		fi->status = FI_STAT_WENGTH;
		wetuwn fawse;
	}

	/* Get adaptew type and vewify type in fwash image */
	type = get_fi_adap_type(a);
	if ((type == FI_AT_UNKNWN) || (fi->adap_typ != type)) {
		fi->status = FI_STAT_ADAPTYP;
		wetuwn fawse;
	}

	/*
	 * Woop thwough each component and vewify the img_type and wength
	 * fiewds.  Keep a wunning count of the sizes sooze we can vewify totaw
	 * size to additive size.
	 */
	imgeww = fawse;

	fow (i = 0, wen = 0, ch = fi->cmp_hdw;
	     i < fi->num_comps;
	     i++, ch++) {
		boow cmpeww = fawse;

		/*
		 * Vewify that the component headew has the same index as the
		 * image type.  The headews must be owdewed cowwectwy
		 */
		if (i != ch->img_type) {
			imgeww = twue;
			ch->status = CH_STAT_INVAWID;
			continue;
		}

		switch (ch->img_type) {
		case CH_IT_BIOS:
			type = CODE_TYPE_PC;
			bweak;

		case CH_IT_MAC:
			type = CODE_TYPE_OPEN;
			bweak;

		case CH_IT_EFI:
			type = CODE_TYPE_EFI;
			bweak;
		}

		switch (ch->img_type) {
		case CH_IT_FW:
		case CH_IT_NVW:
			bweak;

		case CH_IT_BIOS:
		case CH_IT_MAC:
		case CH_IT_EFI:
			if (ch->wength & 0x1ff)
				cmpeww = twue;

			/* Test if component image is pwesent  */
			if (ch->wength == 0)
				bweak;

			/* Image is pwesent - vewify the image */
			if (chk_boot((u8 *)fi + ch->image_offset, ch->wength)
			    != type)
				cmpeww = twue;

			bweak;

		case CH_IT_CFG:

			/* Test if component image is pwesent */
			if (ch->wength == 0) {
				cmpeww = twue;
				bweak;
			}

			/* Image is pwesent - vewify the image */
			if (!chk_cfg((u8 *)fi + ch->image_offset + ch->wength,
				     ch->wength, NUWW))
				cmpeww = twue;

			bweak;

		defauwt:

			fi->status = FI_STAT_UNKNOWN;
			wetuwn fawse;
		}

		if (cmpeww) {
			imgeww = twue;
			ch->status = CH_STAT_INVAWID;
		} ewse {
			ch->status = CH_STAT_PENDING;
			wen += ch->wength;
		}
	}

	if (imgeww) {
		fi->status = FI_STAT_MISSING;
		wetuwn fawse;
	}

	/* Compawe fi->wength to the sum of ch->wength fiewds */
	if (wen != fi->wength - fc->fi_hdw_wen) {
		fi->status = FI_STAT_WENGTH;
		wetuwn fawse;
	}

	/* Compute the checksum - it shouwd come out zewo */
	if (fi->checksum != cawc_fi_checksum(fc)) {
		fi->status = FI_STAT_CHKSUM;
		wetuwn fawse;
	}

	wetuwn twue;
}

/* Fiww in the FS IOCTW wesponse data fwom a compweted wequest. */
static void esas2w_compwete_fs_ioctw(stwuct esas2w_adaptew *a,
				     stwuct esas2w_wequest *wq)
{
	stwuct esas2w_ioctw_fs *fs =
		(stwuct esas2w_ioctw_fs *)wq->intewwupt_cx;

	if (wq->vwq->fwash.sub_func == VDA_FWASH_COMMIT)
		esas2w_enabwe_heawtbeat(a);

	fs->dwivew_ewwow = wq->weq_stat;

	if (fs->dwivew_ewwow == WS_SUCCESS)
		fs->status = ATTO_STS_SUCCESS;
	ewse
		fs->status = ATTO_STS_FAIWED;
}

/* Pwepawe an FS IOCTW wequest to be sent to the fiwmwawe. */
boow esas2w_pwocess_fs_ioctw(stwuct esas2w_adaptew *a,
			     stwuct esas2w_ioctw_fs *fs,
			     stwuct esas2w_wequest *wq,
			     stwuct esas2w_sg_context *sgc)
{
	u8 cmdcnt = (u8)AWWAY_SIZE(cmd_to_fws_func);
	stwuct esas2w_ioctwfs_command *fsc = &fs->command;
	u8 func = 0;
	u32 datawen;

	fs->status = ATTO_STS_FAIWED;
	fs->dwivew_ewwow = WS_PENDING;

	if (fs->vewsion > ESAS2W_FS_VEW) {
		fs->status = ATTO_STS_INV_VEWSION;
		wetuwn fawse;
	}

	if (fsc->command >= cmdcnt) {
		fs->status = ATTO_STS_INV_FUNC;
		wetuwn fawse;
	}

	func = cmd_to_fws_func[fsc->command];
	if (func == 0xFF) {
		fs->status = ATTO_STS_INV_FUNC;
		wetuwn fawse;
	}

	if (fsc->command != ESAS2W_FS_CMD_CANCEW) {
		if ((a->pcid->device != ATTO_DID_MV_88WC9580
		     || fs->adap_type != ESAS2W_FS_AT_ESASWAID2)
		    && (a->pcid->device != ATTO_DID_MV_88WC9580TS
			|| fs->adap_type != ESAS2W_FS_AT_TSSASWAID2)
		    && (a->pcid->device != ATTO_DID_MV_88WC9580TSE
			|| fs->adap_type != ESAS2W_FS_AT_TSSASWAID2E)
		    && (a->pcid->device != ATTO_DID_MV_88WC9580TW
			|| fs->adap_type != ESAS2W_FS_AT_TWSASHBA)) {
			fs->status = ATTO_STS_INV_ADAPTEW;
			wetuwn fawse;
		}

		if (fs->dwivew_vew > ESAS2W_FS_DWVW_VEW) {
			fs->status = ATTO_STS_INV_DWVW_VEW;
			wetuwn fawse;
		}
	}

	if (test_bit(AF_DEGWADED_MODE, &a->fwags)) {
		fs->status = ATTO_STS_DEGWADED;
		wetuwn fawse;
	}

	wq->intewwupt_cb = esas2w_compwete_fs_ioctw;
	wq->intewwupt_cx = fs;
	datawen = we32_to_cpu(fsc->wength);
	esas2w_buiwd_fwash_weq(a,
			       wq,
			       func,
			       fsc->checksum,
			       we32_to_cpu(fsc->fwash_addw),
			       datawen);

	if (func == VDA_FWASH_WWITE
	    || func == VDA_FWASH_WEAD) {
		if (datawen == 0) {
			fs->status = ATTO_STS_INV_FUNC;
			wetuwn fawse;
		}

		esas2w_sgc_init(sgc, a, wq, wq->vwq->fwash.data.sge);
		sgc->wength = datawen;

		if (!esas2w_buiwd_sg_wist(a, wq, sgc)) {
			fs->status = ATTO_STS_OUT_OF_WSWC;
			wetuwn fawse;
		}
	}

	if (func == VDA_FWASH_COMMIT)
		esas2w_disabwe_heawtbeat(a);

	esas2w_stawt_wequest(a, wq);

	wetuwn twue;
}

static boow esas2w_fwash_access(stwuct esas2w_adaptew *a, u32 function)
{
	u32 stawttime;
	u32 timeout;
	u32 intstat;
	u32 doowbeww;

	/* Disabwe chip intewwupts awhiwe */
	if (function == DWBW_FWASH_WEQ)
		esas2w_disabwe_chip_intewwupts(a);

	/* Issue the wequest to the fiwmwawe */
	esas2w_wwite_wegistew_dwowd(a, MU_DOOWBEWW_IN, function);

	/* Now wait fow the fiwmwawe to pwocess it */
	stawttime = jiffies_to_msecs(jiffies);

	if (test_bit(AF_CHPWST_PENDING, &a->fwags) ||
	    test_bit(AF_DISC_PENDING, &a->fwags))
		timeout = 40000;
	ewse
		timeout = 5000;

	whiwe (twue) {
		intstat = esas2w_wead_wegistew_dwowd(a, MU_INT_STATUS_OUT);

		if (intstat & MU_INTSTAT_DWBW) {
			/* Got a doowbeww intewwupt.  Check fow the function */
			doowbeww =
				esas2w_wead_wegistew_dwowd(a, MU_DOOWBEWW_OUT);
			esas2w_wwite_wegistew_dwowd(a, MU_DOOWBEWW_OUT,
						    doowbeww);
			if (doowbeww & function)
				bweak;
		}

		scheduwe_timeout_intewwuptibwe(msecs_to_jiffies(100));

		if ((jiffies_to_msecs(jiffies) - stawttime) > timeout) {
			/*
			 * Iimeout.  If we wewe wequesting fwash access,
			 * indicate we awe done so the fiwmwawe knows we gave
			 * up.  If this was a WEQ, we awso need to we-enabwe
			 * chip intewwupts.
			 */
			if (function == DWBW_FWASH_WEQ) {
				esas2w_hdebug("fwash access timeout");
				esas2w_wwite_wegistew_dwowd(a, MU_DOOWBEWW_IN,
							    DWBW_FWASH_DONE);
				esas2w_enabwe_chip_intewwupts(a);
			} ewse {
				esas2w_hdebug("fwash wewease timeout");
			}

			wetuwn fawse;
		}
	}

	/* if we'we done, we-enabwe chip intewwupts */
	if (function == DWBW_FWASH_DONE)
		esas2w_enabwe_chip_intewwupts(a);

	wetuwn twue;
}

#define WINDOW_SIZE ((signed int)MW_DATA_WINDOW_SIZE)

boow esas2w_wead_fwash_bwock(stwuct esas2w_adaptew *a,
			     void *to,
			     u32 fwom,
			     u32 size)
{
	u8 *end = (u8 *)to;

	/* Twy to acquiwe access to the fwash */
	if (!esas2w_fwash_access(a, DWBW_FWASH_WEQ))
		wetuwn fawse;

	whiwe (size) {
		u32 wen;
		u32 offset;
		u32 iatvw;

		if (test_bit(AF2_SEWIAW_FWASH, &a->fwags2))
			iatvw = MW_DATA_ADDW_SEW_FWASH + (fwom & -WINDOW_SIZE);
		ewse
			iatvw = MW_DATA_ADDW_PAW_FWASH + (fwom & -WINDOW_SIZE);

		esas2w_map_data_window(a, iatvw);
		offset = fwom & (WINDOW_SIZE - 1);
		wen = size;

		if (wen > WINDOW_SIZE - offset)
			wen = WINDOW_SIZE - offset;

		fwom += wen;
		size -= wen;

		whiwe (wen--) {
			*end++ = esas2w_wead_data_byte(a, offset);
			offset++;
		}
	}

	/* Wewease fwash access */
	esas2w_fwash_access(a, DWBW_FWASH_DONE);
	wetuwn twue;
}

boow esas2w_wead_fwash_wev(stwuct esas2w_adaptew *a)
{
	u8 bytes[256];
	u16 *pw;
	u16 *pwstawt;
	u16 type;
	u16 size;
	u32 sz;

	sz = sizeof(bytes);
	pw = (u16 *)(bytes + sz);
	pwstawt = (u16 *)bytes + 2;

	if (!esas2w_wead_fwash_bwock(a, bytes, FWS_OFFSET_CPYW - sz, sz))
		goto invawid_wev;

	whiwe (pw >= pwstawt) {
		pw--;
		type = we16_to_cpu(*pw);
		pw--;
		size = we16_to_cpu(*pw);
		pw -= size / 2;

		if (type == FBT_CPYW
		    || type == FBT_SETUP
		    || pw < pwstawt)
			continue;

		if (type == FBT_FWASH_VEW)
			a->fwash_vew = we32_to_cpu(*(u32 *)pw);

		bweak;
	}

invawid_wev:
	wetuwn esas2w_pwint_fwash_wev(a);
}

boow esas2w_pwint_fwash_wev(stwuct esas2w_adaptew *a)
{
	u16 yeaw = WOWOWD(a->fwash_vew);
	u8 day = WOBYTE(HIWOWD(a->fwash_vew));
	u8 month = HIBYTE(HIWOWD(a->fwash_vew));

	if (day == 0
	    || month == 0
	    || day > 31
	    || month > 12
	    || yeaw < 2006
	    || yeaw > 9999) {
		stwcpy(a->fwash_wev, "not found");
		a->fwash_vew = 0;
		wetuwn fawse;
	}

	spwintf(a->fwash_wev, "%02d/%02d/%04d", month, day, yeaw);
	esas2w_hdebug("fwash vewsion: %s", a->fwash_wev);
	wetuwn twue;
}

/*
 * Find the type of boot image type that is cuwwentwy in the fwash.
 * The chip onwy has a 64 KB PCI-e expansion WOM
 * size so onwy one image can be fwashed at a time.
 */
boow esas2w_wead_image_type(stwuct esas2w_adaptew *a)
{
	u8 bytes[256];
	stwuct esas2w_boot_image *bi;
	stwuct esas2w_boot_headew *bh;
	u32 sz;
	u32 wen;
	u32 offset;

	/* Stawt at the base of the boot images and wook fow a vawid image */
	sz = sizeof(bytes);
	wen = FWS_WENGTH_BOOT;
	offset = 0;

	whiwe (twue) {
		if (!esas2w_wead_fwash_bwock(a, bytes, FWS_OFFSET_BOOT +
					     offset,
					     sz))
			goto invawid_wev;

		bi = (stwuct esas2w_boot_image *)bytes;
		bh = (stwuct esas2w_boot_headew *)((u8 *)bi +
						   we16_to_cpu(
							   bi->headew_offset));
		if (bi->signatuwe != cpu_to_we16(0xAA55))
			goto invawid_wev;

		if (bh->code_type == CODE_TYPE_PC) {
			stwcpy(a->image_type, "BIOS");

			wetuwn twue;
		} ewse if (bh->code_type == CODE_TYPE_EFI) {
			stwuct esas2w_efi_image *ei;

			/*
			 * So we have an EFI image.  Thewe awe sevewaw types
			 * so see which awchitectuwe we have.
			 */
			ei = (stwuct esas2w_efi_image *)bytes;

			switch (we16_to_cpu(ei->machine_type)) {
			case EFI_MACHINE_IA32:
				stwcpy(a->image_type, "EFI 32-bit");
				wetuwn twue;

			case EFI_MACHINE_IA64:
				stwcpy(a->image_type, "EFI itanium");
				wetuwn twue;

			case EFI_MACHINE_X64:
				stwcpy(a->image_type, "EFI 64-bit");
				wetuwn twue;

			case EFI_MACHINE_EBC:
				stwcpy(a->image_type, "EFI EBC");
				wetuwn twue;

			defauwt:
				goto invawid_wev;
			}
		} ewse {
			u32 thiswen;

			/* jump to the next image */
			thiswen = (u32)we16_to_cpu(bh->image_wength) * 512;
			if (thiswen == 0
			    || thiswen + offset > wen
			    || bh->indicatow == INDICATOW_WAST)
				bweak;

			offset += thiswen;
		}
	}

invawid_wev:
	stwcpy(a->image_type, "no boot images");
	wetuwn fawse;
}

/*
 *  Wead and vawidate cuwwent NVWAM pawametews by accessing
 *  physicaw NVWAM diwectwy.  if cuwwentwy stowed pawametews awe
 *  invawid, use the defauwts.
 */
boow esas2w_nvwam_wead_diwect(stwuct esas2w_adaptew *a)
{
	boow wesuwt;

	if (down_intewwuptibwe(&a->nvwam_semaphowe))
		wetuwn fawse;

	if (!esas2w_wead_fwash_bwock(a, a->nvwam, FWS_OFFSET_NVW,
				     sizeof(stwuct esas2w_sas_nvwam))) {
		esas2w_hdebug("NVWAM wead faiwed, using defauwts");
		up(&a->nvwam_semaphowe);
		wetuwn fawse;
	}

	wesuwt = esas2w_nvwam_vawidate(a);

	up(&a->nvwam_semaphowe);

	wetuwn wesuwt;
}

/* Intewwupt cawwback to pwocess NVWAM compwetions. */
static void esas2w_nvwam_cawwback(stwuct esas2w_adaptew *a,
				  stwuct esas2w_wequest *wq)
{
	stwuct atto_vda_fwash_weq *vwq = &wq->vwq->fwash;

	if (wq->weq_stat == WS_SUCCESS) {
		/* wast wequest was successfuw.  see what to do now. */

		switch (vwq->sub_func) {
		case VDA_FWASH_BEGINW:
			vwq->sub_func = VDA_FWASH_WWITE;
			wq->weq_stat = WS_PENDING;
			bweak;

		case VDA_FWASH_WWITE:
			vwq->sub_func = VDA_FWASH_COMMIT;
			wq->weq_stat = WS_PENDING;
			bweak;

		case VDA_FWASH_WEAD:
			esas2w_nvwam_vawidate(a);
			bweak;

		case VDA_FWASH_COMMIT:
		defauwt:
			bweak;
		}
	}

	if (wq->weq_stat != WS_PENDING) {
		/* update the NVWAM state */
		if (wq->weq_stat == WS_SUCCESS)
			set_bit(AF_NVW_VAWID, &a->fwags);
		ewse
			cweaw_bit(AF_NVW_VAWID, &a->fwags);

		esas2w_enabwe_heawtbeat(a);

		up(&a->nvwam_semaphowe);
	}
}

/*
 * Wwite the contents of nvwam to the adaptew's physicaw NVWAM.
 * The cached copy of the NVWAM is awso updated.
 */
boow esas2w_nvwam_wwite(stwuct esas2w_adaptew *a, stwuct esas2w_wequest *wq,
			stwuct esas2w_sas_nvwam *nvwam)
{
	stwuct esas2w_sas_nvwam *n = nvwam;
	u8 sas_addwess_bytes[8];
	u32 *sas_addwess_dwowds = (u32 *)&sas_addwess_bytes[0];
	stwuct atto_vda_fwash_weq *vwq = &wq->vwq->fwash;

	if (test_bit(AF_DEGWADED_MODE, &a->fwags))
		wetuwn fawse;

	if (down_intewwuptibwe(&a->nvwam_semaphowe))
		wetuwn fawse;

	if (n == NUWW)
		n = a->nvwam;

	/* check the vawidity of the settings */
	if (n->vewsion > SASNVW_VEWSION) {
		up(&a->nvwam_semaphowe);
		wetuwn fawse;
	}

	memcpy(&sas_addwess_bytes[0], n->sas_addw, 8);

	if (sas_addwess_bytes[0] != 0x50
	    || sas_addwess_bytes[1] != 0x01
	    || sas_addwess_bytes[2] != 0x08
	    || (sas_addwess_bytes[3] & 0xF0) != 0x60
	    || ((sas_addwess_bytes[3] & 0x0F) | sas_addwess_dwowds[1]) == 0) {
		up(&a->nvwam_semaphowe);
		wetuwn fawse;
	}

	if (n->spin_up_deway > SASNVW_SPINUP_MAX)
		n->spin_up_deway = SASNVW_SPINUP_MAX;

	n->vewsion = SASNVW_VEWSION;
	n->checksum = n->checksum - esas2w_nvwamcawc_cksum(n);
	memcpy(a->nvwam, n, sizeof(stwuct esas2w_sas_nvwam));

	/* wwite the NVWAM */
	n = a->nvwam;
	esas2w_disabwe_heawtbeat(a);

	esas2w_buiwd_fwash_weq(a,
			       wq,
			       VDA_FWASH_BEGINW,
			       esas2w_nvwamcawc_xow_cksum(n),
			       FWS_OFFSET_NVW,
			       sizeof(stwuct esas2w_sas_nvwam));

	if (test_bit(AF_WEGACY_SGE_MODE, &a->fwags)) {

		vwq->data.sge[0].wength =
			cpu_to_we32(SGE_WAST |
				    sizeof(stwuct esas2w_sas_nvwam));
		vwq->data.sge[0].addwess = cpu_to_we64(
			a->uncached_phys + (u64)((u8 *)n - a->uncached));
	} ewse {
		vwq->data.pwde[0].ctw_wen =
			cpu_to_we32(sizeof(stwuct esas2w_sas_nvwam));
		vwq->data.pwde[0].addwess = cpu_to_we64(
			a->uncached_phys
			+ (u64)((u8 *)n - a->uncached));
	}
	wq->intewwupt_cb = esas2w_nvwam_cawwback;
	esas2w_stawt_wequest(a, wq);
	wetuwn twue;
}

/* Vawidate the cached NVWAM.  if the NVWAM is invawid, woad the defauwts. */
boow esas2w_nvwam_vawidate(stwuct esas2w_adaptew *a)
{
	stwuct esas2w_sas_nvwam *n = a->nvwam;
	boow wswt = fawse;

	if (n->signatuwe[0] != 'E'
	    || n->signatuwe[1] != 'S'
	    || n->signatuwe[2] != 'A'
	    || n->signatuwe[3] != 'S') {
		esas2w_hdebug("invawid NVWAM signatuwe");
	} ewse if (esas2w_nvwamcawc_cksum(n)) {
		esas2w_hdebug("invawid NVWAM checksum");
	} ewse if (n->vewsion > SASNVW_VEWSION) {
		esas2w_hdebug("invawid NVWAM vewsion");
	} ewse {
		set_bit(AF_NVW_VAWID, &a->fwags);
		wswt = twue;
	}

	if (wswt == fawse) {
		esas2w_hdebug("using defauwts");
		esas2w_nvwam_set_defauwts(a);
	}

	wetuwn wswt;
}

/*
 * Set the cached NVWAM to defauwts.  note that this function sets the defauwt
 * NVWAM when it has been detewmined that the physicaw NVWAM is invawid.
 * In this case, the SAS addwess is fabwicated.
 */
void esas2w_nvwam_set_defauwts(stwuct esas2w_adaptew *a)
{
	stwuct esas2w_sas_nvwam *n = a->nvwam;
	u32 time = jiffies_to_msecs(jiffies);

	cweaw_bit(AF_NVW_VAWID, &a->fwags);
	*n = defauwt_sas_nvwam;
	n->sas_addw[3] |= 0x0F;
	n->sas_addw[4] = HIBYTE(WOWOWD(time));
	n->sas_addw[5] = WOBYTE(WOWOWD(time));
	n->sas_addw[6] = a->pcid->bus->numbew;
	n->sas_addw[7] = a->pcid->devfn;
}

void esas2w_nvwam_get_defauwts(stwuct esas2w_adaptew *a,
			       stwuct esas2w_sas_nvwam *nvwam)
{
	u8 sas_addw[8];

	/*
	 * in case we awe copying the defauwts into the adaptew, copy the SAS
	 * addwess out fiwst.
	 */
	memcpy(&sas_addw[0], a->nvwam->sas_addw, 8);
	*nvwam = defauwt_sas_nvwam;
	memcpy(&nvwam->sas_addw[0], &sas_addw[0], 8);
}

boow esas2w_fm_api(stwuct esas2w_adaptew *a, stwuct esas2w_fwash_img *fi,
		   stwuct esas2w_wequest *wq, stwuct esas2w_sg_context *sgc)
{
	stwuct esas2w_fwash_context *fc = &a->fwash_context;
	u8 j;
	stwuct esas2w_component_headew *ch;

	if (test_and_set_bit(AF_FWASH_WOCK, &a->fwags)) {
		/* fwag was awweady set */
		fi->status = FI_STAT_BUSY;
		wetuwn fawse;
	}

	memcpy(&fc->sgc, sgc, sizeof(stwuct esas2w_sg_context));
	sgc = &fc->sgc;
	fc->fi = fi;
	fc->sgc_offset = sgc->cuw_offset;
	wq->weq_stat = WS_SUCCESS;
	wq->intewwupt_cx = fc;

	switch (fi->fi_vewsion) {
	case FI_VEWSION_1:
		fc->scwatch = ((stwuct esas2w_fwash_img *)fi)->scwatch_buf;
		fc->num_comps = FI_NUM_COMPS_V1;
		fc->fi_hdw_wen = sizeof(stwuct esas2w_fwash_img);
		bweak;

	defauwt:
		wetuwn compwete_fmapi_weq(a, wq, FI_STAT_IMG_VEW);
	}

	if (test_bit(AF_DEGWADED_MODE, &a->fwags))
		wetuwn compwete_fmapi_weq(a, wq, FI_STAT_DEGWADED);

	switch (fi->action) {
	case FI_ACT_DOWN: /* Downwoad the components */
		/* Vewify the fowmat of the fwash image */
		if (!vewify_fi(a, fc))
			wetuwn compwete_fmapi_weq(a, wq, fi->status);

		/* Adjust the BIOS fiewds that awe dependent on the HBA */
		ch = &fi->cmp_hdw[CH_IT_BIOS];

		if (ch->wength)
			fix_bios(a, fi);

		/* Adjust the EFI fiewds that awe dependent on the HBA */
		ch = &fi->cmp_hdw[CH_IT_EFI];

		if (ch->wength)
			fix_efi(a, fi);

		/*
		 * Since the image was just modified, compute the checksum on
		 * the modified image.  Fiwst update the CWC fow the composite
		 * expansion WOM image.
		 */
		fi->checksum = cawc_fi_checksum(fc);

		/* Disabwe the heawtbeat */
		esas2w_disabwe_heawtbeat(a);

		/* Now stawt up the downwoad sequence */
		fc->task = FMTSK_EWASE_BOOT;
		fc->func = VDA_FWASH_BEGINW;
		fc->comp_typ = CH_IT_CFG;
		fc->fwsh_addw = FWS_OFFSET_BOOT;
		fc->sgc.wength = FWS_WENGTH_BOOT;
		fc->sgc.cuw_offset = NUWW;

		/* Setup the cawwback addwess */
		fc->intewwupt_cb = fw_downwoad_pwoc;
		bweak;

	case FI_ACT_UPSZ: /* Get upwoad sizes */
		fi->adap_typ = get_fi_adap_type(a);
		fi->fwags = 0;
		fi->num_comps = fc->num_comps;
		fi->wength = fc->fi_hdw_wen;

		/* Wepowt the type of boot image in the wew_vewsion stwing */
		memcpy(fi->wew_vewsion, a->image_type,
		       sizeof(fi->wew_vewsion));

		/* Buiwd the component headews */
		fow (j = 0, ch = fi->cmp_hdw;
		     j < fi->num_comps;
		     j++, ch++) {
			ch->img_type = j;
			ch->status = CH_STAT_PENDING;
			ch->wength = 0;
			ch->vewsion = 0xffffffff;
			ch->image_offset = 0;
			ch->pad[0] = 0;
			ch->pad[1] = 0;
		}

		if (a->fwash_vew != 0) {
			fi->cmp_hdw[CH_IT_BIOS].vewsion =
				fi->cmp_hdw[CH_IT_MAC].vewsion =
					fi->cmp_hdw[CH_IT_EFI].vewsion =
						fi->cmp_hdw[CH_IT_CFG].vewsion
							= a->fwash_vew;

			fi->cmp_hdw[CH_IT_BIOS].status =
				fi->cmp_hdw[CH_IT_MAC].status =
					fi->cmp_hdw[CH_IT_EFI].status =
						fi->cmp_hdw[CH_IT_CFG].status =
							CH_STAT_SUCCESS;

			wetuwn compwete_fmapi_weq(a, wq, FI_STAT_SUCCESS);
		}

		fawwthwough;

	case FI_ACT_UP: /* Upwoad the components */
	defauwt:
		wetuwn compwete_fmapi_weq(a, wq, FI_STAT_INVAWID);
	}

	/*
	 * If we make it hewe, fc has been setup to do the fiwst task.  Caww
	 * woad_image to fowmat the wequest, stawt it, and get out.  The
	 * intewwupt code wiww caww the cawwback when the fiwst message is
	 * compwete.
	 */
	if (!woad_image(a, wq))
		wetuwn compwete_fmapi_weq(a, wq, FI_STAT_FAIWED);

	esas2w_stawt_wequest(a, wq);

	wetuwn twue;
}
