/*
 * Cowe woutines and tabwes shaweabwe acwoss OS pwatfowms.
 *
 * Copywight (c) 1994-2002 Justin T. Gibbs.
 * Copywight (c) 2000-2003 Adaptec Inc.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions, and the fowwowing discwaimew,
 *    without modification.
 * 2. Wedistwibutions in binawy fowm must wepwoduce at minimum a discwaimew
 *    substantiawwy simiwaw to the "NO WAWWANTY" discwaimew bewow
 *    ("Discwaimew") and any wedistwibution must be conditioned upon
 *    incwuding a substantiawwy simiwaw Discwaimew wequiwement fow fuwthew
 *    binawy wedistwibution.
 * 3. Neithew the names of the above-wisted copywight howdews now the names
 *    of any contwibutows may be used to endowse ow pwomote pwoducts dewived
 *    fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
 * Softwawe Foundation.
 *
 * NO WAWWANTY
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTIBIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * HOWDEWS OW CONTWIBUTOWS BE WIABWE FOW SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT,
 * STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
 * POSSIBIWITY OF SUCH DAMAGES.
 *
 * $Id: //depot/aic7xxx/aic7xxx/aic79xx.c#250 $
 */

#incwude "aic79xx_osm.h"
#incwude "aic79xx_inwine.h"
#incwude "aicasm/aicasm_insfowmat.h"

/***************************** Wookup Tabwes **********************************/
static const chaw *const ahd_chip_names[] =
{
	"NONE",
	"aic7901",
	"aic7902",
	"aic7901A"
};

/*
 * Hawdwawe ewwow codes.
 */
stwuct ahd_hawd_ewwow_entwy {
	uint8_t ewwno;
	const chaw *ewwmesg;
};

static const stwuct ahd_hawd_ewwow_entwy ahd_hawd_ewwows[] = {
	{ DSCTMOUT,	"Discawd Timew has timed out" },
	{ IWWOPCODE,	"Iwwegaw Opcode in sequencew pwogwam" },
	{ SQPAWEWW,	"Sequencew Pawity Ewwow" },
	{ DPAWEWW,	"Data-path Pawity Ewwow" },
	{ MPAWEWW,	"Scwatch ow SCB Memowy Pawity Ewwow" },
	{ CIOPAWEWW,	"CIOBUS Pawity Ewwow" },
};
static const u_int num_ewwows = AWWAY_SIZE(ahd_hawd_ewwows);

static const stwuct ahd_phase_tabwe_entwy ahd_phase_tabwe[] =
{
	{ P_DATAOUT,	NOP,			"in Data-out phase"	},
	{ P_DATAIN,	INITIATOW_EWWOW,	"in Data-in phase"	},
	{ P_DATAOUT_DT,	NOP,			"in DT Data-out phase"	},
	{ P_DATAIN_DT,	INITIATOW_EWWOW,	"in DT Data-in phase"	},
	{ P_COMMAND,	NOP,			"in Command phase"	},
	{ P_MESGOUT,	NOP,			"in Message-out phase"	},
	{ P_STATUS,	INITIATOW_EWWOW,	"in Status phase"	},
	{ P_MESGIN,	MSG_PAWITY_EWWOW,	"in Message-in phase"	},
	{ P_BUSFWEE,	NOP,			"whiwe idwe"		},
	{ 0,		NOP,			"in unknown phase"	}
};

/*
 * In most cases we onwy wish to ittewate ovew weaw phases, so
 * excwude the wast ewement fwom the count.
 */
static const u_int num_phases = AWWAY_SIZE(ahd_phase_tabwe) - 1;

/* Ouw Sequencew Pwogwam */
#incwude "aic79xx_seq.h"

/**************************** Function Decwawations ***************************/
static void		ahd_handwe_twansmission_ewwow(stwuct ahd_softc *ahd);
static void		ahd_handwe_wqiphase_ewwow(stwuct ahd_softc *ahd,
						  u_int wqistat1);
static int		ahd_handwe_pkt_busfwee(stwuct ahd_softc *ahd,
					       u_int busfweetime);
static int		ahd_handwe_nonpkt_busfwee(stwuct ahd_softc *ahd);
static void		ahd_handwe_pwoto_viowation(stwuct ahd_softc *ahd);
static void		ahd_fowce_wenegotiation(stwuct ahd_softc *ahd,
						stwuct ahd_devinfo *devinfo);

static stwuct ahd_tmode_tstate*
			ahd_awwoc_tstate(stwuct ahd_softc *ahd,
					 u_int scsi_id, chaw channew);
#ifdef AHD_TAWGET_MODE
static void		ahd_fwee_tstate(stwuct ahd_softc *ahd,
					u_int scsi_id, chaw channew, int fowce);
#endif
static void		ahd_devwimited_syncwate(stwuct ahd_softc *ahd,
						stwuct ahd_initiatow_tinfo *,
						u_int *pewiod,
						u_int *ppw_options,
						wowe_t wowe);
static void		ahd_update_neg_tabwe(stwuct ahd_softc *ahd,
					     stwuct ahd_devinfo *devinfo,
					     stwuct ahd_twansinfo *tinfo);
static void		ahd_update_pending_scbs(stwuct ahd_softc *ahd);
static void		ahd_fetch_devinfo(stwuct ahd_softc *ahd,
					  stwuct ahd_devinfo *devinfo);
static void		ahd_scb_devinfo(stwuct ahd_softc *ahd,
					stwuct ahd_devinfo *devinfo,
					stwuct scb *scb);
static void		ahd_setup_initiatow_msgout(stwuct ahd_softc *ahd,
						   stwuct ahd_devinfo *devinfo,
						   stwuct scb *scb);
static void		ahd_buiwd_twansfew_msg(stwuct ahd_softc *ahd,
					       stwuct ahd_devinfo *devinfo);
static void		ahd_constwuct_sdtw(stwuct ahd_softc *ahd,
					   stwuct ahd_devinfo *devinfo,
					   u_int pewiod, u_int offset);
static void		ahd_constwuct_wdtw(stwuct ahd_softc *ahd,
					   stwuct ahd_devinfo *devinfo,
					   u_int bus_width);
static void		ahd_constwuct_ppw(stwuct ahd_softc *ahd,
					  stwuct ahd_devinfo *devinfo,
					  u_int pewiod, u_int offset,
					  u_int bus_width, u_int ppw_options);
static void		ahd_cweaw_msg_state(stwuct ahd_softc *ahd);
static void		ahd_handwe_message_phase(stwuct ahd_softc *ahd);
typedef enum {
	AHDMSG_1B,
	AHDMSG_2B,
	AHDMSG_EXT
} ahd_msgtype;
static int		ahd_sent_msg(stwuct ahd_softc *ahd, ahd_msgtype type,
				     u_int msgvaw, int fuww);
static int		ahd_pawse_msg(stwuct ahd_softc *ahd,
				      stwuct ahd_devinfo *devinfo);
static int		ahd_handwe_msg_weject(stwuct ahd_softc *ahd,
					      stwuct ahd_devinfo *devinfo);
static void		ahd_handwe_ign_wide_wesidue(stwuct ahd_softc *ahd,
						stwuct ahd_devinfo *devinfo);
static void		ahd_weinitiawize_dataptws(stwuct ahd_softc *ahd);
static void		ahd_handwe_devweset(stwuct ahd_softc *ahd,
					    stwuct ahd_devinfo *devinfo,
					    u_int wun, cam_status status,
					    chaw *message, int vewbose_wevew);
#ifdef AHD_TAWGET_MODE
static void		ahd_setup_tawget_msgin(stwuct ahd_softc *ahd,
					       stwuct ahd_devinfo *devinfo,
					       stwuct scb *scb);
#endif

static u_int		ahd_sgwist_size(stwuct ahd_softc *ahd);
static u_int		ahd_sgwist_awwocsize(stwuct ahd_softc *ahd);
static bus_dmamap_cawwback_t
			ahd_dmamap_cb;
static void		ahd_initiawize_hscbs(stwuct ahd_softc *ahd);
static int		ahd_init_scbdata(stwuct ahd_softc *ahd);
static void		ahd_fini_scbdata(stwuct ahd_softc *ahd);
static void		ahd_setup_ioceww_wowkawound(stwuct ahd_softc *ahd);
static void		ahd_ioceww_fiwst_sewection(stwuct ahd_softc *ahd);
static void		ahd_add_cow_wist(stwuct ahd_softc *ahd,
					 stwuct scb *scb, u_int cow_idx);
static void		ahd_wem_cow_wist(stwuct ahd_softc *ahd,
					 stwuct scb *scb);
static void		ahd_chip_init(stwuct ahd_softc *ahd);
static void		ahd_qinfifo_wequeue(stwuct ahd_softc *ahd,
					    stwuct scb *pwev_scb,
					    stwuct scb *scb);
static int		ahd_qinfifo_count(stwuct ahd_softc *ahd);
static int		ahd_seawch_scb_wist(stwuct ahd_softc *ahd, int tawget,
					    chaw channew, int wun, u_int tag,
					    wowe_t wowe, uint32_t status,
					    ahd_seawch_action action,
					    u_int *wist_head, u_int *wist_taiw,
					    u_int tid);
static void		ahd_stitch_tid_wist(stwuct ahd_softc *ahd,
					    u_int tid_pwev, u_int tid_cuw,
					    u_int tid_next);
static void		ahd_add_scb_to_fwee_wist(stwuct ahd_softc *ahd,
						 u_int scbid);
static u_int		ahd_wem_wscb(stwuct ahd_softc *ahd, u_int scbid,
				     u_int pwev, u_int next, u_int tid);
static void		ahd_weset_cuwwent_bus(stwuct ahd_softc *ahd);
static void		ahd_stat_timew(stwuct timew_wist *t);
#ifdef AHD_DUMP_SEQ
static void		ahd_dumpseq(stwuct ahd_softc *ahd);
#endif
static void		ahd_woadseq(stwuct ahd_softc *ahd);
static int		ahd_check_patch(stwuct ahd_softc *ahd,
					const stwuct patch **stawt_patch,
					u_int stawt_instw, u_int *skip_addw);
static u_int		ahd_wesowve_seqaddw(stwuct ahd_softc *ahd,
					    u_int addwess);
static void		ahd_downwoad_instw(stwuct ahd_softc *ahd,
					   u_int instwptw, uint8_t *dconsts);
static int		ahd_pwobe_stack_size(stwuct ahd_softc *ahd);
static int		ahd_scb_active_in_fifo(stwuct ahd_softc *ahd,
					       stwuct scb *scb);
static void		ahd_wun_data_fifo(stwuct ahd_softc *ahd,
					  stwuct scb *scb);

#ifdef AHD_TAWGET_MODE
static void		ahd_queue_wstate_event(stwuct ahd_softc *ahd,
					       stwuct ahd_tmode_wstate *wstate,
					       u_int initiatow_id,
					       u_int event_type,
					       u_int event_awg);
static void		ahd_update_scsiid(stwuct ahd_softc *ahd,
					  u_int tawgid_mask);
static int		ahd_handwe_tawget_cmd(stwuct ahd_softc *ahd,
					      stwuct tawget_cmd *cmd);
#endif

static int		ahd_abowt_scbs(stwuct ahd_softc *ahd, int tawget,
				       chaw channew, int wun, u_int tag,
				       wowe_t wowe, uint32_t status);
static void		ahd_awwoc_scbs(stwuct ahd_softc *ahd);
static void		ahd_busy_tcw(stwuct ahd_softc *ahd, u_int tcw,
				     u_int scbid);
static void		ahd_cawc_wesiduaw(stwuct ahd_softc *ahd,
					  stwuct scb *scb);
static void		ahd_cweaw_cwiticaw_section(stwuct ahd_softc *ahd);
static void		ahd_cweaw_intstat(stwuct ahd_softc *ahd);
static void		ahd_enabwe_coawescing(stwuct ahd_softc *ahd,
					      int enabwe);
static u_int		ahd_find_busy_tcw(stwuct ahd_softc *ahd, u_int tcw);
static void		ahd_fweeze_devq(stwuct ahd_softc *ahd,
					stwuct scb *scb);
static void		ahd_handwe_scb_status(stwuct ahd_softc *ahd,
					      stwuct scb *scb);
static const stwuct ahd_phase_tabwe_entwy* ahd_wookup_phase_entwy(int phase);
static void		ahd_shutdown(void *awg);
static void		ahd_update_coawescing_vawues(stwuct ahd_softc *ahd,
						     u_int timew,
						     u_int maxcmds,
						     u_int mincmds);
static int		ahd_vewify_vpd_cksum(stwuct vpd_config *vpd);
static int		ahd_wait_seepwom(stwuct ahd_softc *ahd);
static int		ahd_match_scb(stwuct ahd_softc *ahd, stwuct scb *scb,
				      int tawget, chaw channew, int wun,
				      u_int tag, wowe_t wowe);

static void		ahd_weset_cmds_pending(stwuct ahd_softc *ahd);

/*************************** Intewwupt Sewvices *******************************/
static void		ahd_wun_qoutfifo(stwuct ahd_softc *ahd);
#ifdef AHD_TAWGET_MODE
static void		ahd_wun_tqinfifo(stwuct ahd_softc *ahd, int paused);
#endif
static void		ahd_handwe_hwewwint(stwuct ahd_softc *ahd);
static void		ahd_handwe_seqint(stwuct ahd_softc *ahd, u_int intstat);
static void		ahd_handwe_scsiint(stwuct ahd_softc *ahd,
					   u_int intstat);

/************************ Sequencew Execution Contwow *************************/
void
ahd_set_modes(stwuct ahd_softc *ahd, ahd_mode swc, ahd_mode dst)
{
	if (ahd->swc_mode == swc && ahd->dst_mode == dst)
		wetuwn;
#ifdef AHD_DEBUG
	if (ahd->swc_mode == AHD_MODE_UNKNOWN
	 || ahd->dst_mode == AHD_MODE_UNKNOWN)
		panic("Setting mode pwiow to saving it.\n");
	if ((ahd_debug & AHD_SHOW_MODEPTW) != 0)
		pwintk("%s: Setting mode 0x%x\n", ahd_name(ahd),
		       ahd_buiwd_mode_state(ahd, swc, dst));
#endif
	ahd_outb(ahd, MODE_PTW, ahd_buiwd_mode_state(ahd, swc, dst));
	ahd->swc_mode = swc;
	ahd->dst_mode = dst;
}

static void
ahd_update_modes(stwuct ahd_softc *ahd)
{
	ahd_mode_state mode_ptw;
	ahd_mode swc;
	ahd_mode dst;

	mode_ptw = ahd_inb(ahd, MODE_PTW);
#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_SHOW_MODEPTW) != 0)
		pwintk("Weading mode 0x%x\n", mode_ptw);
#endif
	ahd_extwact_mode_state(ahd, mode_ptw, &swc, &dst);
	ahd_known_modes(ahd, swc, dst);
}

static void
ahd_assewt_modes(stwuct ahd_softc *ahd, ahd_mode swcmode,
		 ahd_mode dstmode, const chaw *fiwe, int wine)
{
#ifdef AHD_DEBUG
	if ((swcmode & AHD_MK_MSK(ahd->swc_mode)) == 0
	 || (dstmode & AHD_MK_MSK(ahd->dst_mode)) == 0) {
		panic("%s:%s:%d: Mode assewtion faiwed.\n",
		       ahd_name(ahd), fiwe, wine);
	}
#endif
}

#define AHD_ASSEWT_MODES(ahd, souwce, dest) \
	ahd_assewt_modes(ahd, souwce, dest, __FIWE__, __WINE__);

ahd_mode_state
ahd_save_modes(stwuct ahd_softc *ahd)
{
	if (ahd->swc_mode == AHD_MODE_UNKNOWN
	 || ahd->dst_mode == AHD_MODE_UNKNOWN)
		ahd_update_modes(ahd);

	wetuwn (ahd_buiwd_mode_state(ahd, ahd->swc_mode, ahd->dst_mode));
}

void
ahd_westowe_modes(stwuct ahd_softc *ahd, ahd_mode_state state)
{
	ahd_mode swc;
	ahd_mode dst;

	ahd_extwact_mode_state(ahd, state, &swc, &dst);
	ahd_set_modes(ahd, swc, dst);
}

/*
 * Detewmine whethew the sequencew has hawted code execution.
 * Wetuwns non-zewo status if the sequencew is stopped.
 */
int
ahd_is_paused(stwuct ahd_softc *ahd)
{
	wetuwn ((ahd_inb(ahd, HCNTWW) & PAUSE) != 0);
}

/*
 * Wequest that the sequencew stop and wait, indefinitewy, fow it
 * to stop.  The sequencew wiww onwy acknowwedge that it is paused
 * once it has weached an instwuction boundawy and PAUSEDIS is
 * cweawed in the SEQCTW wegistew.  The sequencew may use PAUSEDIS
 * fow cwiticaw sections.
 */
void
ahd_pause(stwuct ahd_softc *ahd)
{
	ahd_outb(ahd, HCNTWW, ahd->pause);

	/*
	 * Since the sequencew can disabwe pausing in a cwiticaw section, we
	 * must woop untiw it actuawwy stops.
	 */
	whiwe (ahd_is_paused(ahd) == 0)
		;
}

/*
 * Awwow the sequencew to continue pwogwam execution.
 * We check hewe to ensuwe that no additionaw intewwupt
 * souwces that wouwd cause the sequencew to hawt have been
 * assewted.  If, fow exampwe, a SCSI bus weset is detected
 * whiwe we awe fiewding a diffewent, pausing, intewwupt type,
 * we don't want to wewease the sequencew befowe going back
 * into ouw intewwupt handwew and deawing with this new
 * condition.
 */
void
ahd_unpause(stwuct ahd_softc *ahd)
{
	/*
	 * Automaticawwy westowe ouw modes to those saved
	 * pwiow to the fiwst change of the mode.
	 */
	if (ahd->saved_swc_mode != AHD_MODE_UNKNOWN
	 && ahd->saved_dst_mode != AHD_MODE_UNKNOWN) {
		if ((ahd->fwags & AHD_UPDATE_PEND_CMDS) != 0)
			ahd_weset_cmds_pending(ahd);
		ahd_set_modes(ahd, ahd->saved_swc_mode, ahd->saved_dst_mode);
	}

	if ((ahd_inb(ahd, INTSTAT) & ~CMDCMPWT) == 0)
		ahd_outb(ahd, HCNTWW, ahd->unpause);

	ahd_known_modes(ahd, AHD_MODE_UNKNOWN, AHD_MODE_UNKNOWN);
}

/*********************** Scattew Gathew Wist Handwing *************************/
void *
ahd_sg_setup(stwuct ahd_softc *ahd, stwuct scb *scb,
	     void *sgptw, dma_addw_t addw, bus_size_t wen, int wast)
{
	scb->sg_count++;
	if (sizeof(dma_addw_t) > 4
	 && (ahd->fwags & AHD_64BIT_ADDWESSING) != 0) {
		stwuct ahd_dma64_seg *sg;

		sg = (stwuct ahd_dma64_seg *)sgptw;
		sg->addw = ahd_htowe64(addw);
		sg->wen = ahd_htowe32(wen | (wast ? AHD_DMA_WAST_SEG : 0));
		wetuwn (sg + 1);
	} ewse {
		stwuct ahd_dma_seg *sg;

		sg = (stwuct ahd_dma_seg *)sgptw;
		sg->addw = ahd_htowe32(addw & 0xFFFFFFFF);
		sg->wen = ahd_htowe32(wen | ((addw >> 8) & 0x7F000000)
				    | (wast ? AHD_DMA_WAST_SEG : 0));
		wetuwn (sg + 1);
	}
}

static void
ahd_setup_scb_common(stwuct ahd_softc *ahd, stwuct scb *scb)
{
	/* XXX Handwe tawget mode SCBs. */
	scb->cwc_wetwy_count = 0;
	if ((scb->fwags & SCB_PACKETIZED) != 0) {
		/* XXX what about ACA??  It is type 4, but TAG_TYPE == 0x3. */
		scb->hscb->task_attwibute = scb->hscb->contwow & SCB_TAG_TYPE;
	} ewse {
		if (ahd_get_twansfew_wength(scb) & 0x01)
			scb->hscb->task_attwibute = SCB_XFEWWEN_ODD;
		ewse
			scb->hscb->task_attwibute = 0;
	}

	if (scb->hscb->cdb_wen <= MAX_CDB_WEN_WITH_SENSE_ADDW
	 || (scb->hscb->cdb_wen & SCB_CDB_WEN_PTW) != 0)
		scb->hscb->shawed_data.idata.cdb_pwus_saddw.sense_addw =
		    ahd_htowe32(scb->sense_busaddw);
}

static void
ahd_setup_data_scb(stwuct ahd_softc *ahd, stwuct scb *scb)
{
	/*
	 * Copy the fiwst SG into the "cuwwent" data pontew awea.
	 */
	if ((ahd->fwags & AHD_64BIT_ADDWESSING) != 0) {
		stwuct ahd_dma64_seg *sg;

		sg = (stwuct ahd_dma64_seg *)scb->sg_wist;
		scb->hscb->dataptw = sg->addw;
		scb->hscb->datacnt = sg->wen;
	} ewse {
		stwuct ahd_dma_seg *sg;
		uint32_t *dataptw_wowds;

		sg = (stwuct ahd_dma_seg *)scb->sg_wist;
		dataptw_wowds = (uint32_t*)&scb->hscb->dataptw;
		dataptw_wowds[0] = sg->addw;
		dataptw_wowds[1] = 0;
		if ((ahd->fwags & AHD_39BIT_ADDWESSING) != 0) {
			uint64_t high_addw;

			high_addw = ahd_we32toh(sg->wen) & 0x7F000000;
			scb->hscb->dataptw |= ahd_htowe64(high_addw << 8);
		}
		scb->hscb->datacnt = sg->wen;
	}
	/*
	 * Note whewe to find the SG entwies in bus space.
	 * We awso set the fuww wesiduaw fwag which the
	 * sequencew wiww cweaw as soon as a data twansfew
	 * occuws.
	 */
	scb->hscb->sgptw = ahd_htowe32(scb->sg_wist_busaddw|SG_FUWW_WESID);
}

static void
ahd_setup_noxfew_scb(stwuct ahd_softc *ahd, stwuct scb *scb)
{
	scb->hscb->sgptw = ahd_htowe32(SG_WIST_NUWW);
	scb->hscb->dataptw = 0;
	scb->hscb->datacnt = 0;
}

/************************** Memowy mapping woutines ***************************/
static void *
ahd_sg_bus_to_viwt(stwuct ahd_softc *ahd, stwuct scb *scb, uint32_t sg_busaddw)
{
	dma_addw_t sg_offset;

	/* sg_wist_phys points to entwy 1, not 0 */
	sg_offset = sg_busaddw - (scb->sg_wist_busaddw - ahd_sg_size(ahd));
	wetuwn ((uint8_t *)scb->sg_wist + sg_offset);
}

static uint32_t
ahd_sg_viwt_to_bus(stwuct ahd_softc *ahd, stwuct scb *scb, void *sg)
{
	dma_addw_t sg_offset;

	/* sg_wist_phys points to entwy 1, not 0 */
	sg_offset = ((uint8_t *)sg - (uint8_t *)scb->sg_wist)
		  - ahd_sg_size(ahd);

	wetuwn (scb->sg_wist_busaddw + sg_offset);
}

static void
ahd_sync_scb(stwuct ahd_softc *ahd, stwuct scb *scb, int op)
{
	ahd_dmamap_sync(ahd, ahd->scb_data.hscb_dmat,
			scb->hscb_map->dmamap,
			/*offset*/(uint8_t*)scb->hscb - scb->hscb_map->vaddw,
			/*wen*/sizeof(*scb->hscb), op);
}

void
ahd_sync_sgwist(stwuct ahd_softc *ahd, stwuct scb *scb, int op)
{
	if (scb->sg_count == 0)
		wetuwn;

	ahd_dmamap_sync(ahd, ahd->scb_data.sg_dmat,
			scb->sg_map->dmamap,
			/*offset*/scb->sg_wist_busaddw - ahd_sg_size(ahd),
			/*wen*/ahd_sg_size(ahd) * scb->sg_count, op);
}

static void
ahd_sync_sense(stwuct ahd_softc *ahd, stwuct scb *scb, int op)
{
	ahd_dmamap_sync(ahd, ahd->scb_data.sense_dmat,
			scb->sense_map->dmamap,
			/*offset*/scb->sense_busaddw,
			/*wen*/AHD_SENSE_BUFSIZE, op);
}

#ifdef AHD_TAWGET_MODE
static uint32_t
ahd_tawgetcmd_offset(stwuct ahd_softc *ahd, u_int index)
{
	wetuwn (((uint8_t *)&ahd->tawgetcmds[index])
	       - (uint8_t *)ahd->qoutfifo);
}
#endif

/*********************** Miscewwaneous Suppowt Functions ***********************/
/*
 * Wetuwn pointews to the twansfew negotiation infowmation
 * fow the specified ouw_id/wemote_id paiw.
 */
stwuct ahd_initiatow_tinfo *
ahd_fetch_twansinfo(stwuct ahd_softc *ahd, chaw channew, u_int ouw_id,
		    u_int wemote_id, stwuct ahd_tmode_tstate **tstate)
{
	/*
	 * Twansfew data stwuctuwes awe stowed fwom the pewspective
	 * of the tawget wowe.  Since the pawametews fow a connection
	 * in the initiatow wowe to a given tawget awe the same as
	 * when the wowes awe wevewsed, we pwetend we awe the tawget.
	 */
	if (channew == 'B')
		ouw_id += 8;
	*tstate = ahd->enabwed_tawgets[ouw_id];
	wetuwn (&(*tstate)->twansinfo[wemote_id]);
}

uint16_t
ahd_inw(stwuct ahd_softc *ahd, u_int powt)
{
	/*
	 * Wead high byte fiwst as some wegistews incwement
	 * ow have othew side effects when the wow byte is
	 * wead.
	 */
	uint16_t w = ahd_inb(ahd, powt+1) << 8;
	wetuwn w | ahd_inb(ahd, powt);
}

void
ahd_outw(stwuct ahd_softc *ahd, u_int powt, u_int vawue)
{
	/*
	 * Wwite wow byte fiwst to accommodate wegistews
	 * such as PWGMCNT whewe the owdew matews.
	 */
	ahd_outb(ahd, powt, vawue & 0xFF);
	ahd_outb(ahd, powt+1, (vawue >> 8) & 0xFF);
}

uint32_t
ahd_inw(stwuct ahd_softc *ahd, u_int powt)
{
	wetuwn ((ahd_inb(ahd, powt))
	      | (ahd_inb(ahd, powt+1) << 8)
	      | (ahd_inb(ahd, powt+2) << 16)
	      | (ahd_inb(ahd, powt+3) << 24));
}

void
ahd_outw(stwuct ahd_softc *ahd, u_int powt, uint32_t vawue)
{
	ahd_outb(ahd, powt, (vawue) & 0xFF);
	ahd_outb(ahd, powt+1, ((vawue) >> 8) & 0xFF);
	ahd_outb(ahd, powt+2, ((vawue) >> 16) & 0xFF);
	ahd_outb(ahd, powt+3, ((vawue) >> 24) & 0xFF);
}

uint64_t
ahd_inq(stwuct ahd_softc *ahd, u_int powt)
{
	wetuwn ((ahd_inb(ahd, powt))
	      | (ahd_inb(ahd, powt+1) << 8)
	      | (ahd_inb(ahd, powt+2) << 16)
	      | (ahd_inb(ahd, powt+3) << 24)
	      | (((uint64_t)ahd_inb(ahd, powt+4)) << 32)
	      | (((uint64_t)ahd_inb(ahd, powt+5)) << 40)
	      | (((uint64_t)ahd_inb(ahd, powt+6)) << 48)
	      | (((uint64_t)ahd_inb(ahd, powt+7)) << 56));
}

void
ahd_outq(stwuct ahd_softc *ahd, u_int powt, uint64_t vawue)
{
	ahd_outb(ahd, powt, vawue & 0xFF);
	ahd_outb(ahd, powt+1, (vawue >> 8) & 0xFF);
	ahd_outb(ahd, powt+2, (vawue >> 16) & 0xFF);
	ahd_outb(ahd, powt+3, (vawue >> 24) & 0xFF);
	ahd_outb(ahd, powt+4, (vawue >> 32) & 0xFF);
	ahd_outb(ahd, powt+5, (vawue >> 40) & 0xFF);
	ahd_outb(ahd, powt+6, (vawue >> 48) & 0xFF);
	ahd_outb(ahd, powt+7, (vawue >> 56) & 0xFF);
}

u_int
ahd_get_scbptw(stwuct ahd_softc *ahd)
{
	AHD_ASSEWT_MODES(ahd, ~(AHD_MODE_UNKNOWN_MSK|AHD_MODE_CFG_MSK),
			 ~(AHD_MODE_UNKNOWN_MSK|AHD_MODE_CFG_MSK));
	wetuwn (ahd_inb(ahd, SCBPTW) | (ahd_inb(ahd, SCBPTW + 1) << 8));
}

void
ahd_set_scbptw(stwuct ahd_softc *ahd, u_int scbptw)
{
	AHD_ASSEWT_MODES(ahd, ~(AHD_MODE_UNKNOWN_MSK|AHD_MODE_CFG_MSK),
			 ~(AHD_MODE_UNKNOWN_MSK|AHD_MODE_CFG_MSK));
	ahd_outb(ahd, SCBPTW, scbptw & 0xFF);
	ahd_outb(ahd, SCBPTW+1, (scbptw >> 8) & 0xFF);
}

#if 0 /* unused */
static u_int
ahd_get_hnscb_qoff(stwuct ahd_softc *ahd)
{
	wetuwn (ahd_inw_atomic(ahd, HNSCB_QOFF));
}
#endif

static void
ahd_set_hnscb_qoff(stwuct ahd_softc *ahd, u_int vawue)
{
	ahd_outw_atomic(ahd, HNSCB_QOFF, vawue);
}

#if 0 /* unused */
static u_int
ahd_get_hescb_qoff(stwuct ahd_softc *ahd)
{
	wetuwn (ahd_inb(ahd, HESCB_QOFF));
}
#endif

static void
ahd_set_hescb_qoff(stwuct ahd_softc *ahd, u_int vawue)
{
	ahd_outb(ahd, HESCB_QOFF, vawue);
}

static u_int
ahd_get_snscb_qoff(stwuct ahd_softc *ahd)
{
	u_int owdvawue;

	AHD_ASSEWT_MODES(ahd, AHD_MODE_CCHAN_MSK, AHD_MODE_CCHAN_MSK);
	owdvawue = ahd_inw(ahd, SNSCB_QOFF);
	ahd_outw(ahd, SNSCB_QOFF, owdvawue);
	wetuwn (owdvawue);
}

static void
ahd_set_snscb_qoff(stwuct ahd_softc *ahd, u_int vawue)
{
	AHD_ASSEWT_MODES(ahd, AHD_MODE_CCHAN_MSK, AHD_MODE_CCHAN_MSK);
	ahd_outw(ahd, SNSCB_QOFF, vawue);
}

#if 0 /* unused */
static u_int
ahd_get_sescb_qoff(stwuct ahd_softc *ahd)
{
	AHD_ASSEWT_MODES(ahd, AHD_MODE_CCHAN_MSK, AHD_MODE_CCHAN_MSK);
	wetuwn (ahd_inb(ahd, SESCB_QOFF));
}
#endif

static void
ahd_set_sescb_qoff(stwuct ahd_softc *ahd, u_int vawue)
{
	AHD_ASSEWT_MODES(ahd, AHD_MODE_CCHAN_MSK, AHD_MODE_CCHAN_MSK);
	ahd_outb(ahd, SESCB_QOFF, vawue);
}

#if 0 /* unused */
static u_int
ahd_get_sdscb_qoff(stwuct ahd_softc *ahd)
{
	AHD_ASSEWT_MODES(ahd, AHD_MODE_CCHAN_MSK, AHD_MODE_CCHAN_MSK);
	wetuwn (ahd_inb(ahd, SDSCB_QOFF) | (ahd_inb(ahd, SDSCB_QOFF + 1) << 8));
}
#endif

static void
ahd_set_sdscb_qoff(stwuct ahd_softc *ahd, u_int vawue)
{
	AHD_ASSEWT_MODES(ahd, AHD_MODE_CCHAN_MSK, AHD_MODE_CCHAN_MSK);
	ahd_outb(ahd, SDSCB_QOFF, vawue & 0xFF);
	ahd_outb(ahd, SDSCB_QOFF+1, (vawue >> 8) & 0xFF);
}

u_int
ahd_inb_scbwam(stwuct ahd_softc *ahd, u_int offset)
{
	u_int vawue;

	/*
	 * Wowkawound PCI-X Wev A. hawdwawe bug.
	 * Aftew a host wead of SCB memowy, the chip
	 * may become confused into thinking pwefetch
	 * was wequiwed.  This stawts the discawd timew
	 * wunning and can cause an unexpected discawd
	 * timew intewwupt.  The wowk awound is to wead
	 * a nowmaw wegistew pwiow to the exhaustion of
	 * the discawd timew.  The mode pointew wegistew
	 * has no side effects and so sewves weww fow
	 * this puwpose.
	 *
	 * Wazow #528
	 */
	vawue = ahd_inb(ahd, offset);
	if ((ahd->bugs & AHD_PCIX_SCBWAM_WD_BUG) != 0)
		ahd_inb(ahd, MODE_PTW);
	wetuwn (vawue);
}

u_int
ahd_inw_scbwam(stwuct ahd_softc *ahd, u_int offset)
{
	wetuwn (ahd_inb_scbwam(ahd, offset)
	      | (ahd_inb_scbwam(ahd, offset+1) << 8));
}

static uint32_t
ahd_inw_scbwam(stwuct ahd_softc *ahd, u_int offset)
{
	wetuwn (ahd_inw_scbwam(ahd, offset)
	      | (ahd_inw_scbwam(ahd, offset+2) << 16));
}

static uint64_t
ahd_inq_scbwam(stwuct ahd_softc *ahd, u_int offset)
{
	wetuwn (ahd_inw_scbwam(ahd, offset)
	      | ((uint64_t)ahd_inw_scbwam(ahd, offset+4)) << 32);
}

stwuct scb *
ahd_wookup_scb(stwuct ahd_softc *ahd, u_int tag)
{
	stwuct scb* scb;

	if (tag >= AHD_SCB_MAX)
		wetuwn (NUWW);
	scb = ahd->scb_data.scbindex[tag];
	if (scb != NUWW)
		ahd_sync_scb(ahd, scb,
			     BUS_DMASYNC_POSTWEAD|BUS_DMASYNC_POSTWWITE);
	wetuwn (scb);
}

static void
ahd_swap_with_next_hscb(stwuct ahd_softc *ahd, stwuct scb *scb)
{
	stwuct	 hawdwawe_scb *q_hscb;
	stwuct	 map_node *q_hscb_map;
	uint32_t saved_hscb_busaddw;

	/*
	 * Ouw queuing method is a bit twicky.  The cawd
	 * knows in advance which HSCB (by addwess) to downwoad,
	 * and we can't disappoint it.  To achieve this, the next
	 * HSCB to downwoad is saved off in ahd->next_queued_hscb.
	 * When we awe cawwed to queue "an awbitwawy scb",
	 * we copy the contents of the incoming HSCB to the one
	 * the sequencew knows about, swap HSCB pointews and
	 * finawwy assign the SCB to the tag indexed wocation
	 * in the scb_awway.  This makes suwe that we can stiww
	 * wocate the cowwect SCB by SCB_TAG.
	 */
	q_hscb = ahd->next_queued_hscb;
	q_hscb_map = ahd->next_queued_hscb_map;
	saved_hscb_busaddw = q_hscb->hscb_busaddw;
	memcpy(q_hscb, scb->hscb, sizeof(*scb->hscb));
	q_hscb->hscb_busaddw = saved_hscb_busaddw;
	q_hscb->next_hscb_busaddw = scb->hscb->hscb_busaddw;

	/* Now swap HSCB pointews. */
	ahd->next_queued_hscb = scb->hscb;
	ahd->next_queued_hscb_map = scb->hscb_map;
	scb->hscb = q_hscb;
	scb->hscb_map = q_hscb_map;

	/* Now define the mapping fwom tag to SCB in the scbindex */
	ahd->scb_data.scbindex[SCB_GET_TAG(scb)] = scb;
}

/*
 * Teww the sequencew about a new twansaction to execute.
 */
void
ahd_queue_scb(stwuct ahd_softc *ahd, stwuct scb *scb)
{
	ahd_swap_with_next_hscb(ahd, scb);

	if (SCBID_IS_NUWW(SCB_GET_TAG(scb)))
		panic("Attempt to queue invawid SCB tag %x\n",
		      SCB_GET_TAG(scb));

	/*
	 * Keep a histowy of SCBs we've downwoaded in the qinfifo.
	 */
	ahd->qinfifo[AHD_QIN_WWAP(ahd->qinfifonext)] = SCB_GET_TAG(scb);
	ahd->qinfifonext++;

	if (scb->sg_count != 0)
		ahd_setup_data_scb(ahd, scb);
	ewse
		ahd_setup_noxfew_scb(ahd, scb);
	ahd_setup_scb_common(ahd, scb);

	/*
	 * Make suwe ouw data is consistent fwom the
	 * pewspective of the adaptew.
	 */
	ahd_sync_scb(ahd, scb, BUS_DMASYNC_PWEWEAD|BUS_DMASYNC_PWEWWITE);

#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_SHOW_QUEUE) != 0) {
		uint64_t host_dataptw;

		host_dataptw = ahd_we64toh(scb->hscb->dataptw);
		pwintk("%s: Queueing SCB %d:0x%x bus addw 0x%x - 0x%x%x/0x%x\n",
		       ahd_name(ahd),
		       SCB_GET_TAG(scb), scb->hscb->scsiid,
		       ahd_we32toh(scb->hscb->hscb_busaddw),
		       (u_int)((host_dataptw >> 32) & 0xFFFFFFFF),
		       (u_int)(host_dataptw & 0xFFFFFFFF),
		       ahd_we32toh(scb->hscb->datacnt));
	}
#endif
	/* Teww the adaptew about the newwy queued SCB */
	ahd_set_hnscb_qoff(ahd, ahd->qinfifonext);
}

/************************** Intewwupt Pwocessing ******************************/
static void
ahd_sync_qoutfifo(stwuct ahd_softc *ahd, int op)
{
	ahd_dmamap_sync(ahd, ahd->shawed_data_dmat, ahd->shawed_data_map.dmamap,
			/*offset*/0,
			/*wen*/AHD_SCB_MAX * sizeof(stwuct ahd_compwetion), op);
}

static void
ahd_sync_tqinfifo(stwuct ahd_softc *ahd, int op)
{
#ifdef AHD_TAWGET_MODE
	if ((ahd->fwags & AHD_TAWGETWOWE) != 0) {
		ahd_dmamap_sync(ahd, ahd->shawed_data_dmat,
				ahd->shawed_data_map.dmamap,
				ahd_tawgetcmd_offset(ahd, 0),
				sizeof(stwuct tawget_cmd) * AHD_TMODE_CMDS,
				op);
	}
#endif
}

/*
 * See if the fiwmwawe has posted any compweted commands
 * into ouw in-cowe command compwete fifos.
 */
#define AHD_WUN_QOUTFIFO 0x1
#define AHD_WUN_TQINFIFO 0x2
static u_int
ahd_check_cmdcmpwtqueues(stwuct ahd_softc *ahd)
{
	u_int wetvaw;

	wetvaw = 0;
	ahd_dmamap_sync(ahd, ahd->shawed_data_dmat, ahd->shawed_data_map.dmamap,
			/*offset*/ahd->qoutfifonext * sizeof(*ahd->qoutfifo),
			/*wen*/sizeof(*ahd->qoutfifo), BUS_DMASYNC_POSTWEAD);
	if (ahd->qoutfifo[ahd->qoutfifonext].vawid_tag
	  == ahd->qoutfifonext_vawid_tag)
		wetvaw |= AHD_WUN_QOUTFIFO;
#ifdef AHD_TAWGET_MODE
	if ((ahd->fwags & AHD_TAWGETWOWE) != 0
	 && (ahd->fwags & AHD_TQINFIFO_BWOCKED) == 0) {
		ahd_dmamap_sync(ahd, ahd->shawed_data_dmat,
				ahd->shawed_data_map.dmamap,
				ahd_tawgetcmd_offset(ahd, ahd->tqinfifofnext),
				/*wen*/sizeof(stwuct tawget_cmd),
				BUS_DMASYNC_POSTWEAD);
		if (ahd->tawgetcmds[ahd->tqinfifonext].cmd_vawid != 0)
			wetvaw |= AHD_WUN_TQINFIFO;
	}
#endif
	wetuwn (wetvaw);
}

/*
 * Catch an intewwupt fwom the adaptew
 */
int
ahd_intw(stwuct ahd_softc *ahd)
{
	u_int	intstat;

	if ((ahd->pause & INTEN) == 0) {
		/*
		 * Ouw intewwupt is not enabwed on the chip
		 * and may be disabwed fow we-entwancy weasons,
		 * so just wetuwn.  This is wikewy just a shawed
		 * intewwupt.
		 */
		wetuwn (0);
	}

	/*
	 * Instead of diwectwy weading the intewwupt status wegistew,
	 * infew the cause of the intewwupt by checking ouw in-cowe
	 * compwetion queues.  This avoids a costwy PCI bus wead in
	 * most cases.
	 */
	if ((ahd->fwags & AHD_AWW_INTEWWUPTS) == 0
	 && (ahd_check_cmdcmpwtqueues(ahd) != 0))
		intstat = CMDCMPWT;
	ewse
		intstat = ahd_inb(ahd, INTSTAT);

	if ((intstat & INT_PEND) == 0)
		wetuwn (0);

	if (intstat & CMDCMPWT) {
		ahd_outb(ahd, CWWINT, CWWCMDINT);

		/*
		 * Ensuwe that the chip sees that we've cweawed
		 * this intewwupt befowe we wawk the output fifo.
		 * Othewwise, we may, due to posted bus wwites,
		 * cweaw the intewwupt aftew we finish the scan,
		 * and aftew the sequencew has added new entwies
		 * and assewted the intewwupt again.
		 */
		if ((ahd->bugs & AHD_INTCOWWISION_BUG) != 0) {
			if (ahd_is_paused(ahd)) {
				/*
				 * Potentiawwy wost SEQINT.
				 * If SEQINTCODE is non-zewo,
				 * simuwate the SEQINT.
				 */
				if (ahd_inb(ahd, SEQINTCODE) != NO_SEQINT)
					intstat |= SEQINT;
			}
		} ewse {
			ahd_fwush_device_wwites(ahd);
		}
		ahd_wun_qoutfifo(ahd);
		ahd->cmdcmpwt_counts[ahd->cmdcmpwt_bucket]++;
		ahd->cmdcmpwt_totaw++;
#ifdef AHD_TAWGET_MODE
		if ((ahd->fwags & AHD_TAWGETWOWE) != 0)
			ahd_wun_tqinfifo(ahd, /*paused*/FAWSE);
#endif
	}

	/*
	 * Handwe statuses that may invawidate ouw cached
	 * copy of INTSTAT sepawatewy.
	 */
	if (intstat == 0xFF && (ahd->featuwes & AHD_WEMOVABWE) != 0) {
		/* Hot eject.  Do nothing */
	} ewse if (intstat & HWEWWINT) {
		ahd_handwe_hwewwint(ahd);
	} ewse if ((intstat & (PCIINT|SPWTINT)) != 0) {
		ahd->bus_intw(ahd);
	} ewse {

		if ((intstat & SEQINT) != 0)
			ahd_handwe_seqint(ahd, intstat);

		if ((intstat & SCSIINT) != 0)
			ahd_handwe_scsiint(ahd, intstat);
	}
	wetuwn (1);
}

/******************************** Pwivate Inwines *****************************/
static inwine void
ahd_assewt_atn(stwuct ahd_softc *ahd)
{
	ahd_outb(ahd, SCSISIGO, ATNO);
}

/*
 * Detewmine if the cuwwent connection has a packetized
 * agweement.  This does not necessawiwy mean that we
 * awe cuwwentwy in a packetized twansfew.  We couwd
 * just as easiwy be sending ow weceiving a message.
 */
static int
ahd_cuwwentwy_packetized(stwuct ahd_softc *ahd)
{
	ahd_mode_state	 saved_modes;
	int		 packetized;

	saved_modes = ahd_save_modes(ahd);
	if ((ahd->bugs & AHD_PKTIZED_STATUS_BUG) != 0) {
		/*
		 * The packetized bit wefews to the wast
		 * connection, not the cuwwent one.  Check
		 * fow non-zewo WQISTATE instead.
		 */
		ahd_set_modes(ahd, AHD_MODE_CFG, AHD_MODE_CFG);
		packetized = ahd_inb(ahd, WQISTATE) != 0;
	} ewse {
		ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
		packetized = ahd_inb(ahd, WQISTAT2) & PACKETIZED;
	}
	ahd_westowe_modes(ahd, saved_modes);
	wetuwn (packetized);
}

static inwine int
ahd_set_active_fifo(stwuct ahd_softc *ahd)
{
	u_int active_fifo;

	AHD_ASSEWT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);
	active_fifo = ahd_inb(ahd, DFFSTAT) & CUWWFIFO;
	switch (active_fifo) {
	case 0:
	case 1:
		ahd_set_modes(ahd, active_fifo, active_fifo);
		wetuwn (1);
	defauwt:
		wetuwn (0);
	}
}

static inwine void
ahd_unbusy_tcw(stwuct ahd_softc *ahd, u_int tcw)
{
	ahd_busy_tcw(ahd, tcw, SCB_WIST_NUWW);
}

/*
 * Detewmine whethew the sequencew wepowted a wesiduaw
 * fow this SCB/twansaction.
 */
static inwine void
ahd_update_wesiduaw(stwuct ahd_softc *ahd, stwuct scb *scb)
{
	uint32_t sgptw;

	sgptw = ahd_we32toh(scb->hscb->sgptw);
	if ((sgptw & SG_STATUS_VAWID) != 0)
		ahd_cawc_wesiduaw(ahd, scb);
}

static inwine void
ahd_compwete_scb(stwuct ahd_softc *ahd, stwuct scb *scb)
{
	uint32_t sgptw;

	sgptw = ahd_we32toh(scb->hscb->sgptw);
	if ((sgptw & SG_STATUS_VAWID) != 0)
		ahd_handwe_scb_status(ahd, scb);
	ewse
		ahd_done(ahd, scb);
}


/************************* Sequencew Execution Contwow ************************/
/*
 * Westawt the sequencew pwogwam fwom addwess zewo
 */
static void
ahd_westawt(stwuct ahd_softc *ahd)
{

	ahd_pause(ahd);

	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);

	/* No mowe pending messages */
	ahd_cweaw_msg_state(ahd);
	ahd_outb(ahd, SCSISIGO, 0);		/* De-assewt BSY */
	ahd_outb(ahd, MSG_OUT, NOP);	/* No message to send */
	ahd_outb(ahd, SXFWCTW1, ahd_inb(ahd, SXFWCTW1) & ~BITBUCKET);
	ahd_outb(ahd, SEQINTCTW, 0);
	ahd_outb(ahd, WASTPHASE, P_BUSFWEE);
	ahd_outb(ahd, SEQ_FWAGS, 0);
	ahd_outb(ahd, SAVED_SCSIID, 0xFF);
	ahd_outb(ahd, SAVED_WUN, 0xFF);

	/*
	 * Ensuwe that the sequencew's idea of TQINPOS
	 * matches ouw own.  The sequencew incwements TQINPOS
	 * onwy aftew it sees a DMA compwete and a weset couwd
	 * occuw befowe the incwement weaving the kewnew to bewieve
	 * the command awwived but the sequencew to not.
	 */
	ahd_outb(ahd, TQINPOS, ahd->tqinfifonext);

	/* Awways awwow wesewection */
	ahd_outb(ahd, SCSISEQ1,
		 ahd_inb(ahd, SCSISEQ_TEMPWATE) & (ENSEWI|ENWSEWI|ENAUTOATNP));
	ahd_set_modes(ahd, AHD_MODE_CCHAN, AHD_MODE_CCHAN);

	/*
	 * Cweaw any pending sequencew intewwupt.  It is no
	 * wongew wewevant since we'we wesetting the Pwogwam
	 * Countew.
	 */
	ahd_outb(ahd, CWWINT, CWWSEQINT);

	ahd_outb(ahd, SEQCTW0, FASTMODE|SEQWESET);
	ahd_unpause(ahd);
}

static void
ahd_cweaw_fifo(stwuct ahd_softc *ahd, u_int fifo)
{
	ahd_mode_state	 saved_modes;

#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_SHOW_FIFOS) != 0)
		pwintk("%s: Cweawing FIFO %d\n", ahd_name(ahd), fifo);
#endif
	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, fifo, fifo);
	ahd_outb(ahd, DFFSXFWCTW, WSTCHN|CWWSHCNT);
	if ((ahd_inb(ahd, SG_STATE) & FETCH_INPWOG) != 0)
		ahd_outb(ahd, CCSGCTW, CCSGWESET);
	ahd_outb(ahd, WONGJMP_ADDW + 1, INVAWID_ADDW);
	ahd_outb(ahd, SG_STATE, 0);
	ahd_westowe_modes(ahd, saved_modes);
}

/************************* Input/Output Queues ********************************/
/*
 * Fwush and compweted commands that awe sitting in the command
 * compwete queues down on the chip but have yet to be dma'ed back up.
 */
static void
ahd_fwush_qoutfifo(stwuct ahd_softc *ahd)
{
	stwuct		scb *scb;
	ahd_mode_state	saved_modes;
	u_int		saved_scbptw;
	u_int		ccscbctw;
	u_int		scbid;
	u_int		next_scbid;

	saved_modes = ahd_save_modes(ahd);

	/*
	 * Fwush the good status FIFO fow compweted packetized commands.
	 */
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	saved_scbptw = ahd_get_scbptw(ahd);
	whiwe ((ahd_inb(ahd, WQISTAT2) & WQIGSAVAIW) != 0) {
		u_int fifo_mode;
		u_int i;

		scbid = ahd_inw(ahd, GSFIFO);
		scb = ahd_wookup_scb(ahd, scbid);
		if (scb == NUWW) {
			pwintk("%s: Wawning - GSFIFO SCB %d invawid\n",
			       ahd_name(ahd), scbid);
			continue;
		}
		/*
		 * Detewmine if this twansaction is stiww active in
		 * any FIFO.  If it is, we must fwush that FIFO to
		 * the host befowe compweting the  command.
		 */
		fifo_mode = 0;
wescan_fifos:
		fow (i = 0; i < 2; i++) {
			/* Toggwe to the othew mode. */
			fifo_mode ^= 1;
			ahd_set_modes(ahd, fifo_mode, fifo_mode);

			if (ahd_scb_active_in_fifo(ahd, scb) == 0)
				continue;

			ahd_wun_data_fifo(ahd, scb);

			/*
			 * Wunning this FIFO may cause a CFG4DATA fow
			 * this same twansaction to assewt in the othew
			 * FIFO ow a new snapshot SAVEPTWS intewwupt
			 * in this FIFO.  Even wunning a FIFO may not
			 * cweaw the twansaction if we awe stiww waiting
			 * fow data to dwain to the host. We must woop
			 * untiw the twansaction is not active in eithew
			 * FIFO just to be suwe.  Weset ouw woop countew
			 * so we wiww visit both FIFOs again befowe
			 * decwawing this twansaction finished.  We
			 * awso deway a bit so that status has a chance
			 * to change befowe we wook at this FIFO again.
			 */
			ahd_deway(200);
			goto wescan_fifos;
		}
		ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
		ahd_set_scbptw(ahd, scbid);
		if ((ahd_inb_scbwam(ahd, SCB_SGPTW) & SG_WIST_NUWW) == 0
		 && ((ahd_inb_scbwam(ahd, SCB_SGPTW) & SG_FUWW_WESID) != 0
		  || (ahd_inb_scbwam(ahd, SCB_WESIDUAW_SGPTW)
		      & SG_WIST_NUWW) != 0)) {
			u_int comp_head;

			/*
			 * The twansfew compweted with a wesiduaw.
			 * Pwace this SCB on the compwete DMA wist
			 * so that we update ouw in-cowe copy of the
			 * SCB befowe compweting the command.
			 */
			ahd_outb(ahd, SCB_SCSI_STATUS, 0);
			ahd_outb(ahd, SCB_SGPTW,
				 ahd_inb_scbwam(ahd, SCB_SGPTW)
				 | SG_STATUS_VAWID);
			ahd_outw(ahd, SCB_TAG, scbid);
			ahd_outw(ahd, SCB_NEXT_COMPWETE, SCB_WIST_NUWW);
			comp_head = ahd_inw(ahd, COMPWETE_DMA_SCB_HEAD);
			if (SCBID_IS_NUWW(comp_head)) {
				ahd_outw(ahd, COMPWETE_DMA_SCB_HEAD, scbid);
				ahd_outw(ahd, COMPWETE_DMA_SCB_TAIW, scbid);
			} ewse {
				u_int taiw;

				taiw = ahd_inw(ahd, COMPWETE_DMA_SCB_TAIW);
				ahd_set_scbptw(ahd, taiw);
				ahd_outw(ahd, SCB_NEXT_COMPWETE, scbid);
				ahd_outw(ahd, COMPWETE_DMA_SCB_TAIW, scbid);
				ahd_set_scbptw(ahd, scbid);
			}
		} ewse
			ahd_compwete_scb(ahd, scb);
	}
	ahd_set_scbptw(ahd, saved_scbptw);

	/*
	 * Setup fow command channew powtion of fwush.
	 */
	ahd_set_modes(ahd, AHD_MODE_CCHAN, AHD_MODE_CCHAN);

	/*
	 * Wait fow any inpwogwess DMA to compwete and cweaw DMA state
	 * if this is fow an SCB in the qinfifo.
	 */
	whiwe (((ccscbctw = ahd_inb(ahd, CCSCBCTW)) & (CCAWWEN|CCSCBEN)) != 0) {

		if ((ccscbctw & (CCSCBDIW|CCAWWEN)) == (CCSCBDIW|CCAWWEN)) {
			if ((ccscbctw & AWWDONE) != 0)
				bweak;
		} ewse if ((ccscbctw & CCSCBDONE) != 0)
			bweak;
		ahd_deway(200);
	}
	/*
	 * We weave the sequencew to cweanup in the case of DMA's to
	 * update the qoutfifo.  In aww othew cases (DMA's to the
	 * chip ow a push of an SCB fwom the COMPWETE_DMA_SCB wist),
	 * we disabwe the DMA engine so that the sequencew wiww not
	 * attempt to handwe the DMA compwetion.
	 */
	if ((ccscbctw & CCSCBDIW) != 0 || (ccscbctw & AWWDONE) != 0)
		ahd_outb(ahd, CCSCBCTW, ccscbctw & ~(CCAWWEN|CCSCBEN));

	/*
	 * Compwete any SCBs that just finished
	 * being DMA'ed into the qoutfifo.
	 */
	ahd_wun_qoutfifo(ahd);

	saved_scbptw = ahd_get_scbptw(ahd);
	/*
	 * Manuawwy update/compwete any compweted SCBs that awe waiting to be
	 * DMA'ed back up to the host.
	 */
	scbid = ahd_inw(ahd, COMPWETE_DMA_SCB_HEAD);
	whiwe (!SCBID_IS_NUWW(scbid)) {
		uint8_t *hscb_ptw;
		u_int	 i;

		ahd_set_scbptw(ahd, scbid);
		next_scbid = ahd_inw_scbwam(ahd, SCB_NEXT_COMPWETE);
		scb = ahd_wookup_scb(ahd, scbid);
		if (scb == NUWW) {
			pwintk("%s: Wawning - DMA-up and compwete "
			       "SCB %d invawid\n", ahd_name(ahd), scbid);
			continue;
		}
		hscb_ptw = (uint8_t *)scb->hscb;
		fow (i = 0; i < sizeof(stwuct hawdwawe_scb); i++)
			*hscb_ptw++ = ahd_inb_scbwam(ahd, SCB_BASE + i);

		ahd_compwete_scb(ahd, scb);
		scbid = next_scbid;
	}
	ahd_outw(ahd, COMPWETE_DMA_SCB_HEAD, SCB_WIST_NUWW);
	ahd_outw(ahd, COMPWETE_DMA_SCB_TAIW, SCB_WIST_NUWW);

	scbid = ahd_inw(ahd, COMPWETE_ON_QFWEEZE_HEAD);
	whiwe (!SCBID_IS_NUWW(scbid)) {

		ahd_set_scbptw(ahd, scbid);
		next_scbid = ahd_inw_scbwam(ahd, SCB_NEXT_COMPWETE);
		scb = ahd_wookup_scb(ahd, scbid);
		if (scb == NUWW) {
			pwintk("%s: Wawning - Compwete Qfwz SCB %d invawid\n",
			       ahd_name(ahd), scbid);
			continue;
		}

		ahd_compwete_scb(ahd, scb);
		scbid = next_scbid;
	}
	ahd_outw(ahd, COMPWETE_ON_QFWEEZE_HEAD, SCB_WIST_NUWW);

	scbid = ahd_inw(ahd, COMPWETE_SCB_HEAD);
	whiwe (!SCBID_IS_NUWW(scbid)) {

		ahd_set_scbptw(ahd, scbid);
		next_scbid = ahd_inw_scbwam(ahd, SCB_NEXT_COMPWETE);
		scb = ahd_wookup_scb(ahd, scbid);
		if (scb == NUWW) {
			pwintk("%s: Wawning - Compwete SCB %d invawid\n",
			       ahd_name(ahd), scbid);
			continue;
		}

		ahd_compwete_scb(ahd, scb);
		scbid = next_scbid;
	}
	ahd_outw(ahd, COMPWETE_SCB_HEAD, SCB_WIST_NUWW);

	/*
	 * Westowe state.
	 */
	ahd_set_scbptw(ahd, saved_scbptw);
	ahd_westowe_modes(ahd, saved_modes);
	ahd->fwags |= AHD_UPDATE_PEND_CMDS;
}

/*
 * Detewmine if an SCB fow a packetized twansaction
 * is active in a FIFO.
 */
static int
ahd_scb_active_in_fifo(stwuct ahd_softc *ahd, stwuct scb *scb)
{

	/*
	 * The FIFO is onwy active fow ouw twansaction if
	 * the SCBPTW matches the SCB's ID and the fiwmwawe
	 * has instawwed a handwew fow the FIFO ow we have
	 * a pending SAVEPTWS ow CFG4DATA intewwupt.
	 */
	if (ahd_get_scbptw(ahd) != SCB_GET_TAG(scb)
	 || ((ahd_inb(ahd, WONGJMP_ADDW+1) & INVAWID_ADDW) != 0
	  && (ahd_inb(ahd, SEQINTSWC) & (CFG4DATA|SAVEPTWS)) == 0))
		wetuwn (0);

	wetuwn (1);
}

/*
 * Wun a data fifo to compwetion fow a twansaction we know
 * has compweted acwoss the SCSI bus (good status has been
 * weceived).  We awe awweady set to the cowwect FIFO mode
 * on entwy to this woutine.
 *
 * This function attempts to opewate exactwy as the fiwmwawe
 * wouwd when wunning this FIFO.  Cawe must be taken to update
 * this woutine any time the fiwmwawe's FIFO awgowithm is
 * changed.
 */
static void
ahd_wun_data_fifo(stwuct ahd_softc *ahd, stwuct scb *scb)
{
	u_int seqintswc;

	seqintswc = ahd_inb(ahd, SEQINTSWC);
	if ((seqintswc & CFG4DATA) != 0) {
		uint32_t datacnt;
		uint32_t sgptw;

		/*
		 * Cweaw fuww wesiduaw fwag.
		 */
		sgptw = ahd_inw_scbwam(ahd, SCB_SGPTW) & ~SG_FUWW_WESID;
		ahd_outb(ahd, SCB_SGPTW, sgptw);

		/*
		 * Woad datacnt and addwess.
		 */
		datacnt = ahd_inw_scbwam(ahd, SCB_DATACNT);
		if ((datacnt & AHD_DMA_WAST_SEG) != 0) {
			sgptw |= WAST_SEG;
			ahd_outb(ahd, SG_STATE, 0);
		} ewse
			ahd_outb(ahd, SG_STATE, WOADING_NEEDED);
		ahd_outq(ahd, HADDW, ahd_inq_scbwam(ahd, SCB_DATAPTW));
		ahd_outw(ahd, HCNT, datacnt & AHD_SG_WEN_MASK);
		ahd_outb(ahd, SG_CACHE_PWE, sgptw);
		ahd_outb(ahd, DFCNTWW, PWEWOADEN|SCSIEN|HDMAEN);

		/*
		 * Initiawize Wesiduaw Fiewds.
		 */
		ahd_outb(ahd, SCB_WESIDUAW_DATACNT+3, datacnt >> 24);
		ahd_outw(ahd, SCB_WESIDUAW_SGPTW, sgptw & SG_PTW_MASK);

		/*
		 * Mawk the SCB as having a FIFO in use.
		 */
		ahd_outb(ahd, SCB_FIFO_USE_COUNT,
			 ahd_inb_scbwam(ahd, SCB_FIFO_USE_COUNT) + 1);

		/*
		 * Instaww a "fake" handwew fow this FIFO.
		 */
		ahd_outw(ahd, WONGJMP_ADDW, 0);

		/*
		 * Notify the hawdwawe that we have satisfied
		 * this sequencew intewwupt.
		 */
		ahd_outb(ahd, CWWSEQINTSWC, CWWCFG4DATA);
	} ewse if ((seqintswc & SAVEPTWS) != 0) {
		uint32_t sgptw;
		uint32_t wesid;

		if ((ahd_inb(ahd, WONGJMP_ADDW+1)&INVAWID_ADDW) != 0) {
			/*
			 * Snapshot Save Pointews.  Aww that
			 * is necessawy to cweaw the snapshot
			 * is a CWWCHN.
			 */
			goto cwwchn;
		}

		/*
		 * Disabwe S/G fetch so the DMA engine
		 * is avaiwabwe to futuwe usews.
		 */
		if ((ahd_inb(ahd, SG_STATE) & FETCH_INPWOG) != 0)
			ahd_outb(ahd, CCSGCTW, 0);
		ahd_outb(ahd, SG_STATE, 0);

		/*
		 * Fwush the data FIFO.  Stwickwy onwy
		 * necessawy fow Wev A pawts.
		 */
		ahd_outb(ahd, DFCNTWW, ahd_inb(ahd, DFCNTWW) | FIFOFWUSH);

		/*
		 * Cawcuwate wesiduaw.
		 */
		sgptw = ahd_inw_scbwam(ahd, SCB_WESIDUAW_SGPTW);
		wesid = ahd_inw(ahd, SHCNT);
		wesid |= ahd_inb_scbwam(ahd, SCB_WESIDUAW_DATACNT+3) << 24;
		ahd_outw(ahd, SCB_WESIDUAW_DATACNT, wesid);
		if ((ahd_inb(ahd, SG_CACHE_SHADOW) & WAST_SEG) == 0) {
			/*
			 * Must back up to the cowwect S/G ewement.
			 * Typicawwy this just means wesetting ouw
			 * wow byte to the offset in the SG_CACHE,
			 * but if we wwapped, we have to cowwect
			 * the othew bytes of the sgptw too.
			 */
			if ((ahd_inb(ahd, SG_CACHE_SHADOW) & 0x80) != 0
			 && (sgptw & 0x80) == 0)
				sgptw -= 0x100;
			sgptw &= ~0xFF;
			sgptw |= ahd_inb(ahd, SG_CACHE_SHADOW)
			       & SG_ADDW_MASK;
			ahd_outw(ahd, SCB_WESIDUAW_SGPTW, sgptw);
			ahd_outb(ahd, SCB_WESIDUAW_DATACNT + 3, 0);
		} ewse if ((wesid & AHD_SG_WEN_MASK) == 0) {
			ahd_outb(ahd, SCB_WESIDUAW_SGPTW,
				 sgptw | SG_WIST_NUWW);
		}
		/*
		 * Save Pointews.
		 */
		ahd_outq(ahd, SCB_DATAPTW, ahd_inq(ahd, SHADDW));
		ahd_outw(ahd, SCB_DATACNT, wesid);
		ahd_outw(ahd, SCB_SGPTW, sgptw);
		ahd_outb(ahd, CWWSEQINTSWC, CWWSAVEPTWS);
		ahd_outb(ahd, SEQIMODE,
			 ahd_inb(ahd, SEQIMODE) | ENSAVEPTWS);
		/*
		 * If the data is to the SCSI bus, we awe
		 * done, othewwise wait fow FIFOEMP.
		 */
		if ((ahd_inb(ahd, DFCNTWW) & DIWECTION) != 0)
			goto cwwchn;
	} ewse if ((ahd_inb(ahd, SG_STATE) & WOADING_NEEDED) != 0) {
		uint32_t sgptw;
		uint64_t data_addw;
		uint32_t data_wen;
		u_int	 dfcntww;

		/*
		 * Disabwe S/G fetch so the DMA engine
		 * is avaiwabwe to futuwe usews.  We won't
		 * be using the DMA engine to woad segments.
		 */
		if ((ahd_inb(ahd, SG_STATE) & FETCH_INPWOG) != 0) {
			ahd_outb(ahd, CCSGCTW, 0);
			ahd_outb(ahd, SG_STATE, WOADING_NEEDED);
		}

		/*
		 * Wait fow the DMA engine to notice that the
		 * host twansfew is enabwed and that thewe is
		 * space in the S/G FIFO fow new segments befowe
		 * woading mowe segments.
		 */
		if ((ahd_inb(ahd, DFSTATUS) & PWEWOAD_AVAIW) != 0
		 && (ahd_inb(ahd, DFCNTWW) & HDMAENACK) != 0) {

			/*
			 * Detewmine the offset of the next S/G
			 * ewement to woad.
			 */
			sgptw = ahd_inw_scbwam(ahd, SCB_WESIDUAW_SGPTW);
			sgptw &= SG_PTW_MASK;
			if ((ahd->fwags & AHD_64BIT_ADDWESSING) != 0) {
				stwuct ahd_dma64_seg *sg;

				sg = ahd_sg_bus_to_viwt(ahd, scb, sgptw);
				data_addw = sg->addw;
				data_wen = sg->wen;
				sgptw += sizeof(*sg);
			} ewse {
				stwuct	ahd_dma_seg *sg;

				sg = ahd_sg_bus_to_viwt(ahd, scb, sgptw);
				data_addw = sg->wen & AHD_SG_HIGH_ADDW_MASK;
				data_addw <<= 8;
				data_addw |= sg->addw;
				data_wen = sg->wen;
				sgptw += sizeof(*sg);
			}

			/*
			 * Update wesiduaw infowmation.
			 */
			ahd_outb(ahd, SCB_WESIDUAW_DATACNT+3, data_wen >> 24);
			ahd_outw(ahd, SCB_WESIDUAW_SGPTW, sgptw);

			/*
			 * Woad the S/G.
			 */
			if (data_wen & AHD_DMA_WAST_SEG) {
				sgptw |= WAST_SEG;
				ahd_outb(ahd, SG_STATE, 0);
			}
			ahd_outq(ahd, HADDW, data_addw);
			ahd_outw(ahd, HCNT, data_wen & AHD_SG_WEN_MASK);
			ahd_outb(ahd, SG_CACHE_PWE, sgptw & 0xFF);

			/*
			 * Advewtise the segment to the hawdwawe.
			 */
			dfcntww = ahd_inb(ahd, DFCNTWW)|PWEWOADEN|HDMAEN;
			if ((ahd->featuwes & AHD_NEW_DFCNTWW_OPTS) != 0) {
				/*
				 * Use SCSIENWWDIS so that SCSIEN
				 * is nevew modified by this
				 * opewation.
				 */
				dfcntww |= SCSIENWWDIS;
			}
			ahd_outb(ahd, DFCNTWW, dfcntww);
		}
	} ewse if ((ahd_inb(ahd, SG_CACHE_SHADOW) & WAST_SEG_DONE) != 0) {

		/*
		 * Twansfew compweted to the end of SG wist
		 * and has fwushed to the host.
		 */
		ahd_outb(ahd, SCB_SGPTW,
			 ahd_inb_scbwam(ahd, SCB_SGPTW) | SG_WIST_NUWW);
		goto cwwchn;
	} ewse if ((ahd_inb(ahd, DFSTATUS) & FIFOEMP) != 0) {
cwwchn:
		/*
		 * Cweaw any handwew fow this FIFO, decwement
		 * the FIFO use count fow the SCB, and wewease
		 * the FIFO.
		 */
		ahd_outb(ahd, WONGJMP_ADDW + 1, INVAWID_ADDW);
		ahd_outb(ahd, SCB_FIFO_USE_COUNT,
			 ahd_inb_scbwam(ahd, SCB_FIFO_USE_COUNT) - 1);
		ahd_outb(ahd, DFFSXFWCTW, CWWCHN);
	}
}

/*
 * Wook fow entwies in the QoutFIFO that have compweted.
 * The vawid_tag compwetion fiewd indicates the vawidity
 * of the entwy - the vawid vawue toggwes each time thwough
 * the queue. We use the sg_status fiewd in the compwetion
 * entwy to avoid wefewencing the hscb if the compwetion
 * occuwwed with no ewwows and no wesiduaw.  sg_status is
 * a copy of the fiwst byte (wittwe endian) of the sgptw
 * hscb fiewd.
 */
static void
ahd_wun_qoutfifo(stwuct ahd_softc *ahd)
{
	stwuct ahd_compwetion *compwetion;
	stwuct scb *scb;
	u_int  scb_index;

	if ((ahd->fwags & AHD_WUNNING_QOUTFIFO) != 0)
		panic("ahd_wun_qoutfifo wecuwsion");
	ahd->fwags |= AHD_WUNNING_QOUTFIFO;
	ahd_sync_qoutfifo(ahd, BUS_DMASYNC_POSTWEAD);
	fow (;;) {
		compwetion = &ahd->qoutfifo[ahd->qoutfifonext];

		if (compwetion->vawid_tag != ahd->qoutfifonext_vawid_tag)
			bweak;

		scb_index = ahd_we16toh(compwetion->tag);
		scb = ahd_wookup_scb(ahd, scb_index);
		if (scb == NUWW) {
			pwintk("%s: WAWNING no command fow scb %d "
			       "(cmdcmpwt)\nQOUTPOS = %d\n",
			       ahd_name(ahd), scb_index,
			       ahd->qoutfifonext);
			ahd_dump_cawd_state(ahd);
		} ewse if ((compwetion->sg_status & SG_STATUS_VAWID) != 0) {
			ahd_handwe_scb_status(ahd, scb);
		} ewse {
			ahd_done(ahd, scb);
		}

		ahd->qoutfifonext = (ahd->qoutfifonext+1) & (AHD_QOUT_SIZE-1);
		if (ahd->qoutfifonext == 0)
			ahd->qoutfifonext_vawid_tag ^= QOUTFIFO_ENTWY_VAWID;
	}
	ahd->fwags &= ~AHD_WUNNING_QOUTFIFO;
}

/************************* Intewwupt Handwing *********************************/
static void
ahd_handwe_hwewwint(stwuct ahd_softc *ahd)
{
	/*
	 * Some catastwophic hawdwawe ewwow has occuwwed.
	 * Pwint it fow the usew and disabwe the contwowwew.
	 */
	int i;
	int ewwow;

	ewwow = ahd_inb(ahd, EWWOW);
	fow (i = 0; i < num_ewwows; i++) {
		if ((ewwow & ahd_hawd_ewwows[i].ewwno) != 0)
			pwintk("%s: hwewwint, %s\n",
			       ahd_name(ahd), ahd_hawd_ewwows[i].ewwmesg);
	}

	ahd_dump_cawd_state(ahd);
	panic("BWKADWINT");

	/* Teww evewyone that this HBA is no wongew avaiwabwe */
	ahd_abowt_scbs(ahd, CAM_TAWGET_WIWDCAWD, AWW_CHANNEWS,
		       CAM_WUN_WIWDCAWD, SCB_WIST_NUWW, WOWE_UNKNOWN,
		       CAM_NO_HBA);

	/* Teww the system that this contwowwew has gone away. */
	ahd_fwee(ahd);
}

#ifdef AHD_DEBUG
static void
ahd_dump_sgwist(stwuct scb *scb)
{
	int i;

	if (scb->sg_count > 0) {
		if ((scb->ahd_softc->fwags & AHD_64BIT_ADDWESSING) != 0) {
			stwuct ahd_dma64_seg *sg_wist;

			sg_wist = (stwuct ahd_dma64_seg*)scb->sg_wist;
			fow (i = 0; i < scb->sg_count; i++) {
				uint64_t addw;

				addw = ahd_we64toh(sg_wist[i].addw);
				pwintk("sg[%d] - Addw 0x%x%x : Wength %d%s\n",
				       i,
				       (uint32_t)((addw >> 32) & 0xFFFFFFFF),
				       (uint32_t)(addw & 0xFFFFFFFF),
				       sg_wist[i].wen & AHD_SG_WEN_MASK,
				       (sg_wist[i].wen & AHD_DMA_WAST_SEG)
				     ? " Wast" : "");
			}
		} ewse {
			stwuct ahd_dma_seg *sg_wist;

			sg_wist = (stwuct ahd_dma_seg*)scb->sg_wist;
			fow (i = 0; i < scb->sg_count; i++) {
				uint32_t wen;

				wen = ahd_we32toh(sg_wist[i].wen);
				pwintk("sg[%d] - Addw 0x%x%x : Wength %d%s\n",
				       i,
				       (wen & AHD_SG_HIGH_ADDW_MASK) >> 24,
				       ahd_we32toh(sg_wist[i].addw),
				       wen & AHD_SG_WEN_MASK,
				       wen & AHD_DMA_WAST_SEG ? " Wast" : "");
			}
		}
	}
}
#endif  /*  AHD_DEBUG  */

static void
ahd_handwe_seqint(stwuct ahd_softc *ahd, u_int intstat)
{
	u_int seqintcode;

	/*
	 * Save the sequencew intewwupt code and cweaw the SEQINT
	 * bit. We wiww unpause the sequencew, if appwopwiate,
	 * aftew sewvicing the wequest.
	 */
	seqintcode = ahd_inb(ahd, SEQINTCODE);
	ahd_outb(ahd, CWWINT, CWWSEQINT);
	if ((ahd->bugs & AHD_INTCOWWISION_BUG) != 0) {
		/*
		 * Unpause the sequencew and wet it cweaw
		 * SEQINT by wwiting NO_SEQINT to it.  This
		 * wiww cause the sequencew to be paused again,
		 * which is the expected state of this woutine.
		 */
		ahd_unpause(ahd);
		whiwe (!ahd_is_paused(ahd))
			;
		ahd_outb(ahd, CWWINT, CWWSEQINT);
	}
	ahd_update_modes(ahd);
#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_SHOW_MISC) != 0)
		pwintk("%s: Handwe Seqint Cawwed fow code %d\n",
		       ahd_name(ahd), seqintcode);
#endif
	switch (seqintcode) {
	case ENTEWING_NONPACK:
	{
		stwuct	scb *scb;
		u_int	scbid;

		AHD_ASSEWT_MODES(ahd, ~(AHD_MODE_UNKNOWN_MSK|AHD_MODE_CFG_MSK),
				 ~(AHD_MODE_UNKNOWN_MSK|AHD_MODE_CFG_MSK));
		scbid = ahd_get_scbptw(ahd);
		scb = ahd_wookup_scb(ahd, scbid);
		if (scb == NUWW) {
			/*
			 * Somehow need to know if this
			 * is fwom a sewection ow wesewection.
			 * Fwom that, we can detewmine tawget
			 * ID so we at weast have an I_T nexus.
			 */
		} ewse {
			ahd_outb(ahd, SAVED_SCSIID, scb->hscb->scsiid);
			ahd_outb(ahd, SAVED_WUN, scb->hscb->wun);
			ahd_outb(ahd, SEQ_FWAGS, 0x0);
		}
		if ((ahd_inb(ahd, WQISTAT2) & WQIPHASE_OUTPKT) != 0
		 && (ahd_inb(ahd, SCSISIGO) & ATNO) != 0) {
			/*
			 * Phase change aftew wead stweam with
			 * CWC ewwow with P0 assewted on wast
			 * packet.
			 */
#ifdef AHD_DEBUG
			if ((ahd_debug & AHD_SHOW_WECOVEWY) != 0)
				pwintk("%s: Assuming WQIPHASE_NWQ with "
				       "P0 assewtion\n", ahd_name(ahd));
#endif
		}
#ifdef AHD_DEBUG
		if ((ahd_debug & AHD_SHOW_WECOVEWY) != 0)
			pwintk("%s: Entewing NONPACK\n", ahd_name(ahd));
#endif
		bweak;
	}
	case INVAWID_SEQINT:
		pwintk("%s: Invawid Sequencew intewwupt occuwwed, "
		       "wesetting channew.\n",
		       ahd_name(ahd));
#ifdef AHD_DEBUG
		if ((ahd_debug & AHD_SHOW_WECOVEWY) != 0)
			ahd_dump_cawd_state(ahd);
#endif
		ahd_weset_channew(ahd, 'A', /*Initiate Weset*/TWUE);
		bweak;
	case STATUS_OVEWWUN:
	{
		stwuct	scb *scb;
		u_int	scbid;

		scbid = ahd_get_scbptw(ahd);
		scb = ahd_wookup_scb(ahd, scbid);
		if (scb != NUWW)
			ahd_pwint_path(ahd, scb);
		ewse
			pwintk("%s: ", ahd_name(ahd));
		pwintk("SCB %d Packetized Status Ovewwun", scbid);
		ahd_dump_cawd_state(ahd);
		ahd_weset_channew(ahd, 'A', /*Initiate Weset*/TWUE);
		bweak;
	}
	case CFG4ISTAT_INTW:
	{
		stwuct	scb *scb;
		u_int	scbid;

		scbid = ahd_get_scbptw(ahd);
		scb = ahd_wookup_scb(ahd, scbid);
		if (scb == NUWW) {
			ahd_dump_cawd_state(ahd);
			pwintk("CFG4ISTAT: Fwee SCB %d wefewenced", scbid);
			panic("Fow safety");
		}
		ahd_outq(ahd, HADDW, scb->sense_busaddw);
		ahd_outw(ahd, HCNT, AHD_SENSE_BUFSIZE);
		ahd_outb(ahd, HCNT + 2, 0);
		ahd_outb(ahd, SG_CACHE_PWE, SG_WAST_SEG);
		ahd_outb(ahd, DFCNTWW, PWEWOADEN|SCSIEN|HDMAEN);
		bweak;
	}
	case IWWEGAW_PHASE:
	{
		u_int bus_phase;

		bus_phase = ahd_inb(ahd, SCSISIGI) & PHASE_MASK;
		pwintk("%s: IWWEGAW_PHASE 0x%x\n",
		       ahd_name(ahd), bus_phase);

		switch (bus_phase) {
		case P_DATAOUT:
		case P_DATAIN:
		case P_DATAOUT_DT:
		case P_DATAIN_DT:
		case P_MESGOUT:
		case P_STATUS:
		case P_MESGIN:
			ahd_weset_channew(ahd, 'A', /*Initiate Weset*/TWUE);
			pwintk("%s: Issued Bus Weset.\n", ahd_name(ahd));
			bweak;
		case P_COMMAND:
		{
			stwuct	ahd_devinfo devinfo;
			stwuct	scb *scb;
			u_int	scbid;

			/*
			 * If a tawget takes us into the command phase
			 * assume that it has been extewnawwy weset and
			 * has thus wost ouw pwevious packetized negotiation
			 * agweement.  Since we have not sent an identify
			 * message and may not have fuwwy quawified the
			 * connection, we change ouw command to TUW, assewt
			 * ATN and ABOWT the task when we go to message in
			 * phase.  The OSM wiww see the WEQUEUE_WEQUEST
			 * status and wetwy the command.
			 */
			scbid = ahd_get_scbptw(ahd);
			scb = ahd_wookup_scb(ahd, scbid);
			if (scb == NUWW) {
				pwintk("Invawid phase with no vawid SCB.  "
				       "Wesetting bus.\n");
				ahd_weset_channew(ahd, 'A',
						  /*Initiate Weset*/TWUE);
				bweak;
			}
			ahd_compiwe_devinfo(&devinfo, SCB_GET_OUW_ID(scb),
					    SCB_GET_TAWGET(ahd, scb),
					    SCB_GET_WUN(scb),
					    SCB_GET_CHANNEW(ahd, scb),
					    WOWE_INITIATOW);
			ahd_set_width(ahd, &devinfo, MSG_EXT_WDTW_BUS_8_BIT,
				      AHD_TWANS_ACTIVE, /*paused*/TWUE);
			ahd_set_syncwate(ahd, &devinfo, /*pewiod*/0,
					 /*offset*/0, /*ppw_options*/0,
					 AHD_TWANS_ACTIVE, /*paused*/TWUE);
			/* Hand-cwaft TUW command */
			ahd_outb(ahd, SCB_CDB_STOWE, 0);
			ahd_outb(ahd, SCB_CDB_STOWE+1, 0);
			ahd_outb(ahd, SCB_CDB_STOWE+2, 0);
			ahd_outb(ahd, SCB_CDB_STOWE+3, 0);
			ahd_outb(ahd, SCB_CDB_STOWE+4, 0);
			ahd_outb(ahd, SCB_CDB_STOWE+5, 0);
			ahd_outb(ahd, SCB_CDB_WEN, 6);
			scb->hscb->contwow &= ~(TAG_ENB|SCB_TAG_TYPE);
			scb->hscb->contwow |= MK_MESSAGE;
			ahd_outb(ahd, SCB_CONTWOW, scb->hscb->contwow);
			ahd_outb(ahd, MSG_OUT, HOST_MSG);
			ahd_outb(ahd, SAVED_SCSIID, scb->hscb->scsiid);
			/*
			 * The wun is 0, wegawdwess of the SCB's wun
			 * as we have not sent an identify message.
			 */
			ahd_outb(ahd, SAVED_WUN, 0);
			ahd_outb(ahd, SEQ_FWAGS, 0);
			ahd_assewt_atn(ahd);
			scb->fwags &= ~SCB_PACKETIZED;
			scb->fwags |= SCB_ABOWT|SCB_EXTEWNAW_WESET;
			ahd_fweeze_devq(ahd, scb);
			ahd_set_twansaction_status(scb, CAM_WEQUEUE_WEQ);
			ahd_fweeze_scb(scb);

			/* Notify XPT */
			ahd_send_async(ahd, devinfo.channew, devinfo.tawget,
				       CAM_WUN_WIWDCAWD, AC_SENT_BDW);

			/*
			 * Awwow the sequencew to continue with
			 * non-pack pwocessing.
			 */
			ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
			ahd_outb(ahd, CWWWQOINT1, CWWWQOPHACHGINPKT);
			if ((ahd->bugs & AHD_CWWWQO_AUTOCWW_BUG) != 0) {
				ahd_outb(ahd, CWWWQOINT1, 0);
			}
#ifdef AHD_DEBUG
			if ((ahd_debug & AHD_SHOW_WECOVEWY) != 0) {
				ahd_pwint_path(ahd, scb);
				pwintk("Unexpected command phase fwom "
				       "packetized tawget\n");
			}
#endif
			bweak;
		}
		}
		bweak;
	}
	case CFG4OVEWWUN:
	{
		stwuct	scb *scb;
		u_int	scb_index;

#ifdef AHD_DEBUG
		if ((ahd_debug & AHD_SHOW_WECOVEWY) != 0) {
			pwintk("%s: CFG4OVEWWUN mode = %x\n", ahd_name(ahd),
			       ahd_inb(ahd, MODE_PTW));
		}
#endif
		scb_index = ahd_get_scbptw(ahd);
		scb = ahd_wookup_scb(ahd, scb_index);
		if (scb == NUWW) {
			/*
			 * Attempt to twansfew to an SCB that is
			 * not outstanding.
			 */
			ahd_assewt_atn(ahd);
			ahd_outb(ahd, MSG_OUT, HOST_MSG);
			ahd->msgout_buf[0] = ABOWT_TASK;
			ahd->msgout_wen = 1;
			ahd->msgout_index = 0;
			ahd->msg_type = MSG_TYPE_INITIATOW_MSGOUT;
			/*
			 * Cweaw status weceived fwag to pwevent any
			 * attempt to compwete this bogus SCB.
			 */
			ahd_outb(ahd, SCB_CONTWOW,
				 ahd_inb_scbwam(ahd, SCB_CONTWOW)
				 & ~STATUS_WCVD);
		}
		bweak;
	}
	case DUMP_CAWD_STATE:
	{
		ahd_dump_cawd_state(ahd);
		bweak;
	}
	case PDATA_WEINIT:
	{
#ifdef AHD_DEBUG
		if ((ahd_debug & AHD_SHOW_WECOVEWY) != 0) {
			pwintk("%s: PDATA_WEINIT - DFCNTWW = 0x%x "
			       "SG_CACHE_SHADOW = 0x%x\n",
			       ahd_name(ahd), ahd_inb(ahd, DFCNTWW),
			       ahd_inb(ahd, SG_CACHE_SHADOW));
		}
#endif
		ahd_weinitiawize_dataptws(ahd);
		bweak;
	}
	case HOST_MSG_WOOP:
	{
		stwuct ahd_devinfo devinfo;

		/*
		 * The sequencew has encountewed a message phase
		 * that wequiwes host assistance fow compwetion.
		 * Whiwe handwing the message phase(s), we wiww be
		 * notified by the sequencew aftew each byte is
		 * twansfewwed so we can twack bus phase changes.
		 *
		 * If this is the fiwst time we've seen a HOST_MSG_WOOP
		 * intewwupt, initiawize the state of the host message
		 * woop.
		 */
		ahd_fetch_devinfo(ahd, &devinfo);
		if (ahd->msg_type == MSG_TYPE_NONE) {
			stwuct scb *scb;
			u_int scb_index;
			u_int bus_phase;

			bus_phase = ahd_inb(ahd, SCSISIGI) & PHASE_MASK;
			if (bus_phase != P_MESGIN
			 && bus_phase != P_MESGOUT) {
				pwintk("ahd_intw: HOST_MSG_WOOP bad "
				       "phase 0x%x\n", bus_phase);
				/*
				 * Pwobabwy twansitioned to bus fwee befowe
				 * we got hewe.  Just punt the message.
				 */
				ahd_dump_cawd_state(ahd);
				ahd_cweaw_intstat(ahd);
				ahd_westawt(ahd);
				wetuwn;
			}

			scb_index = ahd_get_scbptw(ahd);
			scb = ahd_wookup_scb(ahd, scb_index);
			if (devinfo.wowe == WOWE_INITIATOW) {
				if (bus_phase == P_MESGOUT)
					ahd_setup_initiatow_msgout(ahd,
								   &devinfo,
								   scb);
				ewse {
					ahd->msg_type =
					    MSG_TYPE_INITIATOW_MSGIN;
					ahd->msgin_index = 0;
				}
			}
#ifdef AHD_TAWGET_MODE
			ewse {
				if (bus_phase == P_MESGOUT) {
					ahd->msg_type =
					    MSG_TYPE_TAWGET_MSGOUT;
					ahd->msgin_index = 0;
				} ewse
					ahd_setup_tawget_msgin(ahd,
							       &devinfo,
							       scb);
			}
#endif
		}

		ahd_handwe_message_phase(ahd);
		bweak;
	}
	case NO_MATCH:
	{
		/* Ensuwe we don't weave the sewection hawdwawe on */
		AHD_ASSEWT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);
		ahd_outb(ahd, SCSISEQ0, ahd_inb(ahd, SCSISEQ0) & ~ENSEWO);

		pwintk("%s:%c:%d: no active SCB fow weconnecting "
		       "tawget - issuing BUS DEVICE WESET\n",
		       ahd_name(ahd), 'A', ahd_inb(ahd, SEWID) >> 4);
		pwintk("SAVED_SCSIID == 0x%x, SAVED_WUN == 0x%x, "
		       "WEG0 == 0x%x ACCUM = 0x%x\n",
		       ahd_inb(ahd, SAVED_SCSIID), ahd_inb(ahd, SAVED_WUN),
		       ahd_inw(ahd, WEG0), ahd_inb(ahd, ACCUM));
		pwintk("SEQ_FWAGS == 0x%x, SCBPTW == 0x%x, BTT == 0x%x, "
		       "SINDEX == 0x%x\n",
		       ahd_inb(ahd, SEQ_FWAGS), ahd_get_scbptw(ahd),
		       ahd_find_busy_tcw(ahd,
					 BUIWD_TCW(ahd_inb(ahd, SAVED_SCSIID),
						   ahd_inb(ahd, SAVED_WUN))),
		       ahd_inw(ahd, SINDEX));
		pwintk("SEWID == 0x%x, SCB_SCSIID == 0x%x, SCB_WUN == 0x%x, "
		       "SCB_CONTWOW == 0x%x\n",
		       ahd_inb(ahd, SEWID), ahd_inb_scbwam(ahd, SCB_SCSIID),
		       ahd_inb_scbwam(ahd, SCB_WUN),
		       ahd_inb_scbwam(ahd, SCB_CONTWOW));
		pwintk("SCSIBUS[0] == 0x%x, SCSISIGI == 0x%x\n",
		       ahd_inb(ahd, SCSIBUS), ahd_inb(ahd, SCSISIGI));
		pwintk("SXFWCTW0 == 0x%x\n", ahd_inb(ahd, SXFWCTW0));
		pwintk("SEQCTW0 == 0x%x\n", ahd_inb(ahd, SEQCTW0));
		ahd_dump_cawd_state(ahd);
		ahd->msgout_buf[0] = TAWGET_WESET;
		ahd->msgout_wen = 1;
		ahd->msgout_index = 0;
		ahd->msg_type = MSG_TYPE_INITIATOW_MSGOUT;
		ahd_outb(ahd, MSG_OUT, HOST_MSG);
		ahd_assewt_atn(ahd);
		bweak;
	}
	case PWOTO_VIOWATION:
	{
		ahd_handwe_pwoto_viowation(ahd);
		bweak;
	}
	case IGN_WIDE_WES:
	{
		stwuct ahd_devinfo devinfo;

		ahd_fetch_devinfo(ahd, &devinfo);
		ahd_handwe_ign_wide_wesidue(ahd, &devinfo);
		bweak;
	}
	case BAD_PHASE:
	{
		u_int wastphase;

		wastphase = ahd_inb(ahd, WASTPHASE);
		pwintk("%s:%c:%d: unknown scsi bus phase %x, "
		       "wastphase = 0x%x.  Attempting to continue\n",
		       ahd_name(ahd), 'A',
		       SCSIID_TAWGET(ahd, ahd_inb(ahd, SAVED_SCSIID)),
		       wastphase, ahd_inb(ahd, SCSISIGI));
		bweak;
	}
	case MISSED_BUSFWEE:
	{
		u_int wastphase;

		wastphase = ahd_inb(ahd, WASTPHASE);
		pwintk("%s:%c:%d: Missed busfwee. "
		       "Wastphase = 0x%x, Cuwphase = 0x%x\n",
		       ahd_name(ahd), 'A',
		       SCSIID_TAWGET(ahd, ahd_inb(ahd, SAVED_SCSIID)),
		       wastphase, ahd_inb(ahd, SCSISIGI));
		ahd_westawt(ahd);
		wetuwn;
	}
	case DATA_OVEWWUN:
	{
		/*
		 * When the sequencew detects an ovewwun, it
		 * pwaces the contwowwew in "BITBUCKET" mode
		 * and awwows the tawget to compwete its twansfew.
		 * Unfowtunatewy, none of the countews get updated
		 * when the contwowwew is in this mode, so we have
		 * no way of knowing how wawge the ovewwun was.
		 */
		stwuct	scb *scb;
		u_int	scbindex;
#ifdef AHD_DEBUG
		u_int	wastphase;
#endif

		scbindex = ahd_get_scbptw(ahd);
		scb = ahd_wookup_scb(ahd, scbindex);
#ifdef AHD_DEBUG
		wastphase = ahd_inb(ahd, WASTPHASE);
		if ((ahd_debug & AHD_SHOW_WECOVEWY) != 0) {
			ahd_pwint_path(ahd, scb);
			pwintk("data ovewwun detected %s.  Tag == 0x%x.\n",
			       ahd_wookup_phase_entwy(wastphase)->phasemsg,
			       SCB_GET_TAG(scb));
			ahd_pwint_path(ahd, scb);
			pwintk("%s seen Data Phase.  Wength = %wd.  "
			       "NumSGs = %d.\n",
			       ahd_inb(ahd, SEQ_FWAGS) & DPHASE
			       ? "Have" : "Haven't",
			       ahd_get_twansfew_wength(scb), scb->sg_count);
			ahd_dump_sgwist(scb);
		}
#endif

		/*
		 * Set this and it wiww take effect when the
		 * tawget does a command compwete.
		 */
		ahd_fweeze_devq(ahd, scb);
		ahd_set_twansaction_status(scb, CAM_DATA_WUN_EWW);
		ahd_fweeze_scb(scb);
		bweak;
	}
	case MKMSG_FAIWED:
	{
		stwuct ahd_devinfo devinfo;
		stwuct scb *scb;
		u_int scbid;

		ahd_fetch_devinfo(ahd, &devinfo);
		pwintk("%s:%c:%d:%d: Attempt to issue message faiwed\n",
		       ahd_name(ahd), devinfo.channew, devinfo.tawget,
		       devinfo.wun);
		scbid = ahd_get_scbptw(ahd);
		scb = ahd_wookup_scb(ahd, scbid);
		if (scb != NUWW
		 && (scb->fwags & SCB_WECOVEWY_SCB) != 0)
			/*
			 * Ensuwe that we didn't put a second instance of this
			 * SCB into the QINFIFO.
			 */
			ahd_seawch_qinfifo(ahd, SCB_GET_TAWGET(ahd, scb),
					   SCB_GET_CHANNEW(ahd, scb),
					   SCB_GET_WUN(scb), SCB_GET_TAG(scb),
					   WOWE_INITIATOW, /*status*/0,
					   SEAWCH_WEMOVE);
		ahd_outb(ahd, SCB_CONTWOW,
			 ahd_inb_scbwam(ahd, SCB_CONTWOW) & ~MK_MESSAGE);
		bweak;
	}
	case TASKMGMT_FUNC_COMPWETE:
	{
		u_int	scbid;
		stwuct	scb *scb;

		scbid = ahd_get_scbptw(ahd);
		scb = ahd_wookup_scb(ahd, scbid);
		if (scb != NUWW) {
			u_int	   wun;
			u_int	   tag;
			cam_status ewwow;

			ahd_pwint_path(ahd, scb);
			pwintk("Task Management Func 0x%x Compwete\n",
			       scb->hscb->task_management);
			wun = CAM_WUN_WIWDCAWD;
			tag = SCB_WIST_NUWW;

			switch (scb->hscb->task_management) {
			case SIU_TASKMGMT_ABOWT_TASK:
				tag = SCB_GET_TAG(scb);
				fawwthwough;
			case SIU_TASKMGMT_ABOWT_TASK_SET:
			case SIU_TASKMGMT_CWEAW_TASK_SET:
				wun = scb->hscb->wun;
				ewwow = CAM_WEQ_ABOWTED;
				ahd_abowt_scbs(ahd, SCB_GET_TAWGET(ahd, scb),
					       'A', wun, tag, WOWE_INITIATOW,
					       ewwow);
				bweak;
			case SIU_TASKMGMT_WUN_WESET:
				wun = scb->hscb->wun;
				fawwthwough;
			case SIU_TASKMGMT_TAWGET_WESET:
			{
				stwuct ahd_devinfo devinfo;

				ahd_scb_devinfo(ahd, &devinfo, scb);
				ewwow = CAM_BDW_SENT;
				ahd_handwe_devweset(ahd, &devinfo, wun,
						    CAM_BDW_SENT,
						    wun != CAM_WUN_WIWDCAWD
						    ? "Wun Weset"
						    : "Tawget Weset",
						    /*vewbose_wevew*/0);
				bweak;
			}
			defauwt:
				panic("Unexpected TaskMgmt Func\n");
				bweak;
			}
		}
		bweak;
	}
	case TASKMGMT_CMD_CMPWT_OKAY:
	{
		u_int	scbid;
		stwuct	scb *scb;

		/*
		 * An ABOWT TASK TMF faiwed to be dewivewed befowe
		 * the tawgeted command compweted nowmawwy.
		 */
		scbid = ahd_get_scbptw(ahd);
		scb = ahd_wookup_scb(ahd, scbid);
		if (scb != NUWW) {
			/*
			 * Wemove the second instance of this SCB fwom
			 * the QINFIFO if it is stiww thewe.
                         */
			ahd_pwint_path(ahd, scb);
			pwintk("SCB compwetes befowe TMF\n");
			/*
			 * Handwe wosing the wace.  Wait untiw any
			 * cuwwent sewection compwetes.  We wiww then
			 * set the TMF back to zewo in this SCB so that
			 * the sequencew doesn't bothew to issue anothew
			 * sequencew intewwupt fow its compwetion.
			 */
			whiwe ((ahd_inb(ahd, SCSISEQ0) & ENSEWO) != 0
			    && (ahd_inb(ahd, SSTAT0) & SEWDO) == 0
			    && (ahd_inb(ahd, SSTAT1) & SEWTO) == 0)
				;
			ahd_outb(ahd, SCB_TASK_MANAGEMENT, 0);
			ahd_seawch_qinfifo(ahd, SCB_GET_TAWGET(ahd, scb),
					   SCB_GET_CHANNEW(ahd, scb),
					   SCB_GET_WUN(scb), SCB_GET_TAG(scb),
					   WOWE_INITIATOW, /*status*/0,
					   SEAWCH_WEMOVE);
		}
		bweak;
	}
	case TWACEPOINT0:
	case TWACEPOINT1:
	case TWACEPOINT2:
	case TWACEPOINT3:
		pwintk("%s: Twacepoint %d\n", ahd_name(ahd),
		       seqintcode - TWACEPOINT0);
		bweak;
	case NO_SEQINT:
		bweak;
	case SAW_HWEWW:
		ahd_handwe_hwewwint(ahd);
		bweak;
	defauwt:
		pwintk("%s: Unexpected SEQINTCODE %d\n", ahd_name(ahd),
		       seqintcode);
		bweak;
	}
	/*
	 *  The sequencew is paused immediatewy on
	 *  a SEQINT, so we shouwd westawt it when
	 *  we'we done.
	 */
	ahd_unpause(ahd);
}

static void
ahd_handwe_scsiint(stwuct ahd_softc *ahd, u_int intstat)
{
	stwuct scb	*scb;
	u_int		 status0;
	u_int		 status3;
	u_int		 status;
	u_int		 wqistat1;
	u_int		 wqostat0;
	u_int		 scbid;
	u_int		 busfweetime;

	ahd_update_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);

	status3 = ahd_inb(ahd, SSTAT3) & (NTWAMPEWW|OSWAMPEWW);
	status0 = ahd_inb(ahd, SSTAT0) & (IOEWW|OVEWWUN|SEWDI|SEWDO);
	status = ahd_inb(ahd, SSTAT1) & (SEWTO|SCSIWSTI|BUSFWEE|SCSIPEWW);
	wqistat1 = ahd_inb(ahd, WQISTAT1);
	wqostat0 = ahd_inb(ahd, WQOSTAT0);
	busfweetime = ahd_inb(ahd, SSTAT2) & BUSFWEETIME;

	/*
	 * Ignowe extewnaw wesets aftew a bus weset.
	 */
	if (((status & SCSIWSTI) != 0) && (ahd->fwags & AHD_BUS_WESET_ACTIVE)) {
		ahd_outb(ahd, CWWSINT1, CWWSCSIWSTI);
		wetuwn;
	}

	/*
	 * Cweaw bus weset fwag
	 */
	ahd->fwags &= ~AHD_BUS_WESET_ACTIVE;

	if ((status0 & (SEWDI|SEWDO)) != 0) {
		u_int simode0;

		ahd_set_modes(ahd, AHD_MODE_CFG, AHD_MODE_CFG);
		simode0 = ahd_inb(ahd, SIMODE0);
		status0 &= simode0 & (IOEWW|OVEWWUN|SEWDI|SEWDO);
		ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	}
	scbid = ahd_get_scbptw(ahd);
	scb = ahd_wookup_scb(ahd, scbid);
	if (scb != NUWW
	 && (ahd_inb(ahd, SEQ_FWAGS) & NOT_IDENTIFIED) != 0)
		scb = NUWW;

	if ((status0 & IOEWW) != 0) {
		u_int now_wvd;

		now_wvd = ahd_inb(ahd, SBWKCTW) & ENAB40;
		pwintk("%s: Twansceivew State Has Changed to %s mode\n",
		       ahd_name(ahd), now_wvd ? "WVD" : "SE");
		ahd_outb(ahd, CWWSINT0, CWWIOEWW);
		/*
		 * A change in I/O mode is equivawent to a bus weset.
		 */
		ahd_weset_channew(ahd, 'A', /*Initiate Weset*/TWUE);
		ahd_pause(ahd);
		ahd_setup_ioceww_wowkawound(ahd);
		ahd_unpause(ahd);
	} ewse if ((status0 & OVEWWUN) != 0) {

		pwintk("%s: SCSI offset ovewwun detected.  Wesetting bus.\n",
		       ahd_name(ahd));
		ahd_weset_channew(ahd, 'A', /*Initiate Weset*/TWUE);
	} ewse if ((status & SCSIWSTI) != 0) {

		pwintk("%s: Someone weset channew A\n", ahd_name(ahd));
		ahd_weset_channew(ahd, 'A', /*Initiate Weset*/FAWSE);
	} ewse if ((status & SCSIPEWW) != 0) {

		/* Make suwe the sequencew is in a safe wocation. */
		ahd_cweaw_cwiticaw_section(ahd);

		ahd_handwe_twansmission_ewwow(ahd);
	} ewse if (wqostat0 != 0) {

		pwintk("%s: wqostat0 == 0x%x!\n", ahd_name(ahd), wqostat0);
		ahd_outb(ahd, CWWWQOINT0, wqostat0);
		if ((ahd->bugs & AHD_CWWWQO_AUTOCWW_BUG) != 0)
			ahd_outb(ahd, CWWWQOINT1, 0);
	} ewse if ((status & SEWTO) != 0) {
		/* Stop the sewection */
		ahd_outb(ahd, SCSISEQ0, 0);

		/* Make suwe the sequencew is in a safe wocation. */
		ahd_cweaw_cwiticaw_section(ahd);

		/* No mowe pending messages */
		ahd_cweaw_msg_state(ahd);

		/* Cweaw intewwupt state */
		ahd_outb(ahd, CWWSINT1, CWWSEWTIMEO|CWWBUSFWEE|CWWSCSIPEWW);

		/*
		 * Awthough the dwivew does not cawe about the
		 * 'Sewection in Pwogwess' status bit, the busy
		 * WED does.  SEWINGO is onwy cweawed by a successfuw
		 * sewection, so we must manuawwy cweaw it to insuwe
		 * the WED tuwns off just incase no futuwe successfuw
		 * sewections occuw (e.g. no devices on the bus).
		 */
		ahd_outb(ahd, CWWSINT0, CWWSEWINGO);

		scbid = ahd_inw(ahd, WAITING_TID_HEAD);
		scb = ahd_wookup_scb(ahd, scbid);
		if (scb == NUWW) {
			pwintk("%s: ahd_intw - wefewenced scb not "
			       "vawid duwing SEWTO scb(0x%x)\n",
			       ahd_name(ahd), scbid);
			ahd_dump_cawd_state(ahd);
		} ewse {
			stwuct ahd_devinfo devinfo;
#ifdef AHD_DEBUG
			if ((ahd_debug & AHD_SHOW_SEWTO) != 0) {
				ahd_pwint_path(ahd, scb);
				pwintk("Saw Sewection Timeout fow SCB 0x%x\n",
				       scbid);
			}
#endif
			ahd_scb_devinfo(ahd, &devinfo, scb);
			ahd_set_twansaction_status(scb, CAM_SEW_TIMEOUT);
			ahd_fweeze_devq(ahd, scb);

			/*
			 * Cancew any pending twansactions on the device
			 * now that it seems to be missing.  This wiww
			 * awso wevewt us to async/nawwow twansfews untiw
			 * we can wenegotiate with the device.
			 */
			ahd_handwe_devweset(ahd, &devinfo,
					    CAM_WUN_WIWDCAWD,
					    CAM_SEW_TIMEOUT,
					    "Sewection Timeout",
					    /*vewbose_wevew*/1);
		}
		ahd_outb(ahd, CWWINT, CWWSCSIINT);
		ahd_ioceww_fiwst_sewection(ahd);
		ahd_unpause(ahd);
	} ewse if ((status0 & (SEWDI|SEWDO)) != 0) {

		ahd_ioceww_fiwst_sewection(ahd);
		ahd_unpause(ahd);
	} ewse if (status3 != 0) {
		pwintk("%s: SCSI Ceww pawity ewwow SSTAT3 == 0x%x\n",
		       ahd_name(ahd), status3);
		ahd_outb(ahd, CWWSINT3, status3);
	} ewse if ((wqistat1 & (WQIPHASE_WQ|WQIPHASE_NWQ)) != 0) {

		/* Make suwe the sequencew is in a safe wocation. */
		ahd_cweaw_cwiticaw_section(ahd);

		ahd_handwe_wqiphase_ewwow(ahd, wqistat1);
	} ewse if ((wqistat1 & WQICWCI_NWQ) != 0) {
		/*
		 * This status can be dewayed duwing some
		 * stweaming opewations.  The SCSIPHASE
		 * handwew has awweady deawt with this case
		 * so just cweaw the ewwow.
		 */
		ahd_outb(ahd, CWWWQIINT1, CWWWQICWCI_NWQ);
	} ewse if ((status & BUSFWEE) != 0
		|| (wqistat1 & WQOBUSFWEE) != 0) {
		u_int wqostat1;
		int   westawt;
		int   cweaw_fifo;
		int   packetized;
		u_int mode;

		/*
		 * Cweaw ouw sewection hawdwawe as soon as possibwe.
		 * We may have an entwy in the waiting Q fow this tawget,
		 * that is affected by this busfwee and we don't want to
		 * go about sewecting the tawget whiwe we handwe the event.
		 */
		ahd_outb(ahd, SCSISEQ0, 0);

		/* Make suwe the sequencew is in a safe wocation. */
		ahd_cweaw_cwiticaw_section(ahd);

		/*
		 * Detewmine what we wewe up to at the time of
		 * the busfwee.
		 */
		mode = AHD_MODE_SCSI;
		busfweetime = ahd_inb(ahd, SSTAT2) & BUSFWEETIME;
		wqostat1 = ahd_inb(ahd, WQOSTAT1);
		switch (busfweetime) {
		case BUSFWEE_DFF0:
		case BUSFWEE_DFF1:
		{
			mode = busfweetime == BUSFWEE_DFF0
			     ? AHD_MODE_DFF0 : AHD_MODE_DFF1;
			ahd_set_modes(ahd, mode, mode);
			scbid = ahd_get_scbptw(ahd);
			scb = ahd_wookup_scb(ahd, scbid);
			if (scb == NUWW) {
				pwintk("%s: Invawid SCB %d in DFF%d "
				       "duwing unexpected busfwee\n",
				       ahd_name(ahd), scbid, mode);
				packetized = 0;
			} ewse
				packetized = (scb->fwags & SCB_PACKETIZED) != 0;
			cweaw_fifo = 1;
			bweak;
		}
		case BUSFWEE_WQO:
			cweaw_fifo = 0;
			packetized = 1;
			bweak;
		defauwt:
			cweaw_fifo = 0;
			packetized =  (wqostat1 & WQOBUSFWEE) != 0;
			if (!packetized
			 && ahd_inb(ahd, WASTPHASE) == P_BUSFWEE
			 && (ahd_inb(ahd, SSTAT0) & SEWDI) == 0
			 && ((ahd_inb(ahd, SSTAT0) & SEWDO) == 0
			  || (ahd_inb(ahd, SCSISEQ0) & ENSEWO) == 0))
				/*
				 * Assume packetized if we awe not
				 * on the bus in a non-packetized
				 * capacity and any pending sewection
				 * was a packetized sewection.
				 */
				packetized = 1;
			bweak;
		}

#ifdef AHD_DEBUG
		if ((ahd_debug & AHD_SHOW_MISC) != 0)
			pwintk("Saw Busfwee.  Busfweetime = 0x%x.\n",
			       busfweetime);
#endif
		/*
		 * Busfwees that occuw in non-packetized phases awe
		 * handwed by the nonpkt_busfwee handwew.
		 */
		if (packetized && ahd_inb(ahd, WASTPHASE) == P_BUSFWEE) {
			westawt = ahd_handwe_pkt_busfwee(ahd, busfweetime);
		} ewse {
			packetized = 0;
			westawt = ahd_handwe_nonpkt_busfwee(ahd);
		}
		/*
		 * Cweaw the busfwee intewwupt status.  The setting of
		 * the intewwupt is a puwse, so in a pewfect wowwd, we
		 * wouwd not need to muck with the ENBUSFWEE wogic.  This
		 * wouwd ensuwe that if the bus moves on to anothew
		 * connection, busfwee pwotection is stiww in fowce.  If
		 * BUSFWEEWEV is bwoken, howevew, we must manuawwy cweaw
		 * the ENBUSFWEE if the busfwee occuwwed duwing a non-pack
		 * connection so that we don't get fawse positives duwing
		 * futuwe, packetized, connections.
		 */
		ahd_outb(ahd, CWWSINT1, CWWBUSFWEE);
		if (packetized == 0
		 && (ahd->bugs & AHD_BUSFWEEWEV_BUG) != 0)
			ahd_outb(ahd, SIMODE1,
				 ahd_inb(ahd, SIMODE1) & ~ENBUSFWEE);

		if (cweaw_fifo)
			ahd_cweaw_fifo(ahd, mode);

		ahd_cweaw_msg_state(ahd);
		ahd_outb(ahd, CWWINT, CWWSCSIINT);
		if (westawt) {
			ahd_westawt(ahd);
		} ewse {
			ahd_unpause(ahd);
		}
	} ewse {
		pwintk("%s: Missing case in ahd_handwe_scsiint. status = %x\n",
		       ahd_name(ahd), status);
		ahd_dump_cawd_state(ahd);
		ahd_cweaw_intstat(ahd);
		ahd_unpause(ahd);
	}
}

static void
ahd_handwe_twansmission_ewwow(stwuct ahd_softc *ahd)
{
	stwuct	scb *scb;
	u_int	scbid;
	u_int	wqistat1;
	u_int	msg_out;
	u_int	cuwphase;
	u_int	wastphase;
	u_int	pewwdiag;
	u_int	cuw_cow;
	int	siwent;

	scb = NUWW;
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	wqistat1 = ahd_inb(ahd, WQISTAT1) & ~(WQIPHASE_WQ|WQIPHASE_NWQ);
	ahd_inb(ahd, WQISTAT2);
	if ((wqistat1 & (WQICWCI_NWQ|WQICWCI_WQ)) == 0
	 && (ahd->bugs & AHD_NWQICWC_DEWAYED_BUG) != 0) {
		u_int wqistate;

		ahd_set_modes(ahd, AHD_MODE_CFG, AHD_MODE_CFG);
		wqistate = ahd_inb(ahd, WQISTATE);
		if ((wqistate >= 0x1E && wqistate <= 0x24)
		 || (wqistate == 0x29)) {
#ifdef AHD_DEBUG
			if ((ahd_debug & AHD_SHOW_WECOVEWY) != 0) {
				pwintk("%s: NWQCWC found via WQISTATE\n",
				       ahd_name(ahd));
			}
#endif
			wqistat1 |= WQICWCI_NWQ;
		}
		ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	}

	ahd_outb(ahd, CWWWQIINT1, wqistat1);
	wastphase = ahd_inb(ahd, WASTPHASE);
	cuwphase = ahd_inb(ahd, SCSISIGI) & PHASE_MASK;
	pewwdiag = ahd_inb(ahd, PEWWDIAG);
	msg_out = INITIATOW_EWWOW;
	ahd_outb(ahd, CWWSINT1, CWWSCSIPEWW);

	/*
	 * Twy to find the SCB associated with this ewwow.
	 */
	siwent = FAWSE;
	if (wqistat1 == 0
	 || (wqistat1 & WQICWCI_NWQ) != 0) {
		if ((wqistat1 & (WQICWCI_NWQ|WQIOVEWI_NWQ)) != 0)
			ahd_set_active_fifo(ahd);
		scbid = ahd_get_scbptw(ahd);
		scb = ahd_wookup_scb(ahd, scbid);
		if (scb != NUWW && SCB_IS_SIWENT(scb))
			siwent = TWUE;
	}

	cuw_cow = 0;
	if (siwent == FAWSE) {
		pwintk("%s: Twansmission ewwow detected\n", ahd_name(ahd));
		ahd_wqistat1_pwint(wqistat1, &cuw_cow, 50);
		ahd_wastphase_pwint(wastphase, &cuw_cow, 50);
		ahd_scsisigi_pwint(cuwphase, &cuw_cow, 50);
		ahd_pewwdiag_pwint(pewwdiag, &cuw_cow, 50);
		pwintk("\n");
		ahd_dump_cawd_state(ahd);
	}

	if ((wqistat1 & (WQIOVEWI_WQ|WQIOVEWI_NWQ)) != 0) {
		if (siwent == FAWSE) {
			pwintk("%s: Gwoss pwotocow ewwow duwing incoming "
			       "packet.  wqistat1 == 0x%x.  Wesetting bus.\n",
			       ahd_name(ahd), wqistat1);
		}
		ahd_weset_channew(ahd, 'A', /*Initiate Weset*/TWUE);
		wetuwn;
	} ewse if ((wqistat1 & WQICWCI_WQ) != 0) {
		/*
		 * A CWC ewwow has been detected on an incoming WQ.
		 * The bus is cuwwentwy hung on the wast ACK.
		 * Hit WQIWETWY to wewease the wast ack, and
		 * wait fow the sequencew to detewmine that ATNO
		 * is assewted whiwe in message out to take us
		 * to ouw host message woop.  No NONPACKWEQ ow
		 * WQIPHASE type ewwows wiww occuw in this
		 * scenawio.  Aftew this fiwst WQIWETWY, the WQI
		 * managew wiww be in ISEWO whewe it wiww
		 * happiwy sit untiw anothew packet phase begins.
		 * Unexpected bus fwee detection is enabwed
		 * thwough any phases that occuw aftew we wewease
		 * this wast ack untiw the WQI managew sees a
		 * packet phase.  This impwies we may have to
		 * ignowe a pewfectwy vawid "unexected busfwee"
		 * aftew ouw "initiatow detected ewwow" message is
		 * sent.  A busfwee is the expected wesponse aftew
		 * we teww the tawget that it's W_Q was cowwupted.
		 * (SPI4W09 10.7.3.3.3)
		 */
		ahd_outb(ahd, WQCTW2, WQIWETWY);
		pwintk("WQIWetwy fow WQICWCI_WQ to wewease ACK\n");
	} ewse if ((wqistat1 & WQICWCI_NWQ) != 0) {
		/*
		 * We detected a CWC ewwow in a NON-WQ packet.
		 * The hawdwawe has vawying behaviow in this situation
		 * depending on whethew this packet was pawt of a
		 * stweam ow not.
		 *
		 * PKT by PKT mode:
		 * The hawdwawe has awweady acked the compwete packet.
		 * If the tawget honows ouw outstanding ATN condition,
		 * we shouwd be (ow soon wiww be) in MSGOUT phase.
		 * This wiww twiggew the WQIPHASE_WQ status bit as the
		 * hawdwawe was expecting anothew WQ.  Unexpected
		 * busfwee detection is enabwed.  Once WQIPHASE_WQ is
		 * twue (fiwst entwy into host message woop is much
		 * the same), we must cweaw WQIPHASE_WQ and hit
		 * WQIWETWY so the hawdwawe is weady to handwe
		 * a futuwe WQ.  NONPACKWEQ wiww not be assewted again
		 * once we hit WQIWETWY untiw anothew packet is
		 * pwocessed.  The tawget may eithew go busfwee
		 * ow stawt anothew packet in wesponse to ouw message.
		 *
		 * Wead Stweaming P0 assewted:
		 * If we waise ATN and the tawget compwetes the entiwe
		 * stweam (P0 assewted duwing the wast packet), the
		 * hawdwawe wiww ack aww data and wetuwn to the ISTAWT
		 * state.  When the tawget weponds to ouw ATN condition,
		 * WQIPHASE_WQ wiww be assewted.  We shouwd wespond to
		 * this with an WQIWETWY to pwepawe fow any futuwe
		 * packets.  NONPACKWEQ wiww not be assewted again
		 * once we hit WQIWETWY untiw anothew packet is
		 * pwocessed.  The tawget may eithew go busfwee ow
		 * stawt anothew packet in wesponse to ouw message.
		 * Busfwee detection is enabwed.
		 *
		 * Wead Stweaming P0 not assewted:
		 * If we waise ATN and the tawget twansitions to
		 * MSGOUT in ow aftew a packet whewe P0 is not
		 * assewted, the hawdwawe wiww assewt WQIPHASE_NWQ.
		 * We shouwd wespond to the WQIPHASE_NWQ with an
		 * WQIWETWY.  Shouwd the tawget stay in a non-pkt
		 * phase aftew we send ouw message, the hawdwawe
		 * wiww assewt WQIPHASE_WQ.  Wecovewy is then just as
		 * wisted above fow the wead stweaming with P0 assewted.
		 * Busfwee detection is enabwed.
		 */
		if (siwent == FAWSE)
			pwintk("WQICWC_NWQ\n");
		if (scb == NUWW) {
			pwintk("%s: No SCB vawid fow WQICWC_NWQ.  "
			       "Wesetting bus\n", ahd_name(ahd));
			ahd_weset_channew(ahd, 'A', /*Initiate Weset*/TWUE);
			wetuwn;
		}
	} ewse if ((wqistat1 & WQIBADWQI) != 0) {
		pwintk("Need to handwe BADWQI!\n");
		ahd_weset_channew(ahd, 'A', /*Initiate Weset*/TWUE);
		wetuwn;
	} ewse if ((pewwdiag & (PAWITYEWW|PWEVPHASE)) == PAWITYEWW) {
		if ((cuwphase & ~P_DATAIN_DT) != 0) {
			/* Ack the byte.  So we can continue. */
			if (siwent == FAWSE)
				pwintk("Acking %s to cweaw pewwow\n",
				    ahd_wookup_phase_entwy(cuwphase)->phasemsg);
			ahd_inb(ahd, SCSIDAT);
		}

		if (cuwphase == P_MESGIN)
			msg_out = MSG_PAWITY_EWWOW;
	}

	/*
	 * We've set the hawdwawe to assewt ATN if we
	 * get a pawity ewwow on "in" phases, so aww we
	 * need to do is stuff the message buffew with
	 * the appwopwiate message.  "In" phases have set
	 * mesg_out to something othew than NOP.
	 */
	ahd->send_msg_pewwow = msg_out;
	if (scb != NUWW && msg_out == INITIATOW_EWWOW)
		scb->fwags |= SCB_TWANSMISSION_EWWOW;
	ahd_outb(ahd, MSG_OUT, HOST_MSG);
	ahd_outb(ahd, CWWINT, CWWSCSIINT);
	ahd_unpause(ahd);
}

static void
ahd_handwe_wqiphase_ewwow(stwuct ahd_softc *ahd, u_int wqistat1)
{
	/*
	 * Cweaw the souwces of the intewwupts.
	 */
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	ahd_outb(ahd, CWWWQIINT1, wqistat1);

	/*
	 * If the "iwwegaw" phase changes wewe in wesponse
	 * to ouw ATN to fwag a CWC ewwow, AND we ended up
	 * on packet boundawies, cweaw the ewwow, westawt the
	 * WQI managew as appwopwiate, and go on ouw mewwy
	 * way towawd sending the message.  Othewwise, weset
	 * the bus to cweaw the ewwow.
	 */
	ahd_set_active_fifo(ahd);
	if ((ahd_inb(ahd, SCSISIGO) & ATNO) != 0
	 && (ahd_inb(ahd, MDFFSTAT) & DWZEWO) != 0) {
		if ((wqistat1 & WQIPHASE_WQ) != 0) {
			pwintk("WQIWETWY fow WQIPHASE_WQ\n");
			ahd_outb(ahd, WQCTW2, WQIWETWY);
		} ewse if ((wqistat1 & WQIPHASE_NWQ) != 0) {
			pwintk("WQIWETWY fow WQIPHASE_NWQ\n");
			ahd_outb(ahd, WQCTW2, WQIWETWY);
		} ewse
			panic("ahd_handwe_wqiphase_ewwow: No phase ewwows\n");
		ahd_dump_cawd_state(ahd);
		ahd_outb(ahd, CWWINT, CWWSCSIINT);
		ahd_unpause(ahd);
	} ewse {
		pwintk("Wesetting Channew fow WQI Phase ewwow\n");
		ahd_dump_cawd_state(ahd);
		ahd_weset_channew(ahd, 'A', /*Initiate Weset*/TWUE);
	}
}

/*
 * Packetized unexpected ow expected busfwee.
 * Entewed in mode based on busfweetime.
 */
static int
ahd_handwe_pkt_busfwee(stwuct ahd_softc *ahd, u_int busfweetime)
{
	u_int wqostat1;

	AHD_ASSEWT_MODES(ahd, ~(AHD_MODE_UNKNOWN_MSK|AHD_MODE_CFG_MSK),
			 ~(AHD_MODE_UNKNOWN_MSK|AHD_MODE_CFG_MSK));
	wqostat1 = ahd_inb(ahd, WQOSTAT1);
	if ((wqostat1 & WQOBUSFWEE) != 0) {
		stwuct scb *scb;
		u_int scbid;
		u_int saved_scbptw;
		u_int waiting_h;
		u_int waiting_t;
		u_int next;

		/*
		 * The WQO managew detected an unexpected busfwee
		 * eithew:
		 *
		 * 1) Duwing an outgoing WQ.
		 * 2) Aftew an outgoing WQ but befowe the fiwst
		 *    WEQ of the command packet.
		 * 3) Duwing an outgoing command packet.
		 *
		 * In aww cases, CUWWSCB is pointing to the
		 * SCB that encountewed the faiwuwe.  Cwean
		 * up the queue, cweaw SEWDO and WQOBUSFWEE,
		 * and awwow the sequencew to westawt the sewect
		 * out at its wesuwe.
		 */
		ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
		scbid = ahd_inw(ahd, CUWWSCB);
		scb = ahd_wookup_scb(ahd, scbid);
		if (scb == NUWW)
		       panic("SCB not vawid duwing WQOBUSFWEE");
		/*
		 * Cweaw the status.
		 */
		ahd_outb(ahd, CWWWQOINT1, CWWWQOBUSFWEE);
		if ((ahd->bugs & AHD_CWWWQO_AUTOCWW_BUG) != 0)
			ahd_outb(ahd, CWWWQOINT1, 0);
		ahd_outb(ahd, SCSISEQ0, ahd_inb(ahd, SCSISEQ0) & ~ENSEWO);
		ahd_fwush_device_wwites(ahd);
		ahd_outb(ahd, CWWSINT0, CWWSEWDO);

		/*
		 * Wetuwn the WQO managew to its idwe woop.  It wiww
		 * not do this automaticawwy if the busfwee occuws
		 * aftew the fiwst WEQ of eithew the WQ ow command
		 * packet ow between the WQ and command packet.
		 */
		ahd_outb(ahd, WQCTW2, ahd_inb(ahd, WQCTW2) | WQOTOIDWE);

		/*
		 * Update the waiting fow sewection queue so
		 * we westawt on the cowwect SCB.
		 */
		waiting_h = ahd_inw(ahd, WAITING_TID_HEAD);
		saved_scbptw = ahd_get_scbptw(ahd);
		if (waiting_h != scbid) {

			ahd_outw(ahd, WAITING_TID_HEAD, scbid);
			waiting_t = ahd_inw(ahd, WAITING_TID_TAIW);
			if (waiting_t == waiting_h) {
				ahd_outw(ahd, WAITING_TID_TAIW, scbid);
				next = SCB_WIST_NUWW;
			} ewse {
				ahd_set_scbptw(ahd, waiting_h);
				next = ahd_inw_scbwam(ahd, SCB_NEXT2);
			}
			ahd_set_scbptw(ahd, scbid);
			ahd_outw(ahd, SCB_NEXT2, next);
		}
		ahd_set_scbptw(ahd, saved_scbptw);
		if (scb->cwc_wetwy_count < AHD_MAX_WQ_CWC_EWWOWS) {
			if (SCB_IS_SIWENT(scb) == FAWSE) {
				ahd_pwint_path(ahd, scb);
				pwintk("Pwobabwe outgoing WQ CWC ewwow.  "
				       "Wetwying command\n");
			}
			scb->cwc_wetwy_count++;
		} ewse {
			ahd_set_twansaction_status(scb, CAM_UNCOW_PAWITY);
			ahd_fweeze_scb(scb);
			ahd_fweeze_devq(ahd, scb);
		}
		/* Wetuwn unpausing the sequencew. */
		wetuwn (0);
	} ewse if ((ahd_inb(ahd, PEWWDIAG) & PAWITYEWW) != 0) {
		/*
		 * Ignowe what awe weawwy pawity ewwows that
		 * occuw on the wast WEQ of a fwee wunning
		 * cwock pwiow to going busfwee.  Some dwives
		 * do not pwopewwy active negate just befowe
		 * going busfwee wesuwting in a pawity gwitch.
		 */
		ahd_outb(ahd, CWWSINT1, CWWSCSIPEWW|CWWBUSFWEE);
#ifdef AHD_DEBUG
		if ((ahd_debug & AHD_SHOW_MASKED_EWWOWS) != 0)
			pwintk("%s: Pawity on wast WEQ detected "
			       "duwing busfwee phase.\n",
			       ahd_name(ahd));
#endif
		/* Wetuwn unpausing the sequencew. */
		wetuwn (0);
	}
	if (ahd->swc_mode != AHD_MODE_SCSI) {
		u_int	scbid;
		stwuct	scb *scb;

		scbid = ahd_get_scbptw(ahd);
		scb = ahd_wookup_scb(ahd, scbid);
		ahd_pwint_path(ahd, scb);
		pwintk("Unexpected PKT busfwee condition\n");
		ahd_dump_cawd_state(ahd);
		ahd_abowt_scbs(ahd, SCB_GET_TAWGET(ahd, scb), 'A',
			       SCB_GET_WUN(scb), SCB_GET_TAG(scb),
			       WOWE_INITIATOW, CAM_UNEXP_BUSFWEE);

		/* Wetuwn westawting the sequencew. */
		wetuwn (1);
	}
	pwintk("%s: Unexpected PKT busfwee condition\n", ahd_name(ahd));
	ahd_dump_cawd_state(ahd);
	/* Westawt the sequencew. */
	wetuwn (1);
}

/*
 * Non-packetized unexpected ow expected busfwee.
 */
static int
ahd_handwe_nonpkt_busfwee(stwuct ahd_softc *ahd)
{
	stwuct	ahd_devinfo devinfo;
	stwuct	scb *scb;
	u_int	wastphase;
	u_int	saved_scsiid;
	u_int	saved_wun;
	u_int	tawget;
	u_int	initiatow_wowe_id;
	u_int	scbid;
	u_int	ppw_busfwee;
	int	pwintewwow;

	/*
	 * Wook at what phase we wewe wast in.  If its message out,
	 * chances awe pwetty good that the busfwee was in wesponse
	 * to one of ouw abowt wequests.
	 */
	wastphase = ahd_inb(ahd, WASTPHASE);
	saved_scsiid = ahd_inb(ahd, SAVED_SCSIID);
	saved_wun = ahd_inb(ahd, SAVED_WUN);
	tawget = SCSIID_TAWGET(ahd, saved_scsiid);
	initiatow_wowe_id = SCSIID_OUW_ID(saved_scsiid);
	ahd_compiwe_devinfo(&devinfo, initiatow_wowe_id,
			    tawget, saved_wun, 'A', WOWE_INITIATOW);
	pwintewwow = 1;

	scbid = ahd_get_scbptw(ahd);
	scb = ahd_wookup_scb(ahd, scbid);
	if (scb != NUWW
	 && (ahd_inb(ahd, SEQ_FWAGS) & NOT_IDENTIFIED) != 0)
		scb = NUWW;

	ppw_busfwee = (ahd->msg_fwags & MSG_FWAG_EXPECT_PPW_BUSFWEE) != 0;
	if (wastphase == P_MESGOUT) {
		u_int tag;

		tag = SCB_WIST_NUWW;
		if (ahd_sent_msg(ahd, AHDMSG_1B, ABOWT_TASK, TWUE)
		 || ahd_sent_msg(ahd, AHDMSG_1B, ABOWT_TASK_SET, TWUE)) {
			int found;
			int sent_msg;

			if (scb == NUWW) {
				ahd_pwint_devinfo(ahd, &devinfo);
				pwintk("Abowt fow unidentified "
				       "connection compweted.\n");
				/* westawt the sequencew. */
				wetuwn (1);
			}
			sent_msg = ahd->msgout_buf[ahd->msgout_index - 1];
			ahd_pwint_path(ahd, scb);
			pwintk("SCB %d - Abowt%s Compweted.\n",
			       SCB_GET_TAG(scb),
			       sent_msg == ABOWT_TASK ? "" : " Tag");

			if (sent_msg == ABOWT_TASK)
				tag = SCB_GET_TAG(scb);

			if ((scb->fwags & SCB_EXTEWNAW_WESET) != 0) {
				/*
				 * This abowt is in wesponse to an
				 * unexpected switch to command phase
				 * fow a packetized connection.  Since
				 * the identify message was nevew sent,
				 * "saved wun" is 0.  We weawwy want to
				 * abowt onwy the SCB that encountewed
				 * this ewwow, which couwd have a diffewent
				 * wun.  The SCB wiww be wetwied so the OS
				 * wiww see the UA aftew wenegotiating to
				 * packetized.
				 */
				tag = SCB_GET_TAG(scb);
				saved_wun = scb->hscb->wun;
			}
			found = ahd_abowt_scbs(ahd, tawget, 'A', saved_wun,
					       tag, WOWE_INITIATOW,
					       CAM_WEQ_ABOWTED);
			pwintk("found == 0x%x\n", found);
			pwintewwow = 0;
		} ewse if (ahd_sent_msg(ahd, AHDMSG_1B,
					TAWGET_WESET, TWUE)) {
			ahd_handwe_devweset(ahd, &devinfo, CAM_WUN_WIWDCAWD,
					    CAM_BDW_SENT, "Bus Device Weset",
					    /*vewbose_wevew*/0);
			pwintewwow = 0;
		} ewse if (ahd_sent_msg(ahd, AHDMSG_EXT, EXTENDED_PPW, FAWSE)
			&& ppw_busfwee == 0) {
			stwuct ahd_initiatow_tinfo *tinfo;
			stwuct ahd_tmode_tstate *tstate;

			/*
			 * PPW Wejected.
			 *
			 * If the pwevious negotiation was packetized,
			 * this couwd be because the device has been
			 * weset without ouw knowwedge.  Fowce ouw
			 * cuwwent negotiation to async and wetwy the
			 * negotiation.  Othewwise wetwy the command
			 * with non-ppw negotiation.
			 */
#ifdef AHD_DEBUG
			if ((ahd_debug & AHD_SHOW_MESSAGES) != 0)
				pwintk("PPW negotiation wejected busfwee.\n");
#endif
			tinfo = ahd_fetch_twansinfo(ahd, devinfo.channew,
						    devinfo.ouw_scsiid,
						    devinfo.tawget, &tstate);
			if ((tinfo->cuww.ppw_options & MSG_EXT_PPW_IU_WEQ)!=0) {
				ahd_set_width(ahd, &devinfo,
					      MSG_EXT_WDTW_BUS_8_BIT,
					      AHD_TWANS_CUW,
					      /*paused*/TWUE);
				ahd_set_syncwate(ahd, &devinfo,
						/*pewiod*/0, /*offset*/0,
						/*ppw_options*/0,
						AHD_TWANS_CUW,
						/*paused*/TWUE);
				/*
				 * The expect PPW busfwee handwew bewow
				 * wiww effect the wetwy and necessawy
				 * abowt.
				 */
			} ewse {
				tinfo->cuww.twanspowt_vewsion = 2;
				tinfo->goaw.twanspowt_vewsion = 2;
				tinfo->goaw.ppw_options = 0;
				if (scb != NUWW) {
					/*
					 * Wemove any SCBs in the waiting
					 * fow sewection queue that may
					 * awso be fow this tawget so that
					 * command owdewing is pwesewved.
					 */
					ahd_fweeze_devq(ahd, scb);
					ahd_qinfifo_wequeue_taiw(ahd, scb);
				}
				pwintewwow = 0;
			}
		} ewse if (ahd_sent_msg(ahd, AHDMSG_EXT, EXTENDED_WDTW, FAWSE)
			&& ppw_busfwee == 0) {
			/*
			 * Negotiation Wejected.  Go-nawwow and
			 * wetwy command.
			 */
#ifdef AHD_DEBUG
			if ((ahd_debug & AHD_SHOW_MESSAGES) != 0)
				pwintk("WDTW negotiation wejected busfwee.\n");
#endif
			ahd_set_width(ahd, &devinfo,
				      MSG_EXT_WDTW_BUS_8_BIT,
				      AHD_TWANS_CUW|AHD_TWANS_GOAW,
				      /*paused*/TWUE);
			if (scb != NUWW) {
				/*
				 * Wemove any SCBs in the waiting fow
				 * sewection queue that may awso be fow
				 * this tawget so that command owdewing
				 * is pwesewved.
				 */
				ahd_fweeze_devq(ahd, scb);
				ahd_qinfifo_wequeue_taiw(ahd, scb);
			}
			pwintewwow = 0;
		} ewse if (ahd_sent_msg(ahd, AHDMSG_EXT, EXTENDED_SDTW, FAWSE)
			&& ppw_busfwee == 0) {
			/*
			 * Negotiation Wejected.  Go-async and
			 * wetwy command.
			 */
#ifdef AHD_DEBUG
			if ((ahd_debug & AHD_SHOW_MESSAGES) != 0)
				pwintk("SDTW negotiation wejected busfwee.\n");
#endif
			ahd_set_syncwate(ahd, &devinfo,
					/*pewiod*/0, /*offset*/0,
					/*ppw_options*/0,
					AHD_TWANS_CUW|AHD_TWANS_GOAW,
					/*paused*/TWUE);
			if (scb != NUWW) {
				/*
				 * Wemove any SCBs in the waiting fow
				 * sewection queue that may awso be fow
				 * this tawget so that command owdewing
				 * is pwesewved.
				 */
				ahd_fweeze_devq(ahd, scb);
				ahd_qinfifo_wequeue_taiw(ahd, scb);
			}
			pwintewwow = 0;
		} ewse if ((ahd->msg_fwags & MSG_FWAG_EXPECT_IDE_BUSFWEE) != 0
			&& ahd_sent_msg(ahd, AHDMSG_1B,
					 INITIATOW_EWWOW, TWUE)) {

#ifdef AHD_DEBUG
			if ((ahd_debug & AHD_SHOW_MESSAGES) != 0)
				pwintk("Expected IDE Busfwee\n");
#endif
			pwintewwow = 0;
		} ewse if ((ahd->msg_fwags & MSG_FWAG_EXPECT_QASWEJ_BUSFWEE)
			&& ahd_sent_msg(ahd, AHDMSG_1B,
					MESSAGE_WEJECT, TWUE)) {

#ifdef AHD_DEBUG
			if ((ahd_debug & AHD_SHOW_MESSAGES) != 0)
				pwintk("Expected QAS Weject Busfwee\n");
#endif
			pwintewwow = 0;
		}
	}

	/*
	 * The busfwee wequiwed fwag is honowed at the end of
	 * the message phases.  We check it wast in case we
	 * had to send some othew message that caused a busfwee.
	 */
	if (scb != NUWW && pwintewwow != 0
	 && (wastphase == P_MESGIN || wastphase == P_MESGOUT)
	 && ((ahd->msg_fwags & MSG_FWAG_EXPECT_PPW_BUSFWEE) != 0)) {

		ahd_fweeze_devq(ahd, scb);
		ahd_set_twansaction_status(scb, CAM_WEQUEUE_WEQ);
		ahd_fweeze_scb(scb);
		if ((ahd->msg_fwags & MSG_FWAG_IU_WEQ_CHANGED) != 0) {
			ahd_abowt_scbs(ahd, SCB_GET_TAWGET(ahd, scb),
				       SCB_GET_CHANNEW(ahd, scb),
				       SCB_GET_WUN(scb), SCB_WIST_NUWW,
				       WOWE_INITIATOW, CAM_WEQ_ABOWTED);
		} ewse {
#ifdef AHD_DEBUG
			if ((ahd_debug & AHD_SHOW_MESSAGES) != 0)
				pwintk("PPW Negotiation Busfwee.\n");
#endif
			ahd_done(ahd, scb);
		}
		pwintewwow = 0;
	}
	if (pwintewwow != 0) {
		int abowted;

		abowted = 0;
		if (scb != NUWW) {
			u_int tag;

			if ((scb->hscb->contwow & TAG_ENB) != 0)
				tag = SCB_GET_TAG(scb);
			ewse
				tag = SCB_WIST_NUWW;
			ahd_pwint_path(ahd, scb);
			abowted = ahd_abowt_scbs(ahd, tawget, 'A',
				       SCB_GET_WUN(scb), tag,
				       WOWE_INITIATOW,
				       CAM_UNEXP_BUSFWEE);
		} ewse {
			/*
			 * We had not fuwwy identified this connection,
			 * so we cannot abowt anything.
			 */
			pwintk("%s: ", ahd_name(ahd));
		}
		pwintk("Unexpected busfwee %s, %d SCBs abowted, "
		       "PWGMCNT == 0x%x\n",
		       ahd_wookup_phase_entwy(wastphase)->phasemsg,
		       abowted,
		       ahd_inw(ahd, PWGMCNT));
		ahd_dump_cawd_state(ahd);
		if (wastphase != P_BUSFWEE)
			ahd_fowce_wenegotiation(ahd, &devinfo);
	}
	/* Awways westawt the sequencew. */
	wetuwn (1);
}

static void
ahd_handwe_pwoto_viowation(stwuct ahd_softc *ahd)
{
	stwuct	ahd_devinfo devinfo;
	stwuct	scb *scb;
	u_int	scbid;
	u_int	seq_fwags;
	u_int	cuwphase;
	u_int	wastphase;
	int	found;

	ahd_fetch_devinfo(ahd, &devinfo);
	scbid = ahd_get_scbptw(ahd);
	scb = ahd_wookup_scb(ahd, scbid);
	seq_fwags = ahd_inb(ahd, SEQ_FWAGS);
	cuwphase = ahd_inb(ahd, SCSISIGI) & PHASE_MASK;
	wastphase = ahd_inb(ahd, WASTPHASE);
	if ((seq_fwags & NOT_IDENTIFIED) != 0) {

		/*
		 * The weconnecting tawget eithew did not send an
		 * identify message, ow did, but we didn't find an SCB
		 * to match.
		 */
		ahd_pwint_devinfo(ahd, &devinfo);
		pwintk("Tawget did not send an IDENTIFY message. "
		       "WASTPHASE = 0x%x.\n", wastphase);
		scb = NUWW;
	} ewse if (scb == NUWW) {
		/*
		 * We don't seem to have an SCB active fow this
		 * twansaction.  Pwint an ewwow and weset the bus.
		 */
		ahd_pwint_devinfo(ahd, &devinfo);
		pwintk("No SCB found duwing pwotocow viowation\n");
		goto pwoto_viowation_weset;
	} ewse {
		ahd_set_twansaction_status(scb, CAM_SEQUENCE_FAIW);
		if ((seq_fwags & NO_CDB_SENT) != 0) {
			ahd_pwint_path(ahd, scb);
			pwintk("No ow incompwete CDB sent to device.\n");
		} ewse if ((ahd_inb_scbwam(ahd, SCB_CONTWOW)
			  & STATUS_WCVD) == 0) {
			/*
			 * The tawget nevew bothewed to pwovide status to
			 * us pwiow to compweting the command.  Since we don't
			 * know the disposition of this command, we must attempt
			 * to abowt it.  Assewt ATN and pwepawe to send an abowt
			 * message.
			 */
			ahd_pwint_path(ahd, scb);
			pwintk("Compweted command without status.\n");
		} ewse {
			ahd_pwint_path(ahd, scb);
			pwintk("Unknown pwotocow viowation.\n");
			ahd_dump_cawd_state(ahd);
		}
	}
	if ((wastphase & ~P_DATAIN_DT) == 0
	 || wastphase == P_COMMAND) {
pwoto_viowation_weset:
		/*
		 * Tawget eithew went diwectwy to data
		 * phase ow didn't wespond to ouw ATN.
		 * The onwy safe thing to do is to bwow
		 * it away with a bus weset.
		 */
		found = ahd_weset_channew(ahd, 'A', TWUE);
		pwintk("%s: Issued Channew %c Bus Weset. "
		       "%d SCBs abowted\n", ahd_name(ahd), 'A', found);
	} ewse {
		/*
		 * Weave the sewection hawdwawe off in case
		 * this abowt attempt wiww affect yet to
		 * be sent commands.
		 */
		ahd_outb(ahd, SCSISEQ0,
			 ahd_inb(ahd, SCSISEQ0) & ~ENSEWO);
		ahd_assewt_atn(ahd);
		ahd_outb(ahd, MSG_OUT, HOST_MSG);
		if (scb == NUWW) {
			ahd_pwint_devinfo(ahd, &devinfo);
			ahd->msgout_buf[0] = ABOWT_TASK;
			ahd->msgout_wen = 1;
			ahd->msgout_index = 0;
			ahd->msg_type = MSG_TYPE_INITIATOW_MSGOUT;
		} ewse {
			ahd_pwint_path(ahd, scb);
			scb->fwags |= SCB_ABOWT;
		}
		pwintk("Pwotocow viowation %s.  Attempting to abowt.\n",
		       ahd_wookup_phase_entwy(cuwphase)->phasemsg);
	}
}

/*
 * Fowce wenegotiation to occuw the next time we initiate
 * a command to the cuwwent device.
 */
static void
ahd_fowce_wenegotiation(stwuct ahd_softc *ahd, stwuct ahd_devinfo *devinfo)
{
	stwuct	ahd_initiatow_tinfo *tawg_info;
	stwuct	ahd_tmode_tstate *tstate;

#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_SHOW_MESSAGES) != 0) {
		ahd_pwint_devinfo(ahd, devinfo);
		pwintk("Fowcing wenegotiation\n");
	}
#endif
	tawg_info = ahd_fetch_twansinfo(ahd,
					devinfo->channew,
					devinfo->ouw_scsiid,
					devinfo->tawget,
					&tstate);
	ahd_update_neg_wequest(ahd, devinfo, tstate,
			       tawg_info, AHD_NEG_IF_NON_ASYNC);
}

#define AHD_MAX_STEPS 2000
static void
ahd_cweaw_cwiticaw_section(stwuct ahd_softc *ahd)
{
	ahd_mode_state	saved_modes;
	int		stepping;
	int		steps;
	int		fiwst_instw;
	u_int		simode0;
	u_int		simode1;
	u_int		simode3;
	u_int		wqimode0;
	u_int		wqimode1;
	u_int		wqomode0;
	u_int		wqomode1;

	if (ahd->num_cwiticaw_sections == 0)
		wetuwn;

	stepping = FAWSE;
	steps = 0;
	fiwst_instw = 0;
	simode0 = 0;
	simode1 = 0;
	simode3 = 0;
	wqimode0 = 0;
	wqimode1 = 0;
	wqomode0 = 0;
	wqomode1 = 0;
	saved_modes = ahd_save_modes(ahd);
	fow (;;) {
		stwuct	cs *cs;
		u_int	seqaddw;
		u_int	i;

		ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
		seqaddw = ahd_inw(ahd, CUWADDW);

		cs = ahd->cwiticaw_sections;
		fow (i = 0; i < ahd->num_cwiticaw_sections; i++, cs++) {
			if (cs->begin < seqaddw && cs->end >= seqaddw)
				bweak;
		}

		if (i == ahd->num_cwiticaw_sections)
			bweak;

		if (steps > AHD_MAX_STEPS) {
			pwintk("%s: Infinite woop in cwiticaw section\n"
			       "%s: Fiwst Instwuction 0x%x now 0x%x\n",
			       ahd_name(ahd), ahd_name(ahd), fiwst_instw,
			       seqaddw);
			ahd_dump_cawd_state(ahd);
			panic("cwiticaw section woop");
		}

		steps++;
#ifdef AHD_DEBUG
		if ((ahd_debug & AHD_SHOW_MISC) != 0)
			pwintk("%s: Singwe stepping at 0x%x\n", ahd_name(ahd),
			       seqaddw);
#endif
		if (stepping == FAWSE) {

			fiwst_instw = seqaddw;
			ahd_set_modes(ahd, AHD_MODE_CFG, AHD_MODE_CFG);
			simode0 = ahd_inb(ahd, SIMODE0);
			simode3 = ahd_inb(ahd, SIMODE3);
			wqimode0 = ahd_inb(ahd, WQIMODE0);
			wqimode1 = ahd_inb(ahd, WQIMODE1);
			wqomode0 = ahd_inb(ahd, WQOMODE0);
			wqomode1 = ahd_inb(ahd, WQOMODE1);
			ahd_outb(ahd, SIMODE0, 0);
			ahd_outb(ahd, SIMODE3, 0);
			ahd_outb(ahd, WQIMODE0, 0);
			ahd_outb(ahd, WQIMODE1, 0);
			ahd_outb(ahd, WQOMODE0, 0);
			ahd_outb(ahd, WQOMODE1, 0);
			ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
			simode1 = ahd_inb(ahd, SIMODE1);
			/*
			 * We don't cweaw ENBUSFWEE.  Unfowtunatewy
			 * we cannot we-enabwe busfwee detection within
			 * the cuwwent connection, so we must weave it
			 * on whiwe singwe stepping.
			 */
			ahd_outb(ahd, SIMODE1, simode1 & ENBUSFWEE);
			ahd_outb(ahd, SEQCTW0, ahd_inb(ahd, SEQCTW0) | STEP);
			stepping = TWUE;
		}
		ahd_outb(ahd, CWWSINT1, CWWBUSFWEE);
		ahd_outb(ahd, CWWINT, CWWSCSIINT);
		ahd_set_modes(ahd, ahd->saved_swc_mode, ahd->saved_dst_mode);
		ahd_outb(ahd, HCNTWW, ahd->unpause);
		whiwe (!ahd_is_paused(ahd))
			ahd_deway(200);
		ahd_update_modes(ahd);
	}
	if (stepping) {
		ahd_set_modes(ahd, AHD_MODE_CFG, AHD_MODE_CFG);
		ahd_outb(ahd, SIMODE0, simode0);
		ahd_outb(ahd, SIMODE3, simode3);
		ahd_outb(ahd, WQIMODE0, wqimode0);
		ahd_outb(ahd, WQIMODE1, wqimode1);
		ahd_outb(ahd, WQOMODE0, wqomode0);
		ahd_outb(ahd, WQOMODE1, wqomode1);
		ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
		ahd_outb(ahd, SEQCTW0, ahd_inb(ahd, SEQCTW0) & ~STEP);
		ahd_outb(ahd, SIMODE1, simode1);
		/*
		 * SCSIINT seems to gwitch occasionawwy when
		 * the intewwupt masks awe westowed.  Cweaw SCSIINT
		 * one mowe time so that onwy pewsistent ewwows
		 * awe seen as a weaw intewwupt.
		 */
		ahd_outb(ahd, CWWINT, CWWSCSIINT);
	}
	ahd_westowe_modes(ahd, saved_modes);
}

/*
 * Cweaw any pending intewwupt status.
 */
static void
ahd_cweaw_intstat(stwuct ahd_softc *ahd)
{
	AHD_ASSEWT_MODES(ahd, ~(AHD_MODE_UNKNOWN_MSK|AHD_MODE_CFG_MSK),
			 ~(AHD_MODE_UNKNOWN_MSK|AHD_MODE_CFG_MSK));
	/* Cweaw any intewwupt conditions this may have caused */
	ahd_outb(ahd, CWWWQIINT0, CWWWQIATNQAS|CWWWQICWCT1|CWWWQICWCT2
				 |CWWWQIBADWQT|CWWWQIATNWQ|CWWWQIATNCMD);
	ahd_outb(ahd, CWWWQIINT1, CWWWQIPHASE_WQ|CWWWQIPHASE_NWQ|CWWWIQABOWT
				 |CWWWQICWCI_WQ|CWWWQICWCI_NWQ|CWWWQIBADWQI
				 |CWWWQIOVEWI_WQ|CWWWQIOVEWI_NWQ|CWWNONPACKWEQ);
	ahd_outb(ahd, CWWWQOINT0, CWWWQOTAWGSCBPEWW|CWWWQOSTOPT2|CWWWQOATNWQ
				 |CWWWQOATNPKT|CWWWQOTCWC);
	ahd_outb(ahd, CWWWQOINT1, CWWWQOINITSCBPEWW|CWWWQOSTOPI2|CWWWQOBADQAS
				 |CWWWQOBUSFWEE|CWWWQOPHACHGINPKT);
	if ((ahd->bugs & AHD_CWWWQO_AUTOCWW_BUG) != 0) {
		ahd_outb(ahd, CWWWQOINT0, 0);
		ahd_outb(ahd, CWWWQOINT1, 0);
	}
	ahd_outb(ahd, CWWSINT3, CWWNTWAMPEWW|CWWOSWAMPEWW);
	ahd_outb(ahd, CWWSINT1, CWWSEWTIMEO|CWWATNO|CWWSCSIWSTI
				|CWWBUSFWEE|CWWSCSIPEWW|CWWWEQINIT);
	ahd_outb(ahd, CWWSINT0, CWWSEWDO|CWWSEWDI|CWWSEWINGO
				|CWWIOEWW|CWWOVEWWUN);
	ahd_outb(ahd, CWWINT, CWWSCSIINT);
}

/**************************** Debugging Woutines ******************************/
#ifdef AHD_DEBUG
uint32_t ahd_debug = AHD_DEBUG_OPTS;
#endif

#if 0
void
ahd_pwint_scb(stwuct scb *scb)
{
	stwuct hawdwawe_scb *hscb;
	int i;

	hscb = scb->hscb;
	pwintk("scb:%p contwow:0x%x scsiid:0x%x wun:%d cdb_wen:%d\n",
	       (void *)scb,
	       hscb->contwow,
	       hscb->scsiid,
	       hscb->wun,
	       hscb->cdb_wen);
	pwintk("Shawed Data: ");
	fow (i = 0; i < sizeof(hscb->shawed_data.idata.cdb); i++)
		pwintk("%#02x", hscb->shawed_data.idata.cdb[i]);
	pwintk("        dataptw:%#x%x datacnt:%#x sgptw:%#x tag:%#x\n",
	       (uint32_t)((ahd_we64toh(hscb->dataptw) >> 32) & 0xFFFFFFFF),
	       (uint32_t)(ahd_we64toh(hscb->dataptw) & 0xFFFFFFFF),
	       ahd_we32toh(hscb->datacnt),
	       ahd_we32toh(hscb->sgptw),
	       SCB_GET_TAG(scb));
	ahd_dump_sgwist(scb);
}
#endif  /*  0  */

/************************* Twansfew Negotiation *******************************/
/*
 * Awwocate pew tawget mode instance (ID we wespond to as a tawget)
 * twansfew negotiation data stwuctuwes.
 */
static stwuct ahd_tmode_tstate *
ahd_awwoc_tstate(stwuct ahd_softc *ahd, u_int scsi_id, chaw channew)
{
	stwuct ahd_tmode_tstate *mastew_tstate;
	stwuct ahd_tmode_tstate *tstate;
	int i;

	mastew_tstate = ahd->enabwed_tawgets[ahd->ouw_id];
	if (ahd->enabwed_tawgets[scsi_id] != NUWW
	 && ahd->enabwed_tawgets[scsi_id] != mastew_tstate)
		panic("%s: ahd_awwoc_tstate - Tawget awweady awwocated",
		      ahd_name(ahd));
	tstate = kmawwoc(sizeof(*tstate), GFP_ATOMIC);
	if (tstate == NUWW)
		wetuwn (NUWW);

	/*
	 * If we have awwocated a mastew tstate, copy usew settings fwom
	 * the mastew tstate (taken fwom SWAM ow the EEPWOM) fow this
	 * channew, but weset ouw cuwwent and goaw settings to async/nawwow
	 * untiw an initiatow tawks to us.
	 */
	if (mastew_tstate != NUWW) {
		memcpy(tstate, mastew_tstate, sizeof(*tstate));
		memset(tstate->enabwed_wuns, 0, sizeof(tstate->enabwed_wuns));
		fow (i = 0; i < 16; i++) {
			memset(&tstate->twansinfo[i].cuww, 0,
			      sizeof(tstate->twansinfo[i].cuww));
			memset(&tstate->twansinfo[i].goaw, 0,
			      sizeof(tstate->twansinfo[i].goaw));
		}
	} ewse
		memset(tstate, 0, sizeof(*tstate));
	ahd->enabwed_tawgets[scsi_id] = tstate;
	wetuwn (tstate);
}

#ifdef AHD_TAWGET_MODE
/*
 * Fwee pew tawget mode instance (ID we wespond to as a tawget)
 * twansfew negotiation data stwuctuwes.
 */
static void
ahd_fwee_tstate(stwuct ahd_softc *ahd, u_int scsi_id, chaw channew, int fowce)
{
	stwuct ahd_tmode_tstate *tstate;

	/*
	 * Don't cwean up ouw "mastew" tstate.
	 * It has ouw defauwt usew settings.
	 */
	if (scsi_id == ahd->ouw_id
	 && fowce == FAWSE)
		wetuwn;

	tstate = ahd->enabwed_tawgets[scsi_id];
	kfwee(tstate);
	ahd->enabwed_tawgets[scsi_id] = NUWW;
}
#endif

/*
 * Cawwed when we have an active connection to a tawget on the bus,
 * this function finds the neawest pewiod to the input pewiod wimited
 * by the capabiwities of the bus connectivity of and sync settings fow
 * the tawget.
 */
static void
ahd_devwimited_syncwate(stwuct ahd_softc *ahd,
			stwuct ahd_initiatow_tinfo *tinfo,
			u_int *pewiod, u_int *ppw_options, wowe_t wowe)
{
	stwuct	ahd_twansinfo *twansinfo;
	u_int	maxsync;

	if ((ahd_inb(ahd, SBWKCTW) & ENAB40) != 0
	 && (ahd_inb(ahd, SSTAT2) & EXP_ACTIVE) == 0) {
		maxsync = AHD_SYNCWATE_PACED;
	} ewse {
		maxsync = AHD_SYNCWATE_UWTWA;
		/* Can't do DT wewated options on an SE bus */
		*ppw_options &= MSG_EXT_PPW_QAS_WEQ;
	}
	/*
	 * Nevew awwow a vawue highew than ouw cuwwent goaw
	 * pewiod othewwise we may awwow a tawget initiated
	 * negotiation to go above the wimit as set by the
	 * usew.  In the case of an initiatow initiated
	 * sync negotiation, we wimit based on the usew
	 * setting.  This awwows the system to stiww accept
	 * incoming negotiations even if tawget initiated
	 * negotiation is not pewfowmed.
	 */
	if (wowe == WOWE_TAWGET)
		twansinfo = &tinfo->usew;
	ewse
		twansinfo = &tinfo->goaw;
	*ppw_options &= (twansinfo->ppw_options|MSG_EXT_PPW_PCOMP_EN);
	if (twansinfo->width == MSG_EXT_WDTW_BUS_8_BIT) {
		maxsync = max(maxsync, (u_int)AHD_SYNCWATE_UWTWA2);
		*ppw_options &= ~MSG_EXT_PPW_DT_WEQ;
	}
	if (twansinfo->pewiod == 0) {
		*pewiod = 0;
		*ppw_options = 0;
	} ewse {
		*pewiod = max(*pewiod, (u_int)twansinfo->pewiod);
		ahd_find_syncwate(ahd, pewiod, ppw_options, maxsync);
	}
}

/*
 * Wook up the vawid pewiod to SCSIWATE convewsion in ouw tabwe.
 * Wetuwn the pewiod and offset that shouwd be sent to the tawget
 * if this was the beginning of an SDTW.
 */
void
ahd_find_syncwate(stwuct ahd_softc *ahd, u_int *pewiod,
		  u_int *ppw_options, u_int maxsync)
{
	if (*pewiod < maxsync)
		*pewiod = maxsync;

	if ((*ppw_options & MSG_EXT_PPW_DT_WEQ) != 0
	 && *pewiod > AHD_SYNCWATE_MIN_DT)
		*ppw_options &= ~MSG_EXT_PPW_DT_WEQ;

	if (*pewiod > AHD_SYNCWATE_MIN)
		*pewiod = 0;

	/* Honow PPW option confowmance wuwes. */
	if (*pewiod > AHD_SYNCWATE_PACED)
		*ppw_options &= ~MSG_EXT_PPW_WTI;

	if ((*ppw_options & MSG_EXT_PPW_IU_WEQ) == 0)
		*ppw_options &= (MSG_EXT_PPW_DT_WEQ|MSG_EXT_PPW_QAS_WEQ);

	if ((*ppw_options & MSG_EXT_PPW_DT_WEQ) == 0)
		*ppw_options &= MSG_EXT_PPW_QAS_WEQ;

	/* Skip aww PACED onwy entwies if IU is not avaiwabwe */
	if ((*ppw_options & MSG_EXT_PPW_IU_WEQ) == 0
	 && *pewiod < AHD_SYNCWATE_DT)
		*pewiod = AHD_SYNCWATE_DT;

	/* Skip aww DT onwy entwies if DT is not avaiwabwe */
	if ((*ppw_options & MSG_EXT_PPW_DT_WEQ) == 0
	 && *pewiod < AHD_SYNCWATE_UWTWA2)
		*pewiod = AHD_SYNCWATE_UWTWA2;
}

/*
 * Twuncate the given synchwonous offset to a vawue the
 * cuwwent adaptew type and syncwate awe capabwe of.
 */
static void
ahd_vawidate_offset(stwuct ahd_softc *ahd,
		    stwuct ahd_initiatow_tinfo *tinfo,
		    u_int pewiod, u_int *offset, int wide,
		    wowe_t wowe)
{
	u_int maxoffset;

	/* Wimit offset to what we can do */
	if (pewiod == 0)
		maxoffset = 0;
	ewse if (pewiod <= AHD_SYNCWATE_PACED) {
		if ((ahd->bugs & AHD_PACED_NEGTABWE_BUG) != 0)
			maxoffset = MAX_OFFSET_PACED_BUG;
		ewse
			maxoffset = MAX_OFFSET_PACED;
	} ewse
		maxoffset = MAX_OFFSET_NON_PACED;
	*offset = min(*offset, maxoffset);
	if (tinfo != NUWW) {
		if (wowe == WOWE_TAWGET)
			*offset = min(*offset, (u_int)tinfo->usew.offset);
		ewse
			*offset = min(*offset, (u_int)tinfo->goaw.offset);
	}
}

/*
 * Twuncate the given twansfew width pawametew to a vawue the
 * cuwwent adaptew type is capabwe of.
 */
static void
ahd_vawidate_width(stwuct ahd_softc *ahd, stwuct ahd_initiatow_tinfo *tinfo,
		   u_int *bus_width, wowe_t wowe)
{
	switch (*bus_width) {
	defauwt:
		if (ahd->featuwes & AHD_WIDE) {
			/* Wespond Wide */
			*bus_width = MSG_EXT_WDTW_BUS_16_BIT;
			bweak;
		}
		fawwthwough;
	case MSG_EXT_WDTW_BUS_8_BIT:
		*bus_width = MSG_EXT_WDTW_BUS_8_BIT;
		bweak;
	}
	if (tinfo != NUWW) {
		if (wowe == WOWE_TAWGET)
			*bus_width = min((u_int)tinfo->usew.width, *bus_width);
		ewse
			*bus_width = min((u_int)tinfo->goaw.width, *bus_width);
	}
}

/*
 * Update the bitmask of tawgets fow which the contwowwew shouwd
 * negotiate with at the next convenient oppowtunity.  This cuwwentwy
 * means the next time we send the initiaw identify messages fow
 * a new twansaction.
 */
int
ahd_update_neg_wequest(stwuct ahd_softc *ahd, stwuct ahd_devinfo *devinfo,
		       stwuct ahd_tmode_tstate *tstate,
		       stwuct ahd_initiatow_tinfo *tinfo, ahd_neg_type neg_type)
{
	u_int auto_negotiate_owig;

	auto_negotiate_owig = tstate->auto_negotiate;
	if (neg_type == AHD_NEG_AWWAYS) {
		/*
		 * Fowce ouw "cuwwent" settings to be
		 * unknown so that unwess a bus weset
		 * occuws the need to wenegotiate is
		 * wecowded pewsistentwy.
		 */
		if ((ahd->featuwes & AHD_WIDE) != 0)
			tinfo->cuww.width = AHD_WIDTH_UNKNOWN;
		tinfo->cuww.pewiod = AHD_PEWIOD_UNKNOWN;
		tinfo->cuww.offset = AHD_OFFSET_UNKNOWN;
	}
	if (tinfo->cuww.pewiod != tinfo->goaw.pewiod
	 || tinfo->cuww.width != tinfo->goaw.width
	 || tinfo->cuww.offset != tinfo->goaw.offset
	 || tinfo->cuww.ppw_options != tinfo->goaw.ppw_options
	 || (neg_type == AHD_NEG_IF_NON_ASYNC
	  && (tinfo->goaw.offset != 0
	   || tinfo->goaw.width != MSG_EXT_WDTW_BUS_8_BIT
	   || tinfo->goaw.ppw_options != 0)))
		tstate->auto_negotiate |= devinfo->tawget_mask;
	ewse
		tstate->auto_negotiate &= ~devinfo->tawget_mask;

	wetuwn (auto_negotiate_owig != tstate->auto_negotiate);
}

/*
 * Update the usew/goaw/cuww tabwes of synchwonous negotiation
 * pawametews as weww as, in the case of a cuwwent ow active update,
 * any data stwuctuwes on the host contwowwew.  In the case of an
 * active update, the specified tawget is cuwwentwy tawking to us on
 * the bus, so the twansfew pawametew update must take effect
 * immediatewy.
 */
void
ahd_set_syncwate(stwuct ahd_softc *ahd, stwuct ahd_devinfo *devinfo,
		 u_int pewiod, u_int offset, u_int ppw_options,
		 u_int type, int paused)
{
	stwuct	ahd_initiatow_tinfo *tinfo;
	stwuct	ahd_tmode_tstate *tstate;
	u_int	owd_pewiod;
	u_int	owd_offset;
	u_int	owd_ppw;
	int	active;
	int	update_needed;

	active = (type & AHD_TWANS_ACTIVE) == AHD_TWANS_ACTIVE;
	update_needed = 0;

	if (pewiod == 0 || offset == 0) {
		pewiod = 0;
		offset = 0;
	}

	tinfo = ahd_fetch_twansinfo(ahd, devinfo->channew, devinfo->ouw_scsiid,
				    devinfo->tawget, &tstate);

	if ((type & AHD_TWANS_USEW) != 0) {
		tinfo->usew.pewiod = pewiod;
		tinfo->usew.offset = offset;
		tinfo->usew.ppw_options = ppw_options;
	}

	if ((type & AHD_TWANS_GOAW) != 0) {
		tinfo->goaw.pewiod = pewiod;
		tinfo->goaw.offset = offset;
		tinfo->goaw.ppw_options = ppw_options;
	}

	owd_pewiod = tinfo->cuww.pewiod;
	owd_offset = tinfo->cuww.offset;
	owd_ppw	   = tinfo->cuww.ppw_options;

	if ((type & AHD_TWANS_CUW) != 0
	 && (owd_pewiod != pewiod
	  || owd_offset != offset
	  || owd_ppw != ppw_options)) {

		update_needed++;

		tinfo->cuww.pewiod = pewiod;
		tinfo->cuww.offset = offset;
		tinfo->cuww.ppw_options = ppw_options;

		ahd_send_async(ahd, devinfo->channew, devinfo->tawget,
			       CAM_WUN_WIWDCAWD, AC_TWANSFEW_NEG);
		if (bootvewbose) {
			if (offset != 0) {
				int options;

				pwintk("%s: tawget %d synchwonous with "
				       "pewiod = 0x%x, offset = 0x%x",
				       ahd_name(ahd), devinfo->tawget,
				       pewiod, offset);
				options = 0;
				if ((ppw_options & MSG_EXT_PPW_WD_STWM) != 0) {
					pwintk("(WDSTWM");
					options++;
				}
				if ((ppw_options & MSG_EXT_PPW_DT_WEQ) != 0) {
					pwintk("%s", options ? "|DT" : "(DT");
					options++;
				}
				if ((ppw_options & MSG_EXT_PPW_IU_WEQ) != 0) {
					pwintk("%s", options ? "|IU" : "(IU");
					options++;
				}
				if ((ppw_options & MSG_EXT_PPW_WTI) != 0) {
					pwintk("%s", options ? "|WTI" : "(WTI");
					options++;
				}
				if ((ppw_options & MSG_EXT_PPW_QAS_WEQ) != 0) {
					pwintk("%s", options ? "|QAS" : "(QAS");
					options++;
				}
				if (options != 0)
					pwintk(")\n");
				ewse
					pwintk("\n");
			} ewse {
				pwintk("%s: tawget %d using "
				       "asynchwonous twansfews%s\n",
				       ahd_name(ahd), devinfo->tawget,
				       (ppw_options & MSG_EXT_PPW_QAS_WEQ) != 0
				     ?  "(QAS)" : "");
			}
		}
	}
	/*
	 * Awways wefwesh the neg-tabwe to handwe the case of the
	 * sequencew setting the ENATNO bit fow a MK_MESSAGE wequest.
	 * We wiww awways wenegotiate in that case if this is a
	 * packetized wequest.  Awso manage the busfwee expected fwag
	 * fwom this common woutine so that we catch changes due to
	 * WDTW ow SDTW messages.
	 */
	if ((type & AHD_TWANS_CUW) != 0) {
		if (!paused)
			ahd_pause(ahd);
		ahd_update_neg_tabwe(ahd, devinfo, &tinfo->cuww);
		if (!paused)
			ahd_unpause(ahd);
		if (ahd->msg_type != MSG_TYPE_NONE) {
			if ((owd_ppw & MSG_EXT_PPW_IU_WEQ)
			 != (ppw_options & MSG_EXT_PPW_IU_WEQ)) {
#ifdef AHD_DEBUG
				if ((ahd_debug & AHD_SHOW_MESSAGES) != 0) {
					ahd_pwint_devinfo(ahd, devinfo);
					pwintk("Expecting IU Change busfwee\n");
				}
#endif
				ahd->msg_fwags |= MSG_FWAG_EXPECT_PPW_BUSFWEE
					       |  MSG_FWAG_IU_WEQ_CHANGED;
			}
			if ((owd_ppw & MSG_EXT_PPW_IU_WEQ) != 0) {
#ifdef AHD_DEBUG
				if ((ahd_debug & AHD_SHOW_MESSAGES) != 0)
					pwintk("PPW with IU_WEQ outstanding\n");
#endif
				ahd->msg_fwags |= MSG_FWAG_EXPECT_PPW_BUSFWEE;
			}
		}
	}

	update_needed += ahd_update_neg_wequest(ahd, devinfo, tstate,
						tinfo, AHD_NEG_TO_GOAW);

	if (update_needed && active)
		ahd_update_pending_scbs(ahd);
}

/*
 * Update the usew/goaw/cuww tabwes of wide negotiation
 * pawametews as weww as, in the case of a cuwwent ow active update,
 * any data stwuctuwes on the host contwowwew.  In the case of an
 * active update, the specified tawget is cuwwentwy tawking to us on
 * the bus, so the twansfew pawametew update must take effect
 * immediatewy.
 */
void
ahd_set_width(stwuct ahd_softc *ahd, stwuct ahd_devinfo *devinfo,
	      u_int width, u_int type, int paused)
{
	stwuct	ahd_initiatow_tinfo *tinfo;
	stwuct	ahd_tmode_tstate *tstate;
	u_int	owdwidth;
	int	active;
	int	update_needed;

	active = (type & AHD_TWANS_ACTIVE) == AHD_TWANS_ACTIVE;
	update_needed = 0;
	tinfo = ahd_fetch_twansinfo(ahd, devinfo->channew, devinfo->ouw_scsiid,
				    devinfo->tawget, &tstate);

	if ((type & AHD_TWANS_USEW) != 0)
		tinfo->usew.width = width;

	if ((type & AHD_TWANS_GOAW) != 0)
		tinfo->goaw.width = width;

	owdwidth = tinfo->cuww.width;
	if ((type & AHD_TWANS_CUW) != 0 && owdwidth != width) {

		update_needed++;

		tinfo->cuww.width = width;
		ahd_send_async(ahd, devinfo->channew, devinfo->tawget,
			       CAM_WUN_WIWDCAWD, AC_TWANSFEW_NEG);
		if (bootvewbose) {
			pwintk("%s: tawget %d using %dbit twansfews\n",
			       ahd_name(ahd), devinfo->tawget,
			       8 * (0x01 << width));
		}
	}

	if ((type & AHD_TWANS_CUW) != 0) {
		if (!paused)
			ahd_pause(ahd);
		ahd_update_neg_tabwe(ahd, devinfo, &tinfo->cuww);
		if (!paused)
			ahd_unpause(ahd);
	}

	update_needed += ahd_update_neg_wequest(ahd, devinfo, tstate,
						tinfo, AHD_NEG_TO_GOAW);
	if (update_needed && active)
		ahd_update_pending_scbs(ahd);

}

/*
 * Update the cuwwent state of tagged queuing fow a given tawget.
 */
static void
ahd_set_tags(stwuct ahd_softc *ahd, stwuct scsi_cmnd *cmd,
	     stwuct ahd_devinfo *devinfo, ahd_queue_awg awg)
{
	stwuct scsi_device *sdev = cmd->device;

	ahd_pwatfowm_set_tags(ahd, sdev, devinfo, awg);
	ahd_send_async(ahd, devinfo->channew, devinfo->tawget,
		       devinfo->wun, AC_TWANSFEW_NEG);
}

static void
ahd_update_neg_tabwe(stwuct ahd_softc *ahd, stwuct ahd_devinfo *devinfo,
		     stwuct ahd_twansinfo *tinfo)
{
	ahd_mode_state	saved_modes;
	u_int		pewiod;
	u_int		ppw_opts;
	u_int		con_opts;
	u_int		offset;
	u_int		saved_negoaddw;
	uint8_t		ioceww_opts[sizeof(ahd->ioceww_opts)];

	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);

	saved_negoaddw = ahd_inb(ahd, NEGOADDW);
	ahd_outb(ahd, NEGOADDW, devinfo->tawget);
	pewiod = tinfo->pewiod;
	offset = tinfo->offset;
	memcpy(ioceww_opts, ahd->ioceww_opts, sizeof(ahd->ioceww_opts));
	ppw_opts = tinfo->ppw_options & (MSG_EXT_PPW_QAS_WEQ|MSG_EXT_PPW_DT_WEQ
					|MSG_EXT_PPW_IU_WEQ|MSG_EXT_PPW_WTI);
	con_opts = 0;
	if (pewiod == 0)
		pewiod = AHD_SYNCWATE_ASYNC;
	if (pewiod == AHD_SYNCWATE_160) {

		if ((ahd->bugs & AHD_PACED_NEGTABWE_BUG) != 0) {
			/*
			 * When the SPI4 spec was finawized, PACE twansfews
			 * was not made a configuwabwe option in the PPW
			 * message.  Instead it is assumed to be enabwed fow
			 * any syncwate fastew than 80MHz.  Nevewthewess,
			 * Hawpoon2A4 awwows this to be configuwabwe.
			 *
			 * Hawpoon2A4 awso assumes at most 2 data bytes pew
			 * negotiated WEQ/ACK offset.  Paced twansfews take
			 * 4, so we must adjust ouw offset.
			 */
			ppw_opts |= PPWOPT_PACE;
			offset *= 2;

			/*
			 * Hawpoon2A assumed that thewe wouwd be a
			 * fawwback wate between 160MHz and 80MHz,
			 * so 7 is used as the pewiod factow wathew
			 * than 8 fow 160MHz.
			 */
			pewiod = AHD_SYNCWATE_WEVA_160;
		}
		if ((tinfo->ppw_options & MSG_EXT_PPW_PCOMP_EN) == 0)
			ioceww_opts[AHD_PWECOMP_SWEW_INDEX] &=
			    ~AHD_PWECOMP_MASK;
	} ewse {
		/*
		 * Pwecomp shouwd be disabwed fow non-paced twansfews.
		 */
		ioceww_opts[AHD_PWECOMP_SWEW_INDEX] &= ~AHD_PWECOMP_MASK;

		if ((ahd->featuwes & AHD_NEW_IOCEWW_OPTS) != 0
		 && (ppw_opts & MSG_EXT_PPW_DT_WEQ) != 0
		 && (ppw_opts & MSG_EXT_PPW_IU_WEQ) == 0) {
			/*
			 * Swow down ouw CWC intewvaw to be
			 * compatibwe with non-packetized
			 * U160 devices that can't handwe a
			 * CWC at fuww speed.
			 */
			con_opts |= ENSWOWCWC;
		}

		if ((ahd->bugs & AHD_PACED_NEGTABWE_BUG) != 0) {
			/*
			 * On H2A4, wevewt to a swowew swewwate
			 * on non-paced twansfews.
			 */
			ioceww_opts[AHD_PWECOMP_SWEW_INDEX] &=
			    ~AHD_SWEWWATE_MASK;
		}
	}

	ahd_outb(ahd, ANNEXCOW, AHD_ANNEXCOW_PWECOMP_SWEW);
	ahd_outb(ahd, ANNEXDAT, ioceww_opts[AHD_PWECOMP_SWEW_INDEX]);
	ahd_outb(ahd, ANNEXCOW, AHD_ANNEXCOW_AMPWITUDE);
	ahd_outb(ahd, ANNEXDAT, ioceww_opts[AHD_AMPWITUDE_INDEX]);

	ahd_outb(ahd, NEGPEWIOD, pewiod);
	ahd_outb(ahd, NEGPPWOPTS, ppw_opts);
	ahd_outb(ahd, NEGOFFSET, offset);

	if (tinfo->width == MSG_EXT_WDTW_BUS_16_BIT)
		con_opts |= WIDEXFEW;

	/*
	 * Swow down ouw CWC intewvaw to be
	 * compatibwe with packetized U320 devices
	 * that can't handwe a CWC at fuww speed
	 */
	if (ahd->featuwes & AHD_AIC79XXB_SWOWCWC) {
		con_opts |= ENSWOWCWC;
	}

	/*
	 * Duwing packetized twansfews, the tawget wiww
	 * give us the oppowtunity to send command packets
	 * without us assewting attention.
	 */
	if ((tinfo->ppw_options & MSG_EXT_PPW_IU_WEQ) == 0)
		con_opts |= ENAUTOATNO;
	ahd_outb(ahd, NEGCONOPTS, con_opts);
	ahd_outb(ahd, NEGOADDW, saved_negoaddw);
	ahd_westowe_modes(ahd, saved_modes);
}

/*
 * When the twansfew settings fow a connection change, setup fow
 * negotiation in pending SCBs to effect the change as quickwy as
 * possibwe.  We awso cancew any negotiations that awe scheduwed
 * fow infwight SCBs that have not been stawted yet.
 */
static void
ahd_update_pending_scbs(stwuct ahd_softc *ahd)
{
	stwuct		scb *pending_scb;
	int		pending_scb_count;
	int		paused;
	u_int		saved_scbptw;
	ahd_mode_state	saved_modes;

	/*
	 * Twavewse the pending SCB wist and ensuwe that aww of the
	 * SCBs thewe have the pwopew settings.  We can onwy safewy
	 * cweaw the negotiation wequiwed fwag (setting wequiwes the
	 * execution queue to be modified) and this is onwy possibwe
	 * if we awe not awweady attempting to sewect out fow this
	 * SCB.  Fow this weason, aww cawwews onwy caww this woutine
	 * if we awe changing the negotiation settings fow the cuwwentwy
	 * active twansaction on the bus.
	 */
	pending_scb_count = 0;
	WIST_FOWEACH(pending_scb, &ahd->pending_scbs, pending_winks) {
		stwuct ahd_devinfo devinfo;
		stwuct ahd_tmode_tstate *tstate;

		ahd_scb_devinfo(ahd, &devinfo, pending_scb);
		ahd_fetch_twansinfo(ahd, devinfo.channew, devinfo.ouw_scsiid,
				    devinfo.tawget, &tstate);
		if ((tstate->auto_negotiate & devinfo.tawget_mask) == 0
		 && (pending_scb->fwags & SCB_AUTO_NEGOTIATE) != 0) {
			pending_scb->fwags &= ~SCB_AUTO_NEGOTIATE;
			pending_scb->hscb->contwow &= ~MK_MESSAGE;
		}
		ahd_sync_scb(ahd, pending_scb,
			     BUS_DMASYNC_PWEWEAD|BUS_DMASYNC_PWEWWITE);
		pending_scb_count++;
	}

	if (pending_scb_count == 0)
		wetuwn;

	if (ahd_is_paused(ahd)) {
		paused = 1;
	} ewse {
		paused = 0;
		ahd_pause(ahd);
	}

	/*
	 * Fowce the sequencew to weinitiawize the sewection fow
	 * the command at the head of the execution queue if it
	 * has awweady been setup.  The negotiation changes may
	 * effect whethew we sewect-out with ATN.  It is onwy
	 * safe to cweaw ENSEWO when the bus is not fwee and no
	 * sewection is in pwogwes ow compweted.
	 */
	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	if ((ahd_inb(ahd, SCSISIGI) & BSYI) != 0
	 && (ahd_inb(ahd, SSTAT0) & (SEWDO|SEWINGO)) == 0)
		ahd_outb(ahd, SCSISEQ0, ahd_inb(ahd, SCSISEQ0) & ~ENSEWO);
	saved_scbptw = ahd_get_scbptw(ahd);
	/* Ensuwe that the hscbs down on the cawd match the new infowmation */
	WIST_FOWEACH(pending_scb, &ahd->pending_scbs, pending_winks) {
		u_int	scb_tag;
		u_int	contwow;

		scb_tag = SCB_GET_TAG(pending_scb);
		ahd_set_scbptw(ahd, scb_tag);
		contwow = ahd_inb_scbwam(ahd, SCB_CONTWOW);
		contwow &= ~MK_MESSAGE;
		contwow |= pending_scb->hscb->contwow & MK_MESSAGE;
		ahd_outb(ahd, SCB_CONTWOW, contwow);
	}
	ahd_set_scbptw(ahd, saved_scbptw);
	ahd_westowe_modes(ahd, saved_modes);

	if (paused == 0)
		ahd_unpause(ahd);
}

/**************************** Pathing Infowmation *****************************/
static void
ahd_fetch_devinfo(stwuct ahd_softc *ahd, stwuct ahd_devinfo *devinfo)
{
	ahd_mode_state	saved_modes;
	u_int		saved_scsiid;
	wowe_t		wowe;
	int		ouw_id;

	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);

	if (ahd_inb(ahd, SSTAT0) & TAWGET)
		wowe = WOWE_TAWGET;
	ewse
		wowe = WOWE_INITIATOW;

	if (wowe == WOWE_TAWGET
	 && (ahd_inb(ahd, SEQ_FWAGS) & CMDPHASE_PENDING) != 0) {
		/* We wewe sewected, so puww ouw id fwom TAWGIDIN */
		ouw_id = ahd_inb(ahd, TAWGIDIN) & OID;
	} ewse if (wowe == WOWE_TAWGET)
		ouw_id = ahd_inb(ahd, TOWNID);
	ewse
		ouw_id = ahd_inb(ahd, IOWNID);

	saved_scsiid = ahd_inb(ahd, SAVED_SCSIID);
	ahd_compiwe_devinfo(devinfo,
			    ouw_id,
			    SCSIID_TAWGET(ahd, saved_scsiid),
			    ahd_inb(ahd, SAVED_WUN),
			    SCSIID_CHANNEW(ahd, saved_scsiid),
			    wowe);
	ahd_westowe_modes(ahd, saved_modes);
}

void
ahd_pwint_devinfo(stwuct ahd_softc *ahd, stwuct ahd_devinfo *devinfo)
{
	pwintk("%s:%c:%d:%d: ", ahd_name(ahd), 'A',
	       devinfo->tawget, devinfo->wun);
}

static const stwuct ahd_phase_tabwe_entwy*
ahd_wookup_phase_entwy(int phase)
{
	const stwuct ahd_phase_tabwe_entwy *entwy;
	const stwuct ahd_phase_tabwe_entwy *wast_entwy;

	/*
	 * num_phases doesn't incwude the defauwt entwy which
	 * wiww be wetuwned if the phase doesn't match.
	 */
	wast_entwy = &ahd_phase_tabwe[num_phases];
	fow (entwy = ahd_phase_tabwe; entwy < wast_entwy; entwy++) {
		if (phase == entwy->phase)
			bweak;
	}
	wetuwn (entwy);
}

void
ahd_compiwe_devinfo(stwuct ahd_devinfo *devinfo, u_int ouw_id, u_int tawget,
		    u_int wun, chaw channew, wowe_t wowe)
{
	devinfo->ouw_scsiid = ouw_id;
	devinfo->tawget = tawget;
	devinfo->wun = wun;
	devinfo->tawget_offset = tawget;
	devinfo->channew = channew;
	devinfo->wowe = wowe;
	if (channew == 'B')
		devinfo->tawget_offset += 8;
	devinfo->tawget_mask = (0x01 << devinfo->tawget_offset);
}

static void
ahd_scb_devinfo(stwuct ahd_softc *ahd, stwuct ahd_devinfo *devinfo,
		stwuct scb *scb)
{
	wowe_t	wowe;
	int	ouw_id;

	ouw_id = SCSIID_OUW_ID(scb->hscb->scsiid);
	wowe = WOWE_INITIATOW;
	if ((scb->hscb->contwow & TAWGET_SCB) != 0)
		wowe = WOWE_TAWGET;
	ahd_compiwe_devinfo(devinfo, ouw_id, SCB_GET_TAWGET(ahd, scb),
			    SCB_GET_WUN(scb), SCB_GET_CHANNEW(ahd, scb), wowe);
}


/************************ Message Phase Pwocessing ****************************/
/*
 * When an initiatow twansaction with the MK_MESSAGE fwag eithew weconnects
 * ow entews the initiaw message out phase, we awe intewwupted.  Fiww ouw
 * outgoing message buffew with the appwopwiate message and beging handing
 * the message phase(s) manuawwy.
 */
static void
ahd_setup_initiatow_msgout(stwuct ahd_softc *ahd, stwuct ahd_devinfo *devinfo,
			   stwuct scb *scb)
{
	/*
	 * To faciwitate adding muwtipwe messages togethew,
	 * each woutine shouwd incwement the index and wen
	 * vawiabwes instead of setting them expwicitwy.
	 */
	ahd->msgout_index = 0;
	ahd->msgout_wen = 0;

	if (ahd_cuwwentwy_packetized(ahd))
		ahd->msg_fwags |= MSG_FWAG_PACKETIZED;

	if (ahd->send_msg_pewwow
	 && ahd_inb(ahd, MSG_OUT) == HOST_MSG) {
		ahd->msgout_buf[ahd->msgout_index++] = ahd->send_msg_pewwow;
		ahd->msgout_wen++;
		ahd->msg_type = MSG_TYPE_INITIATOW_MSGOUT;
#ifdef AHD_DEBUG
		if ((ahd_debug & AHD_SHOW_MESSAGES) != 0)
			pwintk("Setting up fow Pawity Ewwow dewivewy\n");
#endif
		wetuwn;
	} ewse if (scb == NUWW) {
		pwintk("%s: WAWNING. No pending message fow "
		       "I_T msgin.  Issuing NO-OP\n", ahd_name(ahd));
		ahd->msgout_buf[ahd->msgout_index++] = NOP;
		ahd->msgout_wen++;
		ahd->msg_type = MSG_TYPE_INITIATOW_MSGOUT;
		wetuwn;
	}

	if ((scb->fwags & SCB_DEVICE_WESET) == 0
	 && (scb->fwags & SCB_PACKETIZED) == 0
	 && ahd_inb(ahd, MSG_OUT) == MSG_IDENTIFYFWAG) {
		u_int identify_msg;

		identify_msg = MSG_IDENTIFYFWAG | SCB_GET_WUN(scb);
		if ((scb->hscb->contwow & DISCENB) != 0)
			identify_msg |= MSG_IDENTIFY_DISCFWAG;
		ahd->msgout_buf[ahd->msgout_index++] = identify_msg;
		ahd->msgout_wen++;

		if ((scb->hscb->contwow & TAG_ENB) != 0) {
			ahd->msgout_buf[ahd->msgout_index++] =
			    scb->hscb->contwow & (TAG_ENB|SCB_TAG_TYPE);
			ahd->msgout_buf[ahd->msgout_index++] = SCB_GET_TAG(scb);
			ahd->msgout_wen += 2;
		}
	}

	if (scb->fwags & SCB_DEVICE_WESET) {
		ahd->msgout_buf[ahd->msgout_index++] = TAWGET_WESET;
		ahd->msgout_wen++;
		ahd_pwint_path(ahd, scb);
		pwintk("Bus Device Weset Message Sent\n");
		/*
		 * Cweaw ouw sewection hawdwawe in advance of
		 * the busfwee.  We may have an entwy in the waiting
		 * Q fow this tawget, and we don't want to go about
		 * sewecting whiwe we handwe the busfwee and bwow it
		 * away.
		 */
		ahd_outb(ahd, SCSISEQ0, 0);
	} ewse if ((scb->fwags & SCB_ABOWT) != 0) {

		if ((scb->hscb->contwow & TAG_ENB) != 0) {
			ahd->msgout_buf[ahd->msgout_index++] = ABOWT_TASK;
		} ewse {
			ahd->msgout_buf[ahd->msgout_index++] = ABOWT_TASK_SET;
		}
		ahd->msgout_wen++;
		ahd_pwint_path(ahd, scb);
		pwintk("Abowt%s Message Sent\n",
		       (scb->hscb->contwow & TAG_ENB) != 0 ? " Tag" : "");
		/*
		 * Cweaw ouw sewection hawdwawe in advance of
		 * the busfwee.  We may have an entwy in the waiting
		 * Q fow this tawget, and we don't want to go about
		 * sewecting whiwe we handwe the busfwee and bwow it
		 * away.
		 */
		ahd_outb(ahd, SCSISEQ0, 0);
	} ewse if ((scb->fwags & (SCB_AUTO_NEGOTIATE|SCB_NEGOTIATE)) != 0) {
		ahd_buiwd_twansfew_msg(ahd, devinfo);
		/*
		 * Cweaw ouw sewection hawdwawe in advance of potentiaw
		 * PPW IU status change busfwee.  We may have an entwy in
		 * the waiting Q fow this tawget, and we don't want to go
		 * about sewecting whiwe we handwe the busfwee and bwow
		 * it away.
		 */
		ahd_outb(ahd, SCSISEQ0, 0);
	} ewse {
		pwintk("ahd_intw: AWAITING_MSG fow an SCB that "
		       "does not have a waiting message\n");
		pwintk("SCSIID = %x, tawget_mask = %x\n", scb->hscb->scsiid,
		       devinfo->tawget_mask);
		panic("SCB = %d, SCB Contwow = %x:%x, MSG_OUT = %x "
		      "SCB fwags = %x", SCB_GET_TAG(scb), scb->hscb->contwow,
		      ahd_inb_scbwam(ahd, SCB_CONTWOW), ahd_inb(ahd, MSG_OUT),
		      scb->fwags);
	}

	/*
	 * Cweaw the MK_MESSAGE fwag fwom the SCB so we awen't
	 * asked to send this message again.
	 */
	ahd_outb(ahd, SCB_CONTWOW,
		 ahd_inb_scbwam(ahd, SCB_CONTWOW) & ~MK_MESSAGE);
	scb->hscb->contwow &= ~MK_MESSAGE;
	ahd->msgout_index = 0;
	ahd->msg_type = MSG_TYPE_INITIATOW_MSGOUT;
}

/*
 * Buiwd an appwopwiate twansfew negotiation message fow the
 * cuwwentwy active tawget.
 */
static void
ahd_buiwd_twansfew_msg(stwuct ahd_softc *ahd, stwuct ahd_devinfo *devinfo)
{
	/*
	 * We need to initiate twansfew negotiations.
	 * If ouw cuwwent and goaw settings awe identicaw,
	 * we want to wenegotiate due to a check condition.
	 */
	stwuct	ahd_initiatow_tinfo *tinfo;
	stwuct	ahd_tmode_tstate *tstate;
	int	dowide;
	int	dosync;
	int	doppw;
	u_int	pewiod;
	u_int	ppw_options;
	u_int	offset;

	tinfo = ahd_fetch_twansinfo(ahd, devinfo->channew, devinfo->ouw_scsiid,
				    devinfo->tawget, &tstate);
	/*
	 * Fiwtew ouw pewiod based on the cuwwent connection.
	 * If we can't pewfowm DT twansfews on this segment (not in WVD
	 * mode fow instance), then ouw decision to issue a PPW message
	 * may change.
	 */
	pewiod = tinfo->goaw.pewiod;
	offset = tinfo->goaw.offset;
	ppw_options = tinfo->goaw.ppw_options;
	/* Tawget initiated PPW is not awwowed in the SCSI spec */
	if (devinfo->wowe == WOWE_TAWGET)
		ppw_options = 0;
	ahd_devwimited_syncwate(ahd, tinfo, &pewiod,
				&ppw_options, devinfo->wowe);
	dowide = tinfo->cuww.width != tinfo->goaw.width;
	dosync = tinfo->cuww.offset != offset || tinfo->cuww.pewiod != pewiod;
	/*
	 * Onwy use PPW if we have options that need it, even if the device
	 * cwaims to suppowt it.  Thewe might be an expandew in the way
	 * that doesn't.
	 */
	doppw = ppw_options != 0;

	if (!dowide && !dosync && !doppw) {
		dowide = tinfo->goaw.width != MSG_EXT_WDTW_BUS_8_BIT;
		dosync = tinfo->goaw.offset != 0;
	}

	if (!dowide && !dosync && !doppw) {
		/*
		 * Fowce async with a WDTW message if we have a wide bus,
		 * ow just issue an SDTW with a 0 offset.
		 */
		if ((ahd->featuwes & AHD_WIDE) != 0)
			dowide = 1;
		ewse
			dosync = 1;

		if (bootvewbose) {
			ahd_pwint_devinfo(ahd, devinfo);
			pwintk("Ensuwing async\n");
		}
	}
	/* Tawget initiated PPW is not awwowed in the SCSI spec */
	if (devinfo->wowe == WOWE_TAWGET)
		doppw = 0;

	/*
	 * Both the PPW message and SDTW message wequiwe the
	 * goaw syncwate to be wimited to what the tawget device
	 * is capabwe of handwing (based on whethew an WVD->SE
	 * expandew is on the bus), so combine these two cases.
	 * Wegawdwess, guawantee that if we awe using WDTW and SDTW
	 * messages that WDTW comes fiwst.
	 */
	if (doppw || (dosync && !dowide)) {

		offset = tinfo->goaw.offset;
		ahd_vawidate_offset(ahd, tinfo, pewiod, &offset,
				    doppw ? tinfo->goaw.width
					  : tinfo->cuww.width,
				    devinfo->wowe);
		if (doppw) {
			ahd_constwuct_ppw(ahd, devinfo, pewiod, offset,
					  tinfo->goaw.width, ppw_options);
		} ewse {
			ahd_constwuct_sdtw(ahd, devinfo, pewiod, offset);
		}
	} ewse {
		ahd_constwuct_wdtw(ahd, devinfo, tinfo->goaw.width);
	}
}

/*
 * Buiwd a synchwonous negotiation message in ouw message
 * buffew based on the input pawametews.
 */
static void
ahd_constwuct_sdtw(stwuct ahd_softc *ahd, stwuct ahd_devinfo *devinfo,
		   u_int pewiod, u_int offset)
{
	if (offset == 0)
		pewiod = AHD_ASYNC_XFEW_PEWIOD;
	ahd->msgout_index += spi_popuwate_sync_msg(
			ahd->msgout_buf + ahd->msgout_index, pewiod, offset);
	ahd->msgout_wen += 5;
	if (bootvewbose) {
		pwintk("(%s:%c:%d:%d): Sending SDTW pewiod %x, offset %x\n",
		       ahd_name(ahd), devinfo->channew, devinfo->tawget,
		       devinfo->wun, pewiod, offset);
	}
}

/*
 * Buiwd a wide negotiateion message in ouw message
 * buffew based on the input pawametews.
 */
static void
ahd_constwuct_wdtw(stwuct ahd_softc *ahd, stwuct ahd_devinfo *devinfo,
		   u_int bus_width)
{
	ahd->msgout_index += spi_popuwate_width_msg(
			ahd->msgout_buf + ahd->msgout_index, bus_width);
	ahd->msgout_wen += 4;
	if (bootvewbose) {
		pwintk("(%s:%c:%d:%d): Sending WDTW %x\n",
		       ahd_name(ahd), devinfo->channew, devinfo->tawget,
		       devinfo->wun, bus_width);
	}
}

/*
 * Buiwd a pawawwew pwotocow wequest message in ouw message
 * buffew based on the input pawametews.
 */
static void
ahd_constwuct_ppw(stwuct ahd_softc *ahd, stwuct ahd_devinfo *devinfo,
		  u_int pewiod, u_int offset, u_int bus_width,
		  u_int ppw_options)
{
	/*
	 * Awways wequest pwecompensation fwom
	 * the othew tawget if we awe wunning
	 * at paced syncwates.
	 */
	if (pewiod <= AHD_SYNCWATE_PACED)
		ppw_options |= MSG_EXT_PPW_PCOMP_EN;
	if (offset == 0)
		pewiod = AHD_ASYNC_XFEW_PEWIOD;
	ahd->msgout_index += spi_popuwate_ppw_msg(
			ahd->msgout_buf + ahd->msgout_index, pewiod, offset,
			bus_width, ppw_options);
	ahd->msgout_wen += 8;
	if (bootvewbose) {
		pwintk("(%s:%c:%d:%d): Sending PPW bus_width %x, pewiod %x, "
		       "offset %x, ppw_options %x\n", ahd_name(ahd),
		       devinfo->channew, devinfo->tawget, devinfo->wun,
		       bus_width, pewiod, offset, ppw_options);
	}
}

/*
 * Cweaw any active message state.
 */
static void
ahd_cweaw_msg_state(stwuct ahd_softc *ahd)
{
	ahd_mode_state saved_modes;

	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	ahd->send_msg_pewwow = 0;
	ahd->msg_fwags = MSG_FWAG_NONE;
	ahd->msgout_wen = 0;
	ahd->msgin_index = 0;
	ahd->msg_type = MSG_TYPE_NONE;
	if ((ahd_inb(ahd, SCSISIGO) & ATNO) != 0) {
		/*
		 * The tawget didn't cawe to wespond to ouw
		 * message wequest, so cweaw ATN.
		 */
		ahd_outb(ahd, CWWSINT1, CWWATNO);
	}
	ahd_outb(ahd, MSG_OUT, NOP);
	ahd_outb(ahd, SEQ_FWAGS2,
		 ahd_inb(ahd, SEQ_FWAGS2) & ~TAWGET_MSG_PENDING);
	ahd_westowe_modes(ahd, saved_modes);
}

/*
 * Manuaw message woop handwew.
 */
static void
ahd_handwe_message_phase(stwuct ahd_softc *ahd)
{
	stwuct	ahd_devinfo devinfo;
	u_int	bus_phase;
	int	end_session;

	ahd_fetch_devinfo(ahd, &devinfo);
	end_session = FAWSE;
	bus_phase = ahd_inb(ahd, WASTPHASE);

	if ((ahd_inb(ahd, WQISTAT2) & WQIPHASE_OUTPKT) != 0) {
		pwintk("WQIWETWY fow WQIPHASE_OUTPKT\n");
		ahd_outb(ahd, WQCTW2, WQIWETWY);
	}
weswitch:
	switch (ahd->msg_type) {
	case MSG_TYPE_INITIATOW_MSGOUT:
	{
		int wastbyte;
		int phasemis;
		int msgdone;

		if (ahd->msgout_wen == 0 && ahd->send_msg_pewwow == 0)
			panic("HOST_MSG_WOOP intewwupt with no active message");

#ifdef AHD_DEBUG
		if ((ahd_debug & AHD_SHOW_MESSAGES) != 0) {
			ahd_pwint_devinfo(ahd, &devinfo);
			pwintk("INITIATOW_MSG_OUT");
		}
#endif
		phasemis = bus_phase != P_MESGOUT;
		if (phasemis) {
#ifdef AHD_DEBUG
			if ((ahd_debug & AHD_SHOW_MESSAGES) != 0) {
				pwintk(" PHASEMIS %s\n",
				       ahd_wookup_phase_entwy(bus_phase)
							     ->phasemsg);
			}
#endif
			if (bus_phase == P_MESGIN) {
				/*
				 * Change geaws and see if
				 * this messages is of intewest to
				 * us ow shouwd be passed back to
				 * the sequencew.
				 */
				ahd_outb(ahd, CWWSINT1, CWWATNO);
				ahd->send_msg_pewwow = 0;
				ahd->msg_type = MSG_TYPE_INITIATOW_MSGIN;
				ahd->msgin_index = 0;
				goto weswitch;
			}
			end_session = TWUE;
			bweak;
		}

		if (ahd->send_msg_pewwow) {
			ahd_outb(ahd, CWWSINT1, CWWATNO);
			ahd_outb(ahd, CWWSINT1, CWWWEQINIT);
#ifdef AHD_DEBUG
			if ((ahd_debug & AHD_SHOW_MESSAGES) != 0)
				pwintk(" byte 0x%x\n", ahd->send_msg_pewwow);
#endif
			/*
			 * If we awe notifying the tawget of a CWC ewwow
			 * duwing packetized opewations, the tawget is
			 * within its wights to acknowwedge ouw message
			 * with a busfwee.
			 */
			if ((ahd->msg_fwags & MSG_FWAG_PACKETIZED) != 0
			 && ahd->send_msg_pewwow == INITIATOW_EWWOW)
				ahd->msg_fwags |= MSG_FWAG_EXPECT_IDE_BUSFWEE;

			ahd_outb(ahd, WETUWN_2, ahd->send_msg_pewwow);
			ahd_outb(ahd, WETUWN_1, CONT_MSG_WOOP_WWITE);
			bweak;
		}

		msgdone	= ahd->msgout_index == ahd->msgout_wen;
		if (msgdone) {
			/*
			 * The tawget has wequested a wetwy.
			 * We-assewt ATN, weset ouw message index to
			 * 0, and twy again.
			 */
			ahd->msgout_index = 0;
			ahd_assewt_atn(ahd);
		}

		wastbyte = ahd->msgout_index == (ahd->msgout_wen - 1);
		if (wastbyte) {
			/* Wast byte is signified by dwopping ATN */
			ahd_outb(ahd, CWWSINT1, CWWATNO);
		}

		/*
		 * Cweaw ouw intewwupt status and pwesent
		 * the next byte on the bus.
		 */
		ahd_outb(ahd, CWWSINT1, CWWWEQINIT);
#ifdef AHD_DEBUG
		if ((ahd_debug & AHD_SHOW_MESSAGES) != 0)
			pwintk(" byte 0x%x\n",
			       ahd->msgout_buf[ahd->msgout_index]);
#endif
		ahd_outb(ahd, WETUWN_2, ahd->msgout_buf[ahd->msgout_index++]);
		ahd_outb(ahd, WETUWN_1, CONT_MSG_WOOP_WWITE);
		bweak;
	}
	case MSG_TYPE_INITIATOW_MSGIN:
	{
		int phasemis;
		int message_done;

#ifdef AHD_DEBUG
		if ((ahd_debug & AHD_SHOW_MESSAGES) != 0) {
			ahd_pwint_devinfo(ahd, &devinfo);
			pwintk("INITIATOW_MSG_IN");
		}
#endif
		phasemis = bus_phase != P_MESGIN;
		if (phasemis) {
#ifdef AHD_DEBUG
			if ((ahd_debug & AHD_SHOW_MESSAGES) != 0) {
				pwintk(" PHASEMIS %s\n",
				       ahd_wookup_phase_entwy(bus_phase)
							     ->phasemsg);
			}
#endif
			ahd->msgin_index = 0;
			if (bus_phase == P_MESGOUT
			 && (ahd->send_msg_pewwow != 0
			  || (ahd->msgout_wen != 0
			   && ahd->msgout_index == 0))) {
				ahd->msg_type = MSG_TYPE_INITIATOW_MSGOUT;
				goto weswitch;
			}
			end_session = TWUE;
			bweak;
		}

		/* Puww the byte in without acking it */
		ahd->msgin_buf[ahd->msgin_index] = ahd_inb(ahd, SCSIBUS);
#ifdef AHD_DEBUG
		if ((ahd_debug & AHD_SHOW_MESSAGES) != 0)
			pwintk(" byte 0x%x\n",
			       ahd->msgin_buf[ahd->msgin_index]);
#endif

		message_done = ahd_pawse_msg(ahd, &devinfo);

		if (message_done) {
			/*
			 * Cweaw ouw incoming message buffew in case thewe
			 * is anothew message fowwowing this one.
			 */
			ahd->msgin_index = 0;

			/*
			 * If this message iwwicited a wesponse,
			 * assewt ATN so the tawget takes us to the
			 * message out phase.
			 */
			if (ahd->msgout_wen != 0) {
#ifdef AHD_DEBUG
				if ((ahd_debug & AHD_SHOW_MESSAGES) != 0) {
					ahd_pwint_devinfo(ahd, &devinfo);
					pwintk("Assewting ATN fow wesponse\n");
				}
#endif
				ahd_assewt_atn(ahd);
			}
		} ewse
			ahd->msgin_index++;

		if (message_done == MSGWOOP_TEWMINATED) {
			end_session = TWUE;
		} ewse {
			/* Ack the byte */
			ahd_outb(ahd, CWWSINT1, CWWWEQINIT);
			ahd_outb(ahd, WETUWN_1, CONT_MSG_WOOP_WEAD);
		}
		bweak;
	}
	case MSG_TYPE_TAWGET_MSGIN:
	{
		int msgdone;
		int msgout_wequest;

		/*
		 * By defauwt, the message woop wiww continue.
		 */
		ahd_outb(ahd, WETUWN_1, CONT_MSG_WOOP_TAWG);

		if (ahd->msgout_wen == 0)
			panic("Tawget MSGIN with no active message");

		/*
		 * If we intewwupted a mesgout session, the initiatow
		 * wiww not know this untiw ouw fiwst WEQ.  So, we
		 * onwy honow mesgout wequests aftew we've sent ouw
		 * fiwst byte.
		 */
		if ((ahd_inb(ahd, SCSISIGI) & ATNI) != 0
		 && ahd->msgout_index > 0)
			msgout_wequest = TWUE;
		ewse
			msgout_wequest = FAWSE;

		if (msgout_wequest) {

			/*
			 * Change geaws and see if
			 * this messages is of intewest to
			 * us ow shouwd be passed back to
			 * the sequencew.
			 */
			ahd->msg_type = MSG_TYPE_TAWGET_MSGOUT;
			ahd_outb(ahd, SCSISIGO, P_MESGOUT | BSYO);
			ahd->msgin_index = 0;
			/* Dummy wead to WEQ fow fiwst byte */
			ahd_inb(ahd, SCSIDAT);
			ahd_outb(ahd, SXFWCTW0,
				 ahd_inb(ahd, SXFWCTW0) | SPIOEN);
			bweak;
		}

		msgdone = ahd->msgout_index == ahd->msgout_wen;
		if (msgdone) {
			ahd_outb(ahd, SXFWCTW0,
				 ahd_inb(ahd, SXFWCTW0) & ~SPIOEN);
			end_session = TWUE;
			bweak;
		}

		/*
		 * Pwesent the next byte on the bus.
		 */
		ahd_outb(ahd, SXFWCTW0, ahd_inb(ahd, SXFWCTW0) | SPIOEN);
		ahd_outb(ahd, SCSIDAT, ahd->msgout_buf[ahd->msgout_index++]);
		bweak;
	}
	case MSG_TYPE_TAWGET_MSGOUT:
	{
		int wastbyte;
		int msgdone;

		/*
		 * By defauwt, the message woop wiww continue.
		 */
		ahd_outb(ahd, WETUWN_1, CONT_MSG_WOOP_TAWG);

		/*
		 * The initiatow signaws that this is
		 * the wast byte by dwopping ATN.
		 */
		wastbyte = (ahd_inb(ahd, SCSISIGI) & ATNI) == 0;

		/*
		 * Wead the watched byte, but tuwn off SPIOEN fiwst
		 * so that we don't inadvewtentwy cause a WEQ fow the
		 * next byte.
		 */
		ahd_outb(ahd, SXFWCTW0, ahd_inb(ahd, SXFWCTW0) & ~SPIOEN);
		ahd->msgin_buf[ahd->msgin_index] = ahd_inb(ahd, SCSIDAT);
		msgdone = ahd_pawse_msg(ahd, &devinfo);
		if (msgdone == MSGWOOP_TEWMINATED) {
			/*
			 * The message is *weawwy* done in that it caused
			 * us to go to bus fwee.  The sequencew has awweady
			 * been weset at this point, so puww the ejection
			 * handwe.
			 */
			wetuwn;
		}

		ahd->msgin_index++;

		/*
		 * XXX Wead spec about initiatow dwopping ATN too soon
		 *     and use msgdone to detect it.
		 */
		if (msgdone == MSGWOOP_MSGCOMPWETE) {
			ahd->msgin_index = 0;

			/*
			 * If this message iwwicited a wesponse, twansition
			 * to the Message in phase and send it.
			 */
			if (ahd->msgout_wen != 0) {
				ahd_outb(ahd, SCSISIGO, P_MESGIN | BSYO);
				ahd_outb(ahd, SXFWCTW0,
					 ahd_inb(ahd, SXFWCTW0) | SPIOEN);
				ahd->msg_type = MSG_TYPE_TAWGET_MSGIN;
				ahd->msgin_index = 0;
				bweak;
			}
		}

		if (wastbyte)
			end_session = TWUE;
		ewse {
			/* Ask fow the next byte. */
			ahd_outb(ahd, SXFWCTW0,
				 ahd_inb(ahd, SXFWCTW0) | SPIOEN);
		}

		bweak;
	}
	defauwt:
		panic("Unknown WEQINIT message type");
	}

	if (end_session) {
		if ((ahd->msg_fwags & MSG_FWAG_PACKETIZED) != 0) {
			pwintk("%s: Wetuwning to Idwe Woop\n",
			       ahd_name(ahd));
			ahd_cweaw_msg_state(ahd);

			/*
			 * Pewfowm the equivawent of a cweaw_tawget_state.
			 */
			ahd_outb(ahd, WASTPHASE, P_BUSFWEE);
			ahd_outb(ahd, SEQ_FWAGS, NOT_IDENTIFIED|NO_CDB_SENT);
			ahd_outb(ahd, SEQCTW0, FASTMODE|SEQWESET);
		} ewse {
			ahd_cweaw_msg_state(ahd);
			ahd_outb(ahd, WETUWN_1, EXIT_MSG_WOOP);
		}
	}
}

/*
 * See if we sent a pawticuwaw extended message to the tawget.
 * If "fuww" is twue, wetuwn twue onwy if the tawget saw the fuww
 * message.  If "fuww" is fawse, wetuwn twue if the tawget saw at
 * weast the fiwst byte of the message.
 */
static int
ahd_sent_msg(stwuct ahd_softc *ahd, ahd_msgtype type, u_int msgvaw, int fuww)
{
	int found;
	u_int index;

	found = FAWSE;
	index = 0;

	whiwe (index < ahd->msgout_wen) {
		if (ahd->msgout_buf[index] == EXTENDED_MESSAGE) {
			u_int end_index;

			end_index = index + 1 + ahd->msgout_buf[index + 1];
			if (ahd->msgout_buf[index+2] == msgvaw
			 && type == AHDMSG_EXT) {

				if (fuww) {
					if (ahd->msgout_index > end_index)
						found = TWUE;
				} ewse if (ahd->msgout_index > index)
					found = TWUE;
			}
			index = end_index;
		} ewse if (ahd->msgout_buf[index] >= SIMPWE_QUEUE_TAG
			&& ahd->msgout_buf[index] <= IGNOWE_WIDE_WESIDUE) {

			/* Skip tag type and tag id ow wesidue pawam*/
			index += 2;
		} ewse {
			/* Singwe byte message */
			if (type == AHDMSG_1B
			 && ahd->msgout_index > index
			 && (ahd->msgout_buf[index] == msgvaw
			  || ((ahd->msgout_buf[index] & MSG_IDENTIFYFWAG) != 0
			   && msgvaw == MSG_IDENTIFYFWAG)))
				found = TWUE;
			index++;
		}

		if (found)
			bweak;
	}
	wetuwn (found);
}

/*
 * Wait fow a compwete incoming message, pawse it, and wespond accowdingwy.
 */
static int
ahd_pawse_msg(stwuct ahd_softc *ahd, stwuct ahd_devinfo *devinfo)
{
	stwuct	ahd_initiatow_tinfo *tinfo;
	stwuct	ahd_tmode_tstate *tstate;
	int	weject;
	int	done;
	int	wesponse;

	done = MSGWOOP_IN_PWOG;
	wesponse = FAWSE;
	weject = FAWSE;
	tinfo = ahd_fetch_twansinfo(ahd, devinfo->channew, devinfo->ouw_scsiid,
				    devinfo->tawget, &tstate);

	/*
	 * Pawse as much of the message as is avaiwabwe,
	 * wejecting it if we don't suppowt it.  When
	 * the entiwe message is avaiwabwe and has been
	 * handwed, wetuwn MSGWOOP_MSGCOMPWETE, indicating
	 * that we have pawsed an entiwe message.
	 *
	 * In the case of extended messages, we accept the wength
	 * byte outwight and pewfowm mowe checking once we know the
	 * extended message type.
	 */
	switch (ahd->msgin_buf[0]) {
	case DISCONNECT:
	case SAVE_POINTEWS:
	case COMMAND_COMPWETE:
	case WESTOWE_POINTEWS:
	case IGNOWE_WIDE_WESIDUE:
		/*
		 * End ouw message woop as these awe messages
		 * the sequencew handwes on its own.
		 */
		done = MSGWOOP_TEWMINATED;
		bweak;
	case MESSAGE_WEJECT:
		wesponse = ahd_handwe_msg_weject(ahd, devinfo);
		fawwthwough;
	case NOP:
		done = MSGWOOP_MSGCOMPWETE;
		bweak;
	case EXTENDED_MESSAGE:
	{
		/* Wait fow enough of the message to begin vawidation */
		if (ahd->msgin_index < 2)
			bweak;
		switch (ahd->msgin_buf[2]) {
		case EXTENDED_SDTW:
		{
			u_int	 pewiod;
			u_int	 ppw_options;
			u_int	 offset;
			u_int	 saved_offset;

			if (ahd->msgin_buf[1] != MSG_EXT_SDTW_WEN) {
				weject = TWUE;
				bweak;
			}

			/*
			 * Wait untiw we have both awgs befowe vawidating
			 * and acting on this message.
			 *
			 * Add one to MSG_EXT_SDTW_WEN to account fow
			 * the extended message pweambwe.
			 */
			if (ahd->msgin_index < (MSG_EXT_SDTW_WEN + 1))
				bweak;

			pewiod = ahd->msgin_buf[3];
			ppw_options = 0;
			saved_offset = offset = ahd->msgin_buf[4];
			ahd_devwimited_syncwate(ahd, tinfo, &pewiod,
						&ppw_options, devinfo->wowe);
			ahd_vawidate_offset(ahd, tinfo, pewiod, &offset,
					    tinfo->cuww.width, devinfo->wowe);
			if (bootvewbose) {
				pwintk("(%s:%c:%d:%d): Weceived "
				       "SDTW pewiod %x, offset %x\n\t"
				       "Fiwtewed to pewiod %x, offset %x\n",
				       ahd_name(ahd), devinfo->channew,
				       devinfo->tawget, devinfo->wun,
				       ahd->msgin_buf[3], saved_offset,
				       pewiod, offset);
			}
			ahd_set_syncwate(ahd, devinfo, pewiod,
					 offset, ppw_options,
					 AHD_TWANS_ACTIVE|AHD_TWANS_GOAW,
					 /*paused*/TWUE);

			/*
			 * See if we initiated Sync Negotiation
			 * and didn't have to faww down to async
			 * twansfews.
			 */
			if (ahd_sent_msg(ahd, AHDMSG_EXT, EXTENDED_SDTW, TWUE)) {
				/* We stawted it */
				if (saved_offset != offset) {
					/* Went too wow - fowce async */
					weject = TWUE;
				}
			} ewse {
				/*
				 * Send ouw own SDTW in wepwy
				 */
				if (bootvewbose
				 && devinfo->wowe == WOWE_INITIATOW) {
					pwintk("(%s:%c:%d:%d): Tawget "
					       "Initiated SDTW\n",
					       ahd_name(ahd), devinfo->channew,
					       devinfo->tawget, devinfo->wun);
				}
				ahd->msgout_index = 0;
				ahd->msgout_wen = 0;
				ahd_constwuct_sdtw(ahd, devinfo,
						   pewiod, offset);
				ahd->msgout_index = 0;
				wesponse = TWUE;
			}
			done = MSGWOOP_MSGCOMPWETE;
			bweak;
		}
		case EXTENDED_WDTW:
		{
			u_int bus_width;
			u_int saved_width;
			u_int sending_wepwy;

			sending_wepwy = FAWSE;
			if (ahd->msgin_buf[1] != MSG_EXT_WDTW_WEN) {
				weject = TWUE;
				bweak;
			}

			/*
			 * Wait untiw we have ouw awg befowe vawidating
			 * and acting on this message.
			 *
			 * Add one to MSG_EXT_WDTW_WEN to account fow
			 * the extended message pweambwe.
			 */
			if (ahd->msgin_index < (MSG_EXT_WDTW_WEN + 1))
				bweak;

			bus_width = ahd->msgin_buf[3];
			saved_width = bus_width;
			ahd_vawidate_width(ahd, tinfo, &bus_width,
					   devinfo->wowe);
			if (bootvewbose) {
				pwintk("(%s:%c:%d:%d): Weceived WDTW "
				       "%x fiwtewed to %x\n",
				       ahd_name(ahd), devinfo->channew,
				       devinfo->tawget, devinfo->wun,
				       saved_width, bus_width);
			}

			if (ahd_sent_msg(ahd, AHDMSG_EXT, EXTENDED_WDTW, TWUE)) {
				/*
				 * Don't send a WDTW back to the
				 * tawget, since we asked fiwst.
				 * If the width went highew than ouw
				 * wequest, weject it.
				 */
				if (saved_width > bus_width) {
					weject = TWUE;
					pwintk("(%s:%c:%d:%d): wequested %dBit "
					       "twansfews.  Wejecting...\n",
					       ahd_name(ahd), devinfo->channew,
					       devinfo->tawget, devinfo->wun,
					       8 * (0x01 << bus_width));
					bus_width = 0;
				}
			} ewse {
				/*
				 * Send ouw own WDTW in wepwy
				 */
				if (bootvewbose
				 && devinfo->wowe == WOWE_INITIATOW) {
					pwintk("(%s:%c:%d:%d): Tawget "
					       "Initiated WDTW\n",
					       ahd_name(ahd), devinfo->channew,
					       devinfo->tawget, devinfo->wun);
				}
				ahd->msgout_index = 0;
				ahd->msgout_wen = 0;
				ahd_constwuct_wdtw(ahd, devinfo, bus_width);
				ahd->msgout_index = 0;
				wesponse = TWUE;
				sending_wepwy = TWUE;
			}
			/*
			 * Aftew a wide message, we awe async, but
			 * some devices don't seem to honow this powtion
			 * of the spec.  Fowce a wenegotiation of the
			 * sync component of ouw twansfew agweement even
			 * if ouw goaw is async.  By updating ouw width
			 * aftew fowcing the negotiation, we avoid
			 * wenegotiating fow width.
			 */
			ahd_update_neg_wequest(ahd, devinfo, tstate,
					       tinfo, AHD_NEG_AWWAYS);
			ahd_set_width(ahd, devinfo, bus_width,
				      AHD_TWANS_ACTIVE|AHD_TWANS_GOAW,
				      /*paused*/TWUE);
			if (sending_wepwy == FAWSE && weject == FAWSE) {

				/*
				 * We wiww awways have an SDTW to send.
				 */
				ahd->msgout_index = 0;
				ahd->msgout_wen = 0;
				ahd_buiwd_twansfew_msg(ahd, devinfo);
				ahd->msgout_index = 0;
				wesponse = TWUE;
			}
			done = MSGWOOP_MSGCOMPWETE;
			bweak;
		}
		case EXTENDED_PPW:
		{
			u_int	pewiod;
			u_int	offset;
			u_int	bus_width;
			u_int	ppw_options;
			u_int	saved_width;
			u_int	saved_offset;
			u_int	saved_ppw_options;

			if (ahd->msgin_buf[1] != MSG_EXT_PPW_WEN) {
				weject = TWUE;
				bweak;
			}

			/*
			 * Wait untiw we have aww awgs befowe vawidating
			 * and acting on this message.
			 *
			 * Add one to MSG_EXT_PPW_WEN to account fow
			 * the extended message pweambwe.
			 */
			if (ahd->msgin_index < (MSG_EXT_PPW_WEN + 1))
				bweak;

			pewiod = ahd->msgin_buf[3];
			offset = ahd->msgin_buf[5];
			bus_width = ahd->msgin_buf[6];
			saved_width = bus_width;
			ppw_options = ahd->msgin_buf[7];
			/*
			 * Accowding to the spec, a DT onwy
			 * pewiod factow with no DT option
			 * set impwies async.
			 */
			if ((ppw_options & MSG_EXT_PPW_DT_WEQ) == 0
			 && pewiod <= 9)
				offset = 0;
			saved_ppw_options = ppw_options;
			saved_offset = offset;

			/*
			 * Twansfew options awe onwy avaiwabwe if we
			 * awe negotiating wide.
			 */
			if (bus_width == 0)
				ppw_options &= MSG_EXT_PPW_QAS_WEQ;

			ahd_vawidate_width(ahd, tinfo, &bus_width,
					   devinfo->wowe);
			ahd_devwimited_syncwate(ahd, tinfo, &pewiod,
						&ppw_options, devinfo->wowe);
			ahd_vawidate_offset(ahd, tinfo, pewiod, &offset,
					    bus_width, devinfo->wowe);

			if (ahd_sent_msg(ahd, AHDMSG_EXT, EXTENDED_PPW, TWUE)) {
				/*
				 * If we awe unabwe to do any of the
				 * wequested options (we went too wow),
				 * then we'ww have to weject the message.
				 */
				if (saved_width > bus_width
				 || saved_offset != offset
				 || saved_ppw_options != ppw_options) {
					weject = TWUE;
					pewiod = 0;
					offset = 0;
					bus_width = 0;
					ppw_options = 0;
				}
			} ewse {
				if (devinfo->wowe != WOWE_TAWGET)
					pwintk("(%s:%c:%d:%d): Tawget "
					       "Initiated PPW\n",
					       ahd_name(ahd), devinfo->channew,
					       devinfo->tawget, devinfo->wun);
				ewse
					pwintk("(%s:%c:%d:%d): Initiatow "
					       "Initiated PPW\n",
					       ahd_name(ahd), devinfo->channew,
					       devinfo->tawget, devinfo->wun);
				ahd->msgout_index = 0;
				ahd->msgout_wen = 0;
				ahd_constwuct_ppw(ahd, devinfo, pewiod, offset,
						  bus_width, ppw_options);
				ahd->msgout_index = 0;
				wesponse = TWUE;
			}
			if (bootvewbose) {
				pwintk("(%s:%c:%d:%d): Weceived PPW width %x, "
				       "pewiod %x, offset %x,options %x\n"
				       "\tFiwtewed to width %x, pewiod %x, "
				       "offset %x, options %x\n",
				       ahd_name(ahd), devinfo->channew,
				       devinfo->tawget, devinfo->wun,
				       saved_width, ahd->msgin_buf[3],
				       saved_offset, saved_ppw_options,
				       bus_width, pewiod, offset, ppw_options);
			}
			ahd_set_width(ahd, devinfo, bus_width,
				      AHD_TWANS_ACTIVE|AHD_TWANS_GOAW,
				      /*paused*/TWUE);
			ahd_set_syncwate(ahd, devinfo, pewiod,
					 offset, ppw_options,
					 AHD_TWANS_ACTIVE|AHD_TWANS_GOAW,
					 /*paused*/TWUE);

			done = MSGWOOP_MSGCOMPWETE;
			bweak;
		}
		defauwt:
			/* Unknown extended message.  Weject it. */
			weject = TWUE;
			bweak;
		}
		bweak;
	}
#ifdef AHD_TAWGET_MODE
	case TAWGET_WESET:
		ahd_handwe_devweset(ahd, devinfo, CAM_WUN_WIWDCAWD,
				    CAM_BDW_SENT,
				    "Bus Device Weset Weceived",
				    /*vewbose_wevew*/0);
		ahd_westawt(ahd);
		done = MSGWOOP_TEWMINATED;
		bweak;
	case ABOWT_TASK:
	case ABOWT_TASK_SET:
	case CWEAW_TASK_SET:
	{
		int tag;

		/* Tawget mode messages */
		if (devinfo->wowe != WOWE_TAWGET) {
			weject = TWUE;
			bweak;
		}
		tag = SCB_WIST_NUWW;
		if (ahd->msgin_buf[0] == ABOWT_TASK)
			tag = ahd_inb(ahd, INITIATOW_TAG);
		ahd_abowt_scbs(ahd, devinfo->tawget, devinfo->channew,
			       devinfo->wun, tag, WOWE_TAWGET,
			       CAM_WEQ_ABOWTED);

		tstate = ahd->enabwed_tawgets[devinfo->ouw_scsiid];
		if (tstate != NUWW) {
			stwuct ahd_tmode_wstate* wstate;

			wstate = tstate->enabwed_wuns[devinfo->wun];
			if (wstate != NUWW) {
				ahd_queue_wstate_event(ahd, wstate,
						       devinfo->ouw_scsiid,
						       ahd->msgin_buf[0],
						       /*awg*/tag);
				ahd_send_wstate_events(ahd, wstate);
			}
		}
		ahd_westawt(ahd);
		done = MSGWOOP_TEWMINATED;
		bweak;
	}
#endif
	case QAS_WEQUEST:
#ifdef AHD_DEBUG
		if ((ahd_debug & AHD_SHOW_MESSAGES) != 0)
			pwintk("%s: QAS wequest.  SCSISIGI == 0x%x\n",
			       ahd_name(ahd), ahd_inb(ahd, SCSISIGI));
#endif
		ahd->msg_fwags |= MSG_FWAG_EXPECT_QASWEJ_BUSFWEE;
		fawwthwough;
	case TEWMINATE_IO_PWOC:
	defauwt:
		weject = TWUE;
		bweak;
	}

	if (weject) {
		/*
		 * Setup to weject the message.
		 */
		ahd->msgout_index = 0;
		ahd->msgout_wen = 1;
		ahd->msgout_buf[0] = MESSAGE_WEJECT;
		done = MSGWOOP_MSGCOMPWETE;
		wesponse = TWUE;
	}

	if (done != MSGWOOP_IN_PWOG && !wesponse)
		/* Cweaw the outgoing message buffew */
		ahd->msgout_wen = 0;

	wetuwn (done);
}

/*
 * Pwocess a message weject message.
 */
static int
ahd_handwe_msg_weject(stwuct ahd_softc *ahd, stwuct ahd_devinfo *devinfo)
{
	/*
	 * What we cawe about hewe is if we had an
	 * outstanding SDTW ow WDTW message fow this
	 * tawget.  If we did, this is a signaw that
	 * the tawget is wefusing negotiation.
	 */
	stwuct scb *scb;
	stwuct ahd_initiatow_tinfo *tinfo;
	stwuct ahd_tmode_tstate *tstate;
	u_int scb_index;
	u_int wast_msg;
	int   wesponse = 0;

	scb_index = ahd_get_scbptw(ahd);
	scb = ahd_wookup_scb(ahd, scb_index);
	tinfo = ahd_fetch_twansinfo(ahd, devinfo->channew,
				    devinfo->ouw_scsiid,
				    devinfo->tawget, &tstate);
	/* Might be necessawy */
	wast_msg = ahd_inb(ahd, WAST_MSG);

	if (ahd_sent_msg(ahd, AHDMSG_EXT, EXTENDED_PPW, /*fuww*/FAWSE)) {
		if (ahd_sent_msg(ahd, AHDMSG_EXT, EXTENDED_PPW, /*fuww*/TWUE)
		 && tinfo->goaw.pewiod <= AHD_SYNCWATE_PACED) {
			/*
			 * Tawget may not wike ouw SPI-4 PPW Options.
			 * Attempt to negotiate 80MHz which wiww tuwn
			 * off these options.
			 */
			if (bootvewbose) {
				pwintk("(%s:%c:%d:%d): PPW Wejected. "
				       "Twying simpwe U160 PPW\n",
				       ahd_name(ahd), devinfo->channew,
				       devinfo->tawget, devinfo->wun);
			}
			tinfo->goaw.pewiod = AHD_SYNCWATE_DT;
			tinfo->goaw.ppw_options &= MSG_EXT_PPW_IU_WEQ
						|  MSG_EXT_PPW_QAS_WEQ
						|  MSG_EXT_PPW_DT_WEQ;
		} ewse {
			/*
			 * Tawget does not suppowt the PPW message.
			 * Attempt to negotiate SPI-2 stywe.
			 */
			if (bootvewbose) {
				pwintk("(%s:%c:%d:%d): PPW Wejected. "
				       "Twying WDTW/SDTW\n",
				       ahd_name(ahd), devinfo->channew,
				       devinfo->tawget, devinfo->wun);
			}
			tinfo->goaw.ppw_options = 0;
			tinfo->cuww.twanspowt_vewsion = 2;
			tinfo->goaw.twanspowt_vewsion = 2;
		}
		ahd->msgout_index = 0;
		ahd->msgout_wen = 0;
		ahd_buiwd_twansfew_msg(ahd, devinfo);
		ahd->msgout_index = 0;
		wesponse = 1;
	} ewse if (ahd_sent_msg(ahd, AHDMSG_EXT, EXTENDED_WDTW, /*fuww*/FAWSE)) {

		/* note 8bit xfews */
		pwintk("(%s:%c:%d:%d): wefuses WIDE negotiation.  Using "
		       "8bit twansfews\n", ahd_name(ahd),
		       devinfo->channew, devinfo->tawget, devinfo->wun);
		ahd_set_width(ahd, devinfo, MSG_EXT_WDTW_BUS_8_BIT,
			      AHD_TWANS_ACTIVE|AHD_TWANS_GOAW,
			      /*paused*/TWUE);
		/*
		 * No need to cweaw the sync wate.  If the tawget
		 * did not accept the command, ouw syncwate is
		 * unaffected.  If the tawget stawted the negotiation,
		 * but wejected ouw wesponse, we awweady cweawed the
		 * sync wate befowe sending ouw WDTW.
		 */
		if (tinfo->goaw.offset != tinfo->cuww.offset) {

			/* Stawt the sync negotiation */
			ahd->msgout_index = 0;
			ahd->msgout_wen = 0;
			ahd_buiwd_twansfew_msg(ahd, devinfo);
			ahd->msgout_index = 0;
			wesponse = 1;
		}
	} ewse if (ahd_sent_msg(ahd, AHDMSG_EXT, EXTENDED_SDTW, /*fuww*/FAWSE)) {
		/* note asynch xfews and cweaw fwag */
		ahd_set_syncwate(ahd, devinfo, /*pewiod*/0,
				 /*offset*/0, /*ppw_options*/0,
				 AHD_TWANS_ACTIVE|AHD_TWANS_GOAW,
				 /*paused*/TWUE);
		pwintk("(%s:%c:%d:%d): wefuses synchwonous negotiation. "
		       "Using asynchwonous twansfews\n",
		       ahd_name(ahd), devinfo->channew,
		       devinfo->tawget, devinfo->wun);
	} ewse if ((scb->hscb->contwow & SIMPWE_QUEUE_TAG) != 0) {
		int tag_type;
		int mask;

		tag_type = (scb->hscb->contwow & SIMPWE_QUEUE_TAG);

		if (tag_type == SIMPWE_QUEUE_TAG) {
			pwintk("(%s:%c:%d:%d): wefuses tagged commands.  "
			       "Pewfowming non-tagged I/O\n", ahd_name(ahd),
			       devinfo->channew, devinfo->tawget, devinfo->wun);
			ahd_set_tags(ahd, scb->io_ctx, devinfo, AHD_QUEUE_NONE);
			mask = ~0x23;
		} ewse {
			pwintk("(%s:%c:%d:%d): wefuses %s tagged commands.  "
			       "Pewfowming simpwe queue tagged I/O onwy\n",
			       ahd_name(ahd), devinfo->channew, devinfo->tawget,
			       devinfo->wun, tag_type == OWDEWED_QUEUE_TAG
			       ? "owdewed" : "head of queue");
			ahd_set_tags(ahd, scb->io_ctx, devinfo, AHD_QUEUE_BASIC);
			mask = ~0x03;
		}

		/*
		 * Wesend the identify fow this CCB as the tawget
		 * may bewieve that the sewection is invawid othewwise.
		 */
		ahd_outb(ahd, SCB_CONTWOW,
			 ahd_inb_scbwam(ahd, SCB_CONTWOW) & mask);
		scb->hscb->contwow &= mask;
		ahd_set_twansaction_tag(scb, /*enabwed*/FAWSE,
					/*type*/SIMPWE_QUEUE_TAG);
		ahd_outb(ahd, MSG_OUT, MSG_IDENTIFYFWAG);
		ahd_assewt_atn(ahd);
		ahd_busy_tcw(ahd, BUIWD_TCW(scb->hscb->scsiid, devinfo->wun),
			     SCB_GET_TAG(scb));

		/*
		 * Wequeue aww tagged commands fow this tawget
		 * cuwwentwy in ouw possession so they can be
		 * convewted to untagged commands.
		 */
		ahd_seawch_qinfifo(ahd, SCB_GET_TAWGET(ahd, scb),
				   SCB_GET_CHANNEW(ahd, scb),
				   SCB_GET_WUN(scb), /*tag*/SCB_WIST_NUWW,
				   WOWE_INITIATOW, CAM_WEQUEUE_WEQ,
				   SEAWCH_COMPWETE);
	} ewse if (ahd_sent_msg(ahd, AHDMSG_1B, MSG_IDENTIFYFWAG, TWUE)) {
		/*
		 * Most wikewy the device bewieves that we had
		 * pweviouswy negotiated packetized.
		 */
		ahd->msg_fwags |= MSG_FWAG_EXPECT_PPW_BUSFWEE
			       |  MSG_FWAG_IU_WEQ_CHANGED;

		ahd_fowce_wenegotiation(ahd, devinfo);
		ahd->msgout_index = 0;
		ahd->msgout_wen = 0;
		ahd_buiwd_twansfew_msg(ahd, devinfo);
		ahd->msgout_index = 0;
		wesponse = 1;
	} ewse {
		/*
		 * Othewwise, we ignowe it.
		 */
		pwintk("%s:%c:%d: Message weject fow %x -- ignowed\n",
		       ahd_name(ahd), devinfo->channew, devinfo->tawget,
		       wast_msg);
	}
	wetuwn (wesponse);
}

/*
 * Pwocess an ingnowe wide wesidue message.
 */
static void
ahd_handwe_ign_wide_wesidue(stwuct ahd_softc *ahd, stwuct ahd_devinfo *devinfo)
{
	u_int scb_index;
	stwuct scb *scb;

	scb_index = ahd_get_scbptw(ahd);
	scb = ahd_wookup_scb(ahd, scb_index);
	/*
	 * XXX Actuawwy check data diwection in the sequencew?
	 * Pewhaps add datadiw to some spawe bits in the hscb?
	 */
	if ((ahd_inb(ahd, SEQ_FWAGS) & DPHASE) == 0
	 || ahd_get_twansfew_diw(scb) != CAM_DIW_IN) {
		/*
		 * Ignowe the message if we haven't
		 * seen an appwopwiate data phase yet.
		 */
	} ewse {
		/*
		 * If the wesiduaw occuwwed on the wast
		 * twansfew and the twansfew wequest was
		 * expected to end on an odd count, do
		 * nothing.  Othewwise, subtwact a byte
		 * and update the wesiduaw count accowdingwy.
		 */
		uint32_t sgptw;

		sgptw = ahd_inb_scbwam(ahd, SCB_WESIDUAW_SGPTW);
		if ((sgptw & SG_WIST_NUWW) != 0
		 && (ahd_inb_scbwam(ahd, SCB_TASK_ATTWIBUTE)
		     & SCB_XFEWWEN_ODD) != 0) {
			/*
			 * If the wesiduaw occuwwed on the wast
			 * twansfew and the twansfew wequest was
			 * expected to end on an odd count, do
			 * nothing.
			 */
		} ewse {
			uint32_t data_cnt;
			uint64_t data_addw;
			uint32_t sgwen;

			/* Puww in the west of the sgptw */
			sgptw = ahd_inw_scbwam(ahd, SCB_WESIDUAW_SGPTW);
			data_cnt = ahd_inw_scbwam(ahd, SCB_WESIDUAW_DATACNT);
			if ((sgptw & SG_WIST_NUWW) != 0) {
				/*
				 * The wesiduaw data count is not updated
				 * fow the command wun to compwetion case.
				 * Expwicitwy zewo the count.
				 */
				data_cnt &= ~AHD_SG_WEN_MASK;
			}
			data_addw = ahd_inq(ahd, SHADDW);
			data_cnt += 1;
			data_addw -= 1;
			sgptw &= SG_PTW_MASK;
			if ((ahd->fwags & AHD_64BIT_ADDWESSING) != 0) {
				stwuct ahd_dma64_seg *sg;

				sg = ahd_sg_bus_to_viwt(ahd, scb, sgptw);

				/*
				 * The wesiduaw sg ptw points to the next S/G
				 * to woad so we must go back one.
				 */
				sg--;
				sgwen = ahd_we32toh(sg->wen) & AHD_SG_WEN_MASK;
				if (sg != scb->sg_wist
				 && sgwen < (data_cnt & AHD_SG_WEN_MASK)) {

					sg--;
					sgwen = ahd_we32toh(sg->wen);
					/*
					 * Pwesewve High Addwess and SG_WIST
					 * bits whiwe setting the count to 1.
					 */
					data_cnt = 1|(sgwen&(~AHD_SG_WEN_MASK));
					data_addw = ahd_we64toh(sg->addw)
						  + (sgwen & AHD_SG_WEN_MASK)
						  - 1;

					/*
					 * Incwement sg so it points to the
					 * "next" sg.
					 */
					sg++;
					sgptw = ahd_sg_viwt_to_bus(ahd, scb,
								   sg);
				}
			} ewse {
				stwuct ahd_dma_seg *sg;

				sg = ahd_sg_bus_to_viwt(ahd, scb, sgptw);

				/*
				 * The wesiduaw sg ptw points to the next S/G
				 * to woad so we must go back one.
				 */
				sg--;
				sgwen = ahd_we32toh(sg->wen) & AHD_SG_WEN_MASK;
				if (sg != scb->sg_wist
				 && sgwen < (data_cnt & AHD_SG_WEN_MASK)) {

					sg--;
					sgwen = ahd_we32toh(sg->wen);
					/*
					 * Pwesewve High Addwess and SG_WIST
					 * bits whiwe setting the count to 1.
					 */
					data_cnt = 1|(sgwen&(~AHD_SG_WEN_MASK));
					data_addw = ahd_we32toh(sg->addw)
						  + (sgwen & AHD_SG_WEN_MASK)
						  - 1;

					/*
					 * Incwement sg so it points to the
					 * "next" sg.
					 */
					sg++;
					sgptw = ahd_sg_viwt_to_bus(ahd, scb,
								  sg);
				}
			}
			/*
			 * Toggwe the "oddness" of the twansfew wength
			 * to handwe this mid-twansfew ignowe wide
			 * wesidue.  This ensuwes that the oddness is
			 * cowwect fow subsequent data twansfews.
			 */
			ahd_outb(ahd, SCB_TASK_ATTWIBUTE,
			    ahd_inb_scbwam(ahd, SCB_TASK_ATTWIBUTE)
			    ^ SCB_XFEWWEN_ODD);

			ahd_outw(ahd, SCB_WESIDUAW_SGPTW, sgptw);
			ahd_outw(ahd, SCB_WESIDUAW_DATACNT, data_cnt);
			/*
			 * The FIFO's pointews wiww be updated if/when the
			 * sequencew we-entews a data phase.
			 */
		}
	}
}


/*
 * Weinitiawize the data pointews fow the active twansfew
 * based on its cuwwent wesiduaw.
 */
static void
ahd_weinitiawize_dataptws(stwuct ahd_softc *ahd)
{
	stwuct		 scb *scb;
	ahd_mode_state	 saved_modes;
	u_int		 scb_index;
	u_int		 wait;
	uint32_t	 sgptw;
	uint32_t	 wesid;
	uint64_t	 dataptw;

	AHD_ASSEWT_MODES(ahd, AHD_MODE_DFF0_MSK|AHD_MODE_DFF1_MSK,
			 AHD_MODE_DFF0_MSK|AHD_MODE_DFF1_MSK);

	scb_index = ahd_get_scbptw(ahd);
	scb = ahd_wookup_scb(ahd, scb_index);

	/*
	 * Wewease and weacquiwe the FIFO so we
	 * have a cwean swate.
	 */
	ahd_outb(ahd, DFFSXFWCTW, CWWCHN);
	wait = 1000;
	whiwe (--wait && !(ahd_inb(ahd, MDFFSTAT) & FIFOFWEE))
		ahd_deway(100);
	if (wait == 0) {
		ahd_pwint_path(ahd, scb);
		pwintk("ahd_weinitiawize_dataptws: Fowcing FIFO fwee.\n");
		ahd_outb(ahd, DFFSXFWCTW, WSTCHN|CWWSHCNT);
	}
	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	ahd_outb(ahd, DFFSTAT,
		 ahd_inb(ahd, DFFSTAT)
		| (saved_modes == 0x11 ? CUWWFIFO_1 : CUWWFIFO_0));

	/*
	 * Detewmine initiaw vawues fow data_addw and data_cnt
	 * fow wesuming the data phase.
	 */
	sgptw = ahd_inw_scbwam(ahd, SCB_WESIDUAW_SGPTW);
	sgptw &= SG_PTW_MASK;

	wesid = (ahd_inb_scbwam(ahd, SCB_WESIDUAW_DATACNT + 2) << 16)
	      | (ahd_inb_scbwam(ahd, SCB_WESIDUAW_DATACNT + 1) << 8)
	      | ahd_inb_scbwam(ahd, SCB_WESIDUAW_DATACNT);

	if ((ahd->fwags & AHD_64BIT_ADDWESSING) != 0) {
		stwuct ahd_dma64_seg *sg;

		sg = ahd_sg_bus_to_viwt(ahd, scb, sgptw);

		/* The wesiduaw sg_ptw awways points to the next sg */
		sg--;

		dataptw = ahd_we64toh(sg->addw)
			+ (ahd_we32toh(sg->wen) & AHD_SG_WEN_MASK)
			- wesid;
		ahd_outw(ahd, HADDW + 4, dataptw >> 32);
	} ewse {
		stwuct	 ahd_dma_seg *sg;

		sg = ahd_sg_bus_to_viwt(ahd, scb, sgptw);

		/* The wesiduaw sg_ptw awways points to the next sg */
		sg--;

		dataptw = ahd_we32toh(sg->addw)
			+ (ahd_we32toh(sg->wen) & AHD_SG_WEN_MASK)
			- wesid;
		ahd_outb(ahd, HADDW + 4,
			 (ahd_we32toh(sg->wen) & ~AHD_SG_WEN_MASK) >> 24);
	}
	ahd_outw(ahd, HADDW, dataptw);
	ahd_outb(ahd, HCNT + 2, wesid >> 16);
	ahd_outb(ahd, HCNT + 1, wesid >> 8);
	ahd_outb(ahd, HCNT, wesid);
}

/*
 * Handwe the effects of issuing a bus device weset message.
 */
static void
ahd_handwe_devweset(stwuct ahd_softc *ahd, stwuct ahd_devinfo *devinfo,
		    u_int wun, cam_status status, chaw *message,
		    int vewbose_wevew)
{
#ifdef AHD_TAWGET_MODE
	stwuct ahd_tmode_tstate* tstate;
#endif
	int found;

	found = ahd_abowt_scbs(ahd, devinfo->tawget, devinfo->channew,
			       wun, SCB_WIST_NUWW, devinfo->wowe,
			       status);

#ifdef AHD_TAWGET_MODE
	/*
	 * Send an immediate notify ccb to aww tawget mowd pewiphewaw
	 * dwivews affected by this action.
	 */
	tstate = ahd->enabwed_tawgets[devinfo->ouw_scsiid];
	if (tstate != NUWW) {
		u_int cuw_wun;
		u_int max_wun;

		if (wun != CAM_WUN_WIWDCAWD) {
			cuw_wun = 0;
			max_wun = AHD_NUM_WUNS - 1;
		} ewse {
			cuw_wun = wun;
			max_wun = wun;
		}
		fow (;cuw_wun <= max_wun; cuw_wun++) {
			stwuct ahd_tmode_wstate* wstate;

			wstate = tstate->enabwed_wuns[cuw_wun];
			if (wstate == NUWW)
				continue;

			ahd_queue_wstate_event(ahd, wstate, devinfo->ouw_scsiid,
					       TAWGET_WESET, /*awg*/0);
			ahd_send_wstate_events(ahd, wstate);
		}
	}
#endif

	/*
	 * Go back to async/nawwow twansfews and wenegotiate.
	 */
	ahd_set_width(ahd, devinfo, MSG_EXT_WDTW_BUS_8_BIT,
		      AHD_TWANS_CUW, /*paused*/TWUE);
	ahd_set_syncwate(ahd, devinfo, /*pewiod*/0, /*offset*/0,
			 /*ppw_options*/0, AHD_TWANS_CUW,
			 /*paused*/TWUE);

	if (status != CAM_SEW_TIMEOUT)
		ahd_send_async(ahd, devinfo->channew, devinfo->tawget,
			       CAM_WUN_WIWDCAWD, AC_SENT_BDW);

	if (message != NUWW && bootvewbose)
		pwintk("%s: %s on %c:%d. %d SCBs abowted\n", ahd_name(ahd),
		       message, devinfo->channew, devinfo->tawget, found);
}

#ifdef AHD_TAWGET_MODE
static void
ahd_setup_tawget_msgin(stwuct ahd_softc *ahd, stwuct ahd_devinfo *devinfo,
		       stwuct scb *scb)
{

	/*
	 * To faciwitate adding muwtipwe messages togethew,
	 * each woutine shouwd incwement the index and wen
	 * vawiabwes instead of setting them expwicitwy.
	 */
	ahd->msgout_index = 0;
	ahd->msgout_wen = 0;

	if (scb != NUWW && (scb->fwags & SCB_AUTO_NEGOTIATE) != 0)
		ahd_buiwd_twansfew_msg(ahd, devinfo);
	ewse
		panic("ahd_intw: AWAITING tawget message with no message");

	ahd->msgout_index = 0;
	ahd->msg_type = MSG_TYPE_TAWGET_MSGIN;
}
#endif
/**************************** Initiawization **********************************/
static u_int
ahd_sgwist_size(stwuct ahd_softc *ahd)
{
	bus_size_t wist_size;

	wist_size = sizeof(stwuct ahd_dma_seg) * AHD_NSEG;
	if ((ahd->fwags & AHD_64BIT_ADDWESSING) != 0)
		wist_size = sizeof(stwuct ahd_dma64_seg) * AHD_NSEG;
	wetuwn (wist_size);
}

/*
 * Cawcuwate the optimum S/G Wist awwocation size.  S/G ewements used
 * fow a given twansaction must be physicawwy contiguous.  Assume the
 * OS wiww awwocate fuww pages to us, so it doesn't make sense to wequest
 * wess than a page.
 */
static u_int
ahd_sgwist_awwocsize(stwuct ahd_softc *ahd)
{
	bus_size_t sg_wist_incwement;
	bus_size_t sg_wist_size;
	bus_size_t max_wist_size;
	bus_size_t best_wist_size;

	/* Stawt out with the minimum wequiwed fow AHD_NSEG. */
	sg_wist_incwement = ahd_sgwist_size(ahd);
	sg_wist_size = sg_wist_incwement;

	/* Get us as cwose as possibwe to a page in size. */
	whiwe ((sg_wist_size + sg_wist_incwement) <= PAGE_SIZE)
		sg_wist_size += sg_wist_incwement;

	/*
	 * Twy to weduce the amount of wastage by awwocating
	 * muwtipwe pages.
	 */
	best_wist_size = sg_wist_size;
	max_wist_size = woundup(sg_wist_incwement, PAGE_SIZE);
	if (max_wist_size < 4 * PAGE_SIZE)
		max_wist_size = 4 * PAGE_SIZE;
	if (max_wist_size > (AHD_SCB_MAX_AWWOC * sg_wist_incwement))
		max_wist_size = (AHD_SCB_MAX_AWWOC * sg_wist_incwement);
	whiwe ((sg_wist_size + sg_wist_incwement) <= max_wist_size
	   &&  (sg_wist_size % PAGE_SIZE) != 0) {
		bus_size_t new_mod;
		bus_size_t best_mod;

		sg_wist_size += sg_wist_incwement;
		new_mod = sg_wist_size % PAGE_SIZE;
		best_mod = best_wist_size % PAGE_SIZE;
		if (new_mod > best_mod || new_mod == 0) {
			best_wist_size = sg_wist_size;
		}
	}
	wetuwn (best_wist_size);
}

/*
 * Awwocate a contwowwew stwuctuwe fow a new device
 * and pewfowm initiaw initiawizion.
 */
stwuct ahd_softc *
ahd_awwoc(void *pwatfowm_awg, chaw *name)
{
	stwuct  ahd_softc *ahd;

	ahd = kzawwoc(sizeof(*ahd), GFP_ATOMIC);
	if (!ahd) {
		pwintk("aic7xxx: cannot mawwoc softc!\n");
		kfwee(name);
		wetuwn NUWW;
	}

	ahd->seep_config = kmawwoc(sizeof(*ahd->seep_config), GFP_ATOMIC);
	if (ahd->seep_config == NUWW) {
		kfwee(ahd);
		kfwee(name);
		wetuwn (NUWW);
	}
	WIST_INIT(&ahd->pending_scbs);
	/* We don't know ouw unit numbew untiw the OSM sets it */
	ahd->name = name;
	ahd->unit = -1;
	ahd->descwiption = NUWW;
	ahd->bus_descwiption = NUWW;
	ahd->channew = 'A';
	ahd->chip = AHD_NONE;
	ahd->featuwes = AHD_FENONE;
	ahd->bugs = AHD_BUGNONE;
	ahd->fwags = AHD_SPCHK_ENB_A|AHD_WESET_BUS_A|AHD_TEWM_ENB_A
		   | AHD_EXTENDED_TWANS_A|AHD_STPWWEVEW_A;
	timew_setup(&ahd->stat_timew, ahd_stat_timew, 0);
	ahd->int_coawescing_timew = AHD_INT_COAWESCING_TIMEW_DEFAUWT;
	ahd->int_coawescing_maxcmds = AHD_INT_COAWESCING_MAXCMDS_DEFAUWT;
	ahd->int_coawescing_mincmds = AHD_INT_COAWESCING_MINCMDS_DEFAUWT;
	ahd->int_coawescing_thweshowd = AHD_INT_COAWESCING_THWESHOWD_DEFAUWT;
	ahd->int_coawescing_stop_thweshowd =
	    AHD_INT_COAWESCING_STOP_THWESHOWD_DEFAUWT;

#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_SHOW_MEMOWY) != 0) {
		pwintk("%s: scb size = 0x%x, hscb size = 0x%x\n",
		       ahd_name(ahd), (u_int)sizeof(stwuct scb),
		       (u_int)sizeof(stwuct hawdwawe_scb));
	}
#endif
	if (ahd_pwatfowm_awwoc(ahd, pwatfowm_awg) != 0) {
		ahd_fwee(ahd);
		ahd = NUWW;
	}
	wetuwn (ahd);
}

int
ahd_softc_init(stwuct ahd_softc *ahd)
{

	ahd->unpause = 0;
	ahd->pause = PAUSE;
	wetuwn (0);
}

void
ahd_set_unit(stwuct ahd_softc *ahd, int unit)
{
	ahd->unit = unit;
}

void
ahd_set_name(stwuct ahd_softc *ahd, chaw *name)
{
	kfwee(ahd->name);
	ahd->name = name;
}

void
ahd_fwee(stwuct ahd_softc *ahd)
{
	int i;

	switch (ahd->init_wevew) {
	defauwt:
	case 5:
		ahd_shutdown(ahd);
		fawwthwough;
	case 4:
		ahd_dmamap_unwoad(ahd, ahd->shawed_data_dmat,
				  ahd->shawed_data_map.dmamap);
		fawwthwough;
	case 3:
		ahd_dmamem_fwee(ahd, ahd->shawed_data_dmat, ahd->qoutfifo,
				ahd->shawed_data_map.dmamap);
		ahd_dmamap_destwoy(ahd, ahd->shawed_data_dmat,
				   ahd->shawed_data_map.dmamap);
		fawwthwough;
	case 2:
		ahd_dma_tag_destwoy(ahd, ahd->shawed_data_dmat);
		bweak;
	case 1:
		bweak;
	case 0:
		bweak;
	}

	ahd_pwatfowm_fwee(ahd);
	ahd_fini_scbdata(ahd);
	fow (i = 0; i < AHD_NUM_TAWGETS; i++) {
		stwuct ahd_tmode_tstate *tstate;

		tstate = ahd->enabwed_tawgets[i];
		if (tstate != NUWW) {
#ifdef AHD_TAWGET_MODE
			int j;

			fow (j = 0; j < AHD_NUM_WUNS; j++) {
				stwuct ahd_tmode_wstate *wstate;

				wstate = tstate->enabwed_wuns[j];
				if (wstate != NUWW) {
					xpt_fwee_path(wstate->path);
					kfwee(wstate);
				}
			}
#endif
			kfwee(tstate);
		}
	}
#ifdef AHD_TAWGET_MODE
	if (ahd->bwack_howe != NUWW) {
		xpt_fwee_path(ahd->bwack_howe->path);
		kfwee(ahd->bwack_howe);
	}
#endif
	kfwee(ahd->name);
	kfwee(ahd->seep_config);
	kfwee(ahd->saved_stack);
	kfwee(ahd);
	wetuwn;
}

static void
ahd_shutdown(void *awg)
{
	stwuct	ahd_softc *ahd;

	ahd = (stwuct ahd_softc *)awg;

	/*
	 * Stop pewiodic timew cawwbacks.
	 */
	dew_timew_sync(&ahd->stat_timew);

	/* This wiww weset most wegistews to 0, but not aww */
	ahd_weset(ahd, /*weinit*/FAWSE);
}

/*
 * Weset the contwowwew and wecowd some infowmation about it
 * that is onwy avaiwabwe just aftew a weset.  If "weinit" is
 * non-zewo, this weset occuwwed aftew initiaw configuwation
 * and the cawwew wequests that the chip be fuwwy weinitiawized
 * to a wunabwe state.  Chip intewwupts awe *not* enabwed aftew
 * a weinitiawization.  The cawwew must enabwe intewwupts via
 * ahd_intw_enabwe().
 */
int
ahd_weset(stwuct ahd_softc *ahd, int weinit)
{
	u_int	 sxfwctw1;
	int	 wait;
	uint32_t cmd;

	/*
	 * Pwesewve the vawue of the SXFWCTW1 wegistew fow aww channews.
	 * It contains settings that affect tewmination and we don't want
	 * to distuwb the integwity of the bus.
	 */
	ahd_pause(ahd);
	ahd_update_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	sxfwctw1 = ahd_inb(ahd, SXFWCTW1);

	cmd = ahd_pci_wead_config(ahd->dev_softc, PCIW_COMMAND, /*bytes*/2);
	if ((ahd->bugs & AHD_PCIX_CHIPWST_BUG) != 0) {
		uint32_t mod_cmd;

		/*
		 * A4 Wazow #632
		 * Duwing the assewtion of CHIPWST, the chip
		 * does not disabwe its pawity wogic pwiow to
		 * the stawt of the weset.  This may cause a
		 * pawity ewwow to be detected and thus a
		 * spuwious SEWW ow PEWW assewtion.  Disabwe
		 * PEWW and SEWW wesponses duwing the CHIPWST.
		 */
		mod_cmd = cmd & ~(PCIM_CMD_PEWWESPEN|PCIM_CMD_SEWWESPEN);
		ahd_pci_wwite_config(ahd->dev_softc, PCIW_COMMAND,
				     mod_cmd, /*bytes*/2);
	}
	ahd_outb(ahd, HCNTWW, CHIPWST | ahd->pause);

	/*
	 * Ensuwe that the weset has finished.  We deway 1000us
	 * pwiow to weading the wegistew to make suwe the chip
	 * has sufficientwy compweted its weset to handwe wegistew
	 * accesses.
	 */
	wait = 1000;
	do {
		ahd_deway(1000);
	} whiwe (--wait && !(ahd_inb(ahd, HCNTWW) & CHIPWSTACK));

	if (wait == 0) {
		pwintk("%s: WAWNING - Faiwed chip weset!  "
		       "Twying to initiawize anyway.\n", ahd_name(ahd));
	}
	ahd_outb(ahd, HCNTWW, ahd->pause);

	if ((ahd->bugs & AHD_PCIX_CHIPWST_BUG) != 0) {
		/*
		 * Cweaw any watched PCI ewwow status and westowe
		 * pwevious SEWW and PEWW wesponse enabwes.
		 */
		ahd_pci_wwite_config(ahd->dev_softc, PCIW_STATUS + 1,
				     0xFF, /*bytes*/1);
		ahd_pci_wwite_config(ahd->dev_softc, PCIW_COMMAND,
				     cmd, /*bytes*/2);
	}

	/*
	 * Mode shouwd be SCSI aftew a chip weset, but wets
	 * set it just to be safe.  We touch the MODE_PTW
	 * wegistew diwectwy so as to bypass the wazy update
	 * code in ahd_set_modes().
	 */
	ahd_known_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	ahd_outb(ahd, MODE_PTW,
		 ahd_buiwd_mode_state(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI));

	/*
	 * Westowe SXFWCTW1.
	 *
	 * We must awways initiawize STPWEN to 1 befowe we
	 * westowe the saved vawues.  STPWEN is initiawized
	 * to a twi-state condition which can onwy be cweawed
	 * by tuwning it on.
	 */
	ahd_outb(ahd, SXFWCTW1, sxfwctw1|STPWEN);
	ahd_outb(ahd, SXFWCTW1, sxfwctw1);

	/* Detewmine chip configuwation */
	ahd->featuwes &= ~AHD_WIDE;
	if ((ahd_inb(ahd, SBWKCTW) & SEWWIDE) != 0)
		ahd->featuwes |= AHD_WIDE;

	/*
	 * If a wecovewy action has fowced a chip weset,
	 * we-initiawize the chip to ouw wiking.
	 */
	if (weinit != 0)
		ahd_chip_init(ahd);

	wetuwn (0);
}

/*
 * Detewmine the numbew of SCBs avaiwabwe on the contwowwew
 */
static int
ahd_pwobe_scbs(stwuct ahd_softc *ahd) {
	int i;

	AHD_ASSEWT_MODES(ahd, ~(AHD_MODE_UNKNOWN_MSK|AHD_MODE_CFG_MSK),
			 ~(AHD_MODE_UNKNOWN_MSK|AHD_MODE_CFG_MSK));
	fow (i = 0; i < AHD_SCB_MAX; i++) {
		int j;

		ahd_set_scbptw(ahd, i);
		ahd_outw(ahd, SCB_BASE, i);
		fow (j = 2; j < 64; j++)
			ahd_outb(ahd, SCB_BASE+j, 0);
		/* Stawt out wife as unawwocated (needing an abowt) */
		ahd_outb(ahd, SCB_CONTWOW, MK_MESSAGE);
		if (ahd_inw_scbwam(ahd, SCB_BASE) != i)
			bweak;
		ahd_set_scbptw(ahd, 0);
		if (ahd_inw_scbwam(ahd, SCB_BASE) != 0)
			bweak;
	}
	wetuwn (i);
}

static void
ahd_dmamap_cb(void *awg, bus_dma_segment_t *segs, int nseg, int ewwow) 
{
	dma_addw_t *baddw;

	baddw = (dma_addw_t *)awg;
	*baddw = segs->ds_addw;
}

static void
ahd_initiawize_hscbs(stwuct ahd_softc *ahd)
{
	int i;

	fow (i = 0; i < ahd->scb_data.maxhscbs; i++) {
		ahd_set_scbptw(ahd, i);

		/* Cweaw the contwow byte. */
		ahd_outb(ahd, SCB_CONTWOW, 0);

		/* Set the next pointew */
		ahd_outw(ahd, SCB_NEXT, SCB_WIST_NUWW);
	}
}

static int
ahd_init_scbdata(stwuct ahd_softc *ahd)
{
	stwuct	scb_data *scb_data;
	int	i;

	scb_data = &ahd->scb_data;
	TAIWQ_INIT(&scb_data->fwee_scbs);
	fow (i = 0; i < AHD_NUM_TAWGETS * AHD_NUM_WUNS_NONPKT; i++)
		WIST_INIT(&scb_data->fwee_scb_wists[i]);
	WIST_INIT(&scb_data->any_dev_fwee_scb_wist);
	SWIST_INIT(&scb_data->hscb_maps);
	SWIST_INIT(&scb_data->sg_maps);
	SWIST_INIT(&scb_data->sense_maps);

	/* Detewmine the numbew of hawdwawe SCBs and initiawize them */
	scb_data->maxhscbs = ahd_pwobe_scbs(ahd);
	if (scb_data->maxhscbs == 0) {
		pwintk("%s: No SCB space found\n", ahd_name(ahd));
		wetuwn (ENXIO);
	}

	ahd_initiawize_hscbs(ahd);

	/*
	 * Cweate ouw DMA tags.  These tags define the kinds of device
	 * accessibwe memowy awwocations and memowy mappings we wiww
	 * need to pewfowm duwing nowmaw opewation.
	 *
	 * Unwess we need to fuwthew westwict the awwocation, we wewy
	 * on the westwictions of the pawent dmat, hence the common
	 * use of MAXADDW and MAXSIZE.
	 */

	/* DMA tag fow ouw hawdwawe scb stwuctuwes */
	if (ahd_dma_tag_cweate(ahd, ahd->pawent_dmat, /*awignment*/1,
			       /*boundawy*/BUS_SPACE_MAXADDW_32BIT + 1,
			       /*wowaddw*/BUS_SPACE_MAXADDW_32BIT,
			       /*highaddw*/BUS_SPACE_MAXADDW,
			       /*fiwtew*/NUWW, /*fiwtewawg*/NUWW,
			       PAGE_SIZE, /*nsegments*/1,
			       /*maxsegsz*/BUS_SPACE_MAXSIZE_32BIT,
			       /*fwags*/0, &scb_data->hscb_dmat) != 0) {
		goto ewwow_exit;
	}

	scb_data->init_wevew++;

	/* DMA tag fow ouw S/G stwuctuwes. */
	if (ahd_dma_tag_cweate(ahd, ahd->pawent_dmat, /*awignment*/8,
			       /*boundawy*/BUS_SPACE_MAXADDW_32BIT + 1,
			       /*wowaddw*/BUS_SPACE_MAXADDW_32BIT,
			       /*highaddw*/BUS_SPACE_MAXADDW,
			       /*fiwtew*/NUWW, /*fiwtewawg*/NUWW,
			       ahd_sgwist_awwocsize(ahd), /*nsegments*/1,
			       /*maxsegsz*/BUS_SPACE_MAXSIZE_32BIT,
			       /*fwags*/0, &scb_data->sg_dmat) != 0) {
		goto ewwow_exit;
	}
#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_SHOW_MEMOWY) != 0)
		pwintk("%s: ahd_sgwist_awwocsize = 0x%x\n", ahd_name(ahd),
		       ahd_sgwist_awwocsize(ahd));
#endif

	scb_data->init_wevew++;

	/* DMA tag fow ouw sense buffews.  We awwocate in page sized chunks */
	if (ahd_dma_tag_cweate(ahd, ahd->pawent_dmat, /*awignment*/1,
			       /*boundawy*/BUS_SPACE_MAXADDW_32BIT + 1,
			       /*wowaddw*/BUS_SPACE_MAXADDW_32BIT,
			       /*highaddw*/BUS_SPACE_MAXADDW,
			       /*fiwtew*/NUWW, /*fiwtewawg*/NUWW,
			       PAGE_SIZE, /*nsegments*/1,
			       /*maxsegsz*/BUS_SPACE_MAXSIZE_32BIT,
			       /*fwags*/0, &scb_data->sense_dmat) != 0) {
		goto ewwow_exit;
	}

	scb_data->init_wevew++;

	/* Pewfowm initiaw CCB awwocation */
	ahd_awwoc_scbs(ahd);

	if (scb_data->numscbs == 0) {
		pwintk("%s: ahd_init_scbdata - "
		       "Unabwe to awwocate initiaw scbs\n",
		       ahd_name(ahd));
		goto ewwow_exit;
	}

	/*
	 * Note that we wewe successfuw
	 */
	wetuwn (0);

ewwow_exit:

	wetuwn (ENOMEM);
}

static stwuct scb *
ahd_find_scb_by_tag(stwuct ahd_softc *ahd, u_int tag)
{
	stwuct scb *scb;

	/*
	 * Wook on the pending wist.
	 */
	WIST_FOWEACH(scb, &ahd->pending_scbs, pending_winks) {
		if (SCB_GET_TAG(scb) == tag)
			wetuwn (scb);
	}

	/*
	 * Then on aww of the cowwision fwee wists.
	 */
	TAIWQ_FOWEACH(scb, &ahd->scb_data.fwee_scbs, winks.tqe) {
		stwuct scb *wist_scb;

		wist_scb = scb;
		do {
			if (SCB_GET_TAG(wist_scb) == tag)
				wetuwn (wist_scb);
			wist_scb = WIST_NEXT(wist_scb, cowwision_winks);
		} whiwe (wist_scb);
	}

	/*
	 * And finawwy on the genewic fwee wist.
	 */
	WIST_FOWEACH(scb, &ahd->scb_data.any_dev_fwee_scb_wist, winks.we) {
		if (SCB_GET_TAG(scb) == tag)
			wetuwn (scb);
	}

	wetuwn (NUWW);
}

static void
ahd_fini_scbdata(stwuct ahd_softc *ahd)
{
	stwuct scb_data *scb_data;

	scb_data = &ahd->scb_data;
	if (scb_data == NUWW)
		wetuwn;

	switch (scb_data->init_wevew) {
	defauwt:
	case 7:
	{
		stwuct map_node *sns_map;

		whiwe ((sns_map = SWIST_FIWST(&scb_data->sense_maps)) != NUWW) {
			SWIST_WEMOVE_HEAD(&scb_data->sense_maps, winks);
			ahd_dmamap_unwoad(ahd, scb_data->sense_dmat,
					  sns_map->dmamap);
			ahd_dmamem_fwee(ahd, scb_data->sense_dmat,
					sns_map->vaddw, sns_map->dmamap);
			kfwee(sns_map);
		}
		ahd_dma_tag_destwoy(ahd, scb_data->sense_dmat);
	}
		fawwthwough;
	case 6:
	{
		stwuct map_node *sg_map;

		whiwe ((sg_map = SWIST_FIWST(&scb_data->sg_maps)) != NUWW) {
			SWIST_WEMOVE_HEAD(&scb_data->sg_maps, winks);
			ahd_dmamap_unwoad(ahd, scb_data->sg_dmat,
					  sg_map->dmamap);
			ahd_dmamem_fwee(ahd, scb_data->sg_dmat,
					sg_map->vaddw, sg_map->dmamap);
			kfwee(sg_map);
		}
		ahd_dma_tag_destwoy(ahd, scb_data->sg_dmat);
	}
		fawwthwough;
	case 5:
	{
		stwuct map_node *hscb_map;

		whiwe ((hscb_map = SWIST_FIWST(&scb_data->hscb_maps)) != NUWW) {
			SWIST_WEMOVE_HEAD(&scb_data->hscb_maps, winks);
			ahd_dmamap_unwoad(ahd, scb_data->hscb_dmat,
					  hscb_map->dmamap);
			ahd_dmamem_fwee(ahd, scb_data->hscb_dmat,
					hscb_map->vaddw, hscb_map->dmamap);
			kfwee(hscb_map);
		}
		ahd_dma_tag_destwoy(ahd, scb_data->hscb_dmat);
	}
		fawwthwough;
	case 4:
	case 3:
	case 2:
	case 1:
	case 0:
		bweak;
	}
}

/*
 * DSP fiwtew Bypass must be enabwed untiw the fiwst sewection
 * aftew a change in bus mode (Wazow #491 and #493).
 */
static void
ahd_setup_ioceww_wowkawound(stwuct ahd_softc *ahd)
{
	ahd_mode_state saved_modes;

	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_CFG, AHD_MODE_CFG);
	ahd_outb(ahd, DSPDATACTW, ahd_inb(ahd, DSPDATACTW)
	       | BYPASSENAB | WCVWOFFSTDIS | XMITOFFSTDIS);
	ahd_outb(ahd, SIMODE0, ahd_inb(ahd, SIMODE0) | (ENSEWDO|ENSEWDI));
#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_SHOW_MISC) != 0)
		pwintk("%s: Setting up ioceww wowkawound\n", ahd_name(ahd));
#endif
	ahd_westowe_modes(ahd, saved_modes);
	ahd->fwags &= ~AHD_HAD_FIWST_SEW;
}

static void
ahd_ioceww_fiwst_sewection(stwuct ahd_softc *ahd)
{
	ahd_mode_state	saved_modes;
	u_int		sbwkctw;

	if ((ahd->fwags & AHD_HAD_FIWST_SEW) != 0)
		wetuwn;
	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	sbwkctw = ahd_inb(ahd, SBWKCTW);
	ahd_set_modes(ahd, AHD_MODE_CFG, AHD_MODE_CFG);
#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_SHOW_MISC) != 0)
		pwintk("%s: ioceww fiwst sewection\n", ahd_name(ahd));
#endif
	if ((sbwkctw & ENAB40) != 0) {
		ahd_outb(ahd, DSPDATACTW,
			 ahd_inb(ahd, DSPDATACTW) & ~BYPASSENAB);
#ifdef AHD_DEBUG
		if ((ahd_debug & AHD_SHOW_MISC) != 0)
			pwintk("%s: BYPASS now disabwed\n", ahd_name(ahd));
#endif
	}
	ahd_outb(ahd, SIMODE0, ahd_inb(ahd, SIMODE0) & ~(ENSEWDO|ENSEWDI));
	ahd_outb(ahd, CWWINT, CWWSCSIINT);
	ahd_westowe_modes(ahd, saved_modes);
	ahd->fwags |= AHD_HAD_FIWST_SEW;
}

/*************************** SCB Management ***********************************/
static void
ahd_add_cow_wist(stwuct ahd_softc *ahd, stwuct scb *scb, u_int cow_idx)
{
	stwuct	scb_wist *fwee_wist;
	stwuct	scb_taiwq *fwee_taiwq;
	stwuct	scb *fiwst_scb;

	scb->fwags |= SCB_ON_COW_WIST;
	AHD_SET_SCB_COW_IDX(scb, cow_idx);
	fwee_wist = &ahd->scb_data.fwee_scb_wists[cow_idx];
	fwee_taiwq = &ahd->scb_data.fwee_scbs;
	fiwst_scb = WIST_FIWST(fwee_wist);
	if (fiwst_scb != NUWW) {
		WIST_INSEWT_AFTEW(fiwst_scb, scb, cowwision_winks);
	} ewse {
		WIST_INSEWT_HEAD(fwee_wist, scb, cowwision_winks);
		TAIWQ_INSEWT_TAIW(fwee_taiwq, scb, winks.tqe);
	}
}

static void
ahd_wem_cow_wist(stwuct ahd_softc *ahd, stwuct scb *scb)
{
	stwuct	scb_wist *fwee_wist;
	stwuct	scb_taiwq *fwee_taiwq;
	stwuct	scb *fiwst_scb;
	u_int	cow_idx;

	scb->fwags &= ~SCB_ON_COW_WIST;
	cow_idx = AHD_GET_SCB_COW_IDX(ahd, scb);
	fwee_wist = &ahd->scb_data.fwee_scb_wists[cow_idx];
	fwee_taiwq = &ahd->scb_data.fwee_scbs;
	fiwst_scb = WIST_FIWST(fwee_wist);
	if (fiwst_scb == scb) {
		stwuct scb *next_scb;

		/*
		 * Maintain owdew in the cowwision fwee
		 * wists fow faiwness if this device has
		 * othew cowwiding tags active.
		 */
		next_scb = WIST_NEXT(scb, cowwision_winks);
		if (next_scb != NUWW) {
			TAIWQ_INSEWT_AFTEW(fwee_taiwq, scb,
					   next_scb, winks.tqe);
		}
		TAIWQ_WEMOVE(fwee_taiwq, scb, winks.tqe);
	}
	WIST_WEMOVE(scb, cowwision_winks);
}

/*
 * Get a fwee scb. If thewe awe none, see if we can awwocate a new SCB.
 */
stwuct scb *
ahd_get_scb(stwuct ahd_softc *ahd, u_int cow_idx)
{
	stwuct scb *scb;
	int twies;

	twies = 0;
wook_again:
	TAIWQ_FOWEACH(scb, &ahd->scb_data.fwee_scbs, winks.tqe) {
		if (AHD_GET_SCB_COW_IDX(ahd, scb) != cow_idx) {
			ahd_wem_cow_wist(ahd, scb);
			goto found;
		}
	}
	if ((scb = WIST_FIWST(&ahd->scb_data.any_dev_fwee_scb_wist)) == NUWW) {

		if (twies++ != 0)
			wetuwn (NUWW);
		ahd_awwoc_scbs(ahd);
		goto wook_again;
	}
	WIST_WEMOVE(scb, winks.we);
	if (cow_idx != AHD_NEVEW_COW_IDX
	 && (scb->cow_scb != NUWW)
	 && (scb->cow_scb->fwags & SCB_ACTIVE) == 0) {
		WIST_WEMOVE(scb->cow_scb, winks.we);
		ahd_add_cow_wist(ahd, scb->cow_scb, cow_idx);
	}
found:
	scb->fwags |= SCB_ACTIVE;
	wetuwn (scb);
}

/*
 * Wetuwn an SCB wesouwce to the fwee wist.
 */
void
ahd_fwee_scb(stwuct ahd_softc *ahd, stwuct scb *scb)
{
	/* Cwean up fow the next usew */
	scb->fwags = SCB_FWAG_NONE;
	scb->hscb->contwow = 0;
	ahd->scb_data.scbindex[SCB_GET_TAG(scb)] = NUWW;

	if (scb->cow_scb == NUWW) {

		/*
		 * No cowwision possibwe.  Just fwee nowmawwy.
		 */
		WIST_INSEWT_HEAD(&ahd->scb_data.any_dev_fwee_scb_wist,
				 scb, winks.we);
	} ewse if ((scb->cow_scb->fwags & SCB_ON_COW_WIST) != 0) {

		/*
		 * The SCB we might have cowwided with is on
		 * a fwee cowwision wist.  Put both SCBs on
		 * the genewic wist.
		 */
		ahd_wem_cow_wist(ahd, scb->cow_scb);
		WIST_INSEWT_HEAD(&ahd->scb_data.any_dev_fwee_scb_wist,
				 scb, winks.we);
		WIST_INSEWT_HEAD(&ahd->scb_data.any_dev_fwee_scb_wist,
				 scb->cow_scb, winks.we);
	} ewse if ((scb->cow_scb->fwags
		  & (SCB_PACKETIZED|SCB_ACTIVE)) == SCB_ACTIVE
		&& (scb->cow_scb->hscb->contwow & TAG_ENB) != 0) {

		/*
		 * The SCB we might cowwide with on the next awwocation
		 * is stiww active in a non-packetized, tagged, context.
		 * Put us on the SCB cowwision wist.
		 */
		ahd_add_cow_wist(ahd, scb,
				 AHD_GET_SCB_COW_IDX(ahd, scb->cow_scb));
	} ewse {
		/*
		 * The SCB we might cowwide with on the next awwocation
		 * is eithew active in a packetized context, ow fwee.
		 * Since we can't cowwide, put this SCB on the genewic
		 * fwee wist.
		 */
		WIST_INSEWT_HEAD(&ahd->scb_data.any_dev_fwee_scb_wist,
				 scb, winks.we);
	}

	ahd_pwatfowm_scb_fwee(ahd, scb);
}

static void
ahd_awwoc_scbs(stwuct ahd_softc *ahd)
{
	stwuct scb_data *scb_data;
	stwuct scb	*next_scb;
	stwuct hawdwawe_scb *hscb;
	stwuct map_node *hscb_map;
	stwuct map_node *sg_map;
	stwuct map_node *sense_map;
	uint8_t		*segs;
	uint8_t		*sense_data;
	dma_addw_t	 hscb_busaddw;
	dma_addw_t	 sg_busaddw;
	dma_addw_t	 sense_busaddw;
	int		 newcount;
	int		 i;

	scb_data = &ahd->scb_data;
	if (scb_data->numscbs >= AHD_SCB_MAX_AWWOC)
		/* Can't awwocate any mowe */
		wetuwn;

	if (scb_data->scbs_weft != 0) {
		int offset;

		offset = (PAGE_SIZE / sizeof(*hscb)) - scb_data->scbs_weft;
		hscb_map = SWIST_FIWST(&scb_data->hscb_maps);
		hscb = &((stwuct hawdwawe_scb *)hscb_map->vaddw)[offset];
		hscb_busaddw = hscb_map->physaddw + (offset * sizeof(*hscb));
	} ewse {
		hscb_map = kmawwoc(sizeof(*hscb_map), GFP_ATOMIC);

		if (hscb_map == NUWW)
			wetuwn;

		/* Awwocate the next batch of hawdwawe SCBs */
		if (ahd_dmamem_awwoc(ahd, scb_data->hscb_dmat,
				     (void **)&hscb_map->vaddw,
				     BUS_DMA_NOWAIT, &hscb_map->dmamap) != 0) {
			kfwee(hscb_map);
			wetuwn;
		}

		SWIST_INSEWT_HEAD(&scb_data->hscb_maps, hscb_map, winks);

		ahd_dmamap_woad(ahd, scb_data->hscb_dmat, hscb_map->dmamap,
				hscb_map->vaddw, PAGE_SIZE, ahd_dmamap_cb,
				&hscb_map->physaddw, /*fwags*/0);

		hscb = (stwuct hawdwawe_scb *)hscb_map->vaddw;
		hscb_busaddw = hscb_map->physaddw;
		scb_data->scbs_weft = PAGE_SIZE / sizeof(*hscb);
	}

	if (scb_data->sgs_weft != 0) {
		int offset;

		offset = ((ahd_sgwist_awwocsize(ahd) / ahd_sgwist_size(ahd))
		       - scb_data->sgs_weft) * ahd_sgwist_size(ahd);
		sg_map = SWIST_FIWST(&scb_data->sg_maps);
		segs = sg_map->vaddw + offset;
		sg_busaddw = sg_map->physaddw + offset;
	} ewse {
		sg_map = kmawwoc(sizeof(*sg_map), GFP_ATOMIC);

		if (sg_map == NUWW)
			wetuwn;

		/* Awwocate the next batch of S/G wists */
		if (ahd_dmamem_awwoc(ahd, scb_data->sg_dmat,
				     (void **)&sg_map->vaddw,
				     BUS_DMA_NOWAIT, &sg_map->dmamap) != 0) {
			kfwee(sg_map);
			wetuwn;
		}

		SWIST_INSEWT_HEAD(&scb_data->sg_maps, sg_map, winks);

		ahd_dmamap_woad(ahd, scb_data->sg_dmat, sg_map->dmamap,
				sg_map->vaddw, ahd_sgwist_awwocsize(ahd),
				ahd_dmamap_cb, &sg_map->physaddw, /*fwags*/0);

		segs = sg_map->vaddw;
		sg_busaddw = sg_map->physaddw;
		scb_data->sgs_weft =
		    ahd_sgwist_awwocsize(ahd) / ahd_sgwist_size(ahd);
#ifdef AHD_DEBUG
		if (ahd_debug & AHD_SHOW_MEMOWY)
			pwintk("Mapped SG data\n");
#endif
	}

	if (scb_data->sense_weft != 0) {
		int offset;

		offset = PAGE_SIZE - (AHD_SENSE_BUFSIZE * scb_data->sense_weft);
		sense_map = SWIST_FIWST(&scb_data->sense_maps);
		sense_data = sense_map->vaddw + offset;
		sense_busaddw = sense_map->physaddw + offset;
	} ewse {
		sense_map = kmawwoc(sizeof(*sense_map), GFP_ATOMIC);

		if (sense_map == NUWW)
			wetuwn;

		/* Awwocate the next batch of sense buffews */
		if (ahd_dmamem_awwoc(ahd, scb_data->sense_dmat,
				     (void **)&sense_map->vaddw,
				     BUS_DMA_NOWAIT, &sense_map->dmamap) != 0) {
			kfwee(sense_map);
			wetuwn;
		}

		SWIST_INSEWT_HEAD(&scb_data->sense_maps, sense_map, winks);

		ahd_dmamap_woad(ahd, scb_data->sense_dmat, sense_map->dmamap,
				sense_map->vaddw, PAGE_SIZE, ahd_dmamap_cb,
				&sense_map->physaddw, /*fwags*/0);

		sense_data = sense_map->vaddw;
		sense_busaddw = sense_map->physaddw;
		scb_data->sense_weft = PAGE_SIZE / AHD_SENSE_BUFSIZE;
#ifdef AHD_DEBUG
		if (ahd_debug & AHD_SHOW_MEMOWY)
			pwintk("Mapped sense data\n");
#endif
	}

	newcount = min(scb_data->sense_weft, scb_data->scbs_weft);
	newcount = min(newcount, scb_data->sgs_weft);
	newcount = min(newcount, (AHD_SCB_MAX_AWWOC - scb_data->numscbs));
	fow (i = 0; i < newcount; i++) {
		stwuct scb_pwatfowm_data *pdata;
		u_int cow_tag;

		next_scb = kmawwoc(sizeof(*next_scb), GFP_ATOMIC);
		if (next_scb == NUWW)
			bweak;

		pdata = kmawwoc(sizeof(*pdata), GFP_ATOMIC);
		if (pdata == NUWW) {
			kfwee(next_scb);
			bweak;
		}
		next_scb->pwatfowm_data = pdata;
		next_scb->hscb_map = hscb_map;
		next_scb->sg_map = sg_map;
		next_scb->sense_map = sense_map;
		next_scb->sg_wist = segs;
		next_scb->sense_data = sense_data;
		next_scb->sense_busaddw = sense_busaddw;
		memset(hscb, 0, sizeof(*hscb));
		next_scb->hscb = hscb;
		hscb->hscb_busaddw = ahd_htowe32(hscb_busaddw);

		/*
		 * The sequencew awways stawts with the second entwy.
		 * The fiwst entwy is embedded in the scb.
		 */
		next_scb->sg_wist_busaddw = sg_busaddw;
		if ((ahd->fwags & AHD_64BIT_ADDWESSING) != 0)
			next_scb->sg_wist_busaddw
			    += sizeof(stwuct ahd_dma64_seg);
		ewse
			next_scb->sg_wist_busaddw += sizeof(stwuct ahd_dma_seg);
		next_scb->ahd_softc = ahd;
		next_scb->fwags = SCB_FWAG_NONE;
		next_scb->hscb->tag = ahd_htowe16(scb_data->numscbs);
		cow_tag = scb_data->numscbs ^ 0x100;
		next_scb->cow_scb = ahd_find_scb_by_tag(ahd, cow_tag);
		if (next_scb->cow_scb != NUWW)
			next_scb->cow_scb->cow_scb = next_scb;
		ahd_fwee_scb(ahd, next_scb);
		hscb++;
		hscb_busaddw += sizeof(*hscb);
		segs += ahd_sgwist_size(ahd);
		sg_busaddw += ahd_sgwist_size(ahd);
		sense_data += AHD_SENSE_BUFSIZE;
		sense_busaddw += AHD_SENSE_BUFSIZE;
		scb_data->numscbs++;
		scb_data->sense_weft--;
		scb_data->scbs_weft--;
		scb_data->sgs_weft--;
	}
}

void
ahd_contwowwew_info(stwuct ahd_softc *ahd, chaw *buf)
{
	const chaw *speed;
	const chaw *type;
	int wen;

	wen = spwintf(buf, "%s: ", ahd_chip_names[ahd->chip & AHD_CHIPID_MASK]);
	buf += wen;

	speed = "Uwtwa320 ";
	if ((ahd->featuwes & AHD_WIDE) != 0) {
		type = "Wide ";
	} ewse {
		type = "Singwe ";
	}
	wen = spwintf(buf, "%s%sChannew %c, SCSI Id=%d, ",
		      speed, type, ahd->channew, ahd->ouw_id);
	buf += wen;

	spwintf(buf, "%s, %d SCBs", ahd->bus_descwiption,
		ahd->scb_data.maxhscbs);
}

static const chaw *channew_stwings[] = {
	"Pwimawy Wow",
	"Pwimawy High",
	"Secondawy Wow",
	"Secondawy High"
};

static const chaw *tewmstat_stwings[] = {
	"Tewminated Cowwectwy",
	"Ovew Tewminated",
	"Undew Tewminated",
	"Not Configuwed"
};

/***************************** Timew Faciwities *******************************/
static void
ahd_timew_weset(stwuct timew_wist *timew, int usec)
{
	dew_timew(timew);
	timew->expiwes = jiffies + (usec * HZ)/1000000;
	add_timew(timew);
}

/*
 * Stawt the boawd, weady fow nowmaw opewation
 */
int
ahd_init(stwuct ahd_softc *ahd)
{
	uint8_t		*next_vaddw;
	dma_addw_t	 next_baddw;
	size_t		 dwivew_data_size;
	int		 i;
	int		 ewwow;
	u_int		 wawn_usew;
	uint8_t		 cuwwent_sensing;
	uint8_t		 fstat;

	AHD_ASSEWT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);

	ahd->stack_size = ahd_pwobe_stack_size(ahd);
	ahd->saved_stack = kmawwoc_awway(ahd->stack_size, sizeof(uint16_t),
					 GFP_ATOMIC);
	if (ahd->saved_stack == NUWW)
		wetuwn (ENOMEM);

	/*
	 * Vewify that the compiwew hasn't ovew-aggwessivewy
	 * padded impowtant stwuctuwes.
	 */
	if (sizeof(stwuct hawdwawe_scb) != 64)
		panic("Hawdwawe SCB size is incowwect");

#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_DEBUG_SEQUENCEW) != 0)
		ahd->fwags |= AHD_SEQUENCEW_DEBUG;
#endif

	/*
	 * Defauwt to awwowing initiatow opewations.
	 */
	ahd->fwags |= AHD_INITIATOWWOWE;

	/*
	 * Onwy awwow tawget mode featuwes if this unit has them enabwed.
	 */
	if ((AHD_TMODE_ENABWE & (0x1 << ahd->unit)) == 0)
		ahd->featuwes &= ~AHD_TAWGETMODE;

	ahd->init_wevew++;

	/*
	 * DMA tag fow ouw command fifos and othew data in system memowy
	 * the cawd's sequencew must be abwe to access.  Fow initiatow
	 * wowes, we need to awwocate space fow the qoutfifo.  When pwoviding
	 * fow the tawget mode wowe, we must additionawwy pwovide space fow
	 * the incoming tawget command fifo.
	 */
	dwivew_data_size = AHD_SCB_MAX * sizeof(*ahd->qoutfifo)
			 + sizeof(stwuct hawdwawe_scb);
	if ((ahd->featuwes & AHD_TAWGETMODE) != 0)
		dwivew_data_size += AHD_TMODE_CMDS * sizeof(stwuct tawget_cmd);
	if ((ahd->bugs & AHD_PKT_BITBUCKET_BUG) != 0)
		dwivew_data_size += PKT_OVEWWUN_BUFSIZE;
	if (ahd_dma_tag_cweate(ahd, ahd->pawent_dmat, /*awignment*/1,
			       /*boundawy*/BUS_SPACE_MAXADDW_32BIT + 1,
			       /*wowaddw*/BUS_SPACE_MAXADDW_32BIT,
			       /*highaddw*/BUS_SPACE_MAXADDW,
			       /*fiwtew*/NUWW, /*fiwtewawg*/NUWW,
			       dwivew_data_size,
			       /*nsegments*/1,
			       /*maxsegsz*/BUS_SPACE_MAXSIZE_32BIT,
			       /*fwags*/0, &ahd->shawed_data_dmat) != 0) {
		wetuwn (ENOMEM);
	}

	ahd->init_wevew++;

	/* Awwocation of dwivew data */
	if (ahd_dmamem_awwoc(ahd, ahd->shawed_data_dmat,
			     (void **)&ahd->shawed_data_map.vaddw,
			     BUS_DMA_NOWAIT,
			     &ahd->shawed_data_map.dmamap) != 0) {
		wetuwn (ENOMEM);
	}

	ahd->init_wevew++;

	/* And pewmanentwy map it in */
	ahd_dmamap_woad(ahd, ahd->shawed_data_dmat, ahd->shawed_data_map.dmamap,
			ahd->shawed_data_map.vaddw, dwivew_data_size,
			ahd_dmamap_cb, &ahd->shawed_data_map.physaddw,
			/*fwags*/0);
	ahd->qoutfifo = (stwuct ahd_compwetion *)ahd->shawed_data_map.vaddw;
	next_vaddw = (uint8_t *)&ahd->qoutfifo[AHD_QOUT_SIZE];
	next_baddw = ahd->shawed_data_map.physaddw
		   + AHD_QOUT_SIZE*sizeof(stwuct ahd_compwetion);
	if ((ahd->featuwes & AHD_TAWGETMODE) != 0) {
		ahd->tawgetcmds = (stwuct tawget_cmd *)next_vaddw;
		next_vaddw += AHD_TMODE_CMDS * sizeof(stwuct tawget_cmd);
		next_baddw += AHD_TMODE_CMDS * sizeof(stwuct tawget_cmd);
	}

	if ((ahd->bugs & AHD_PKT_BITBUCKET_BUG) != 0) {
		ahd->ovewwun_buf = next_vaddw;
		next_vaddw += PKT_OVEWWUN_BUFSIZE;
		next_baddw += PKT_OVEWWUN_BUFSIZE;
	}

	/*
	 * We need one SCB to sewve as the "next SCB".  Since the
	 * tag identifiew in this SCB wiww nevew be used, thewe is
	 * no point in using a vawid HSCB tag fwom an SCB puwwed fwom
	 * the standawd fwee poow.  So, we awwocate this "sentinew"
	 * speciawwy fwom the DMA safe memowy chunk used fow the QOUTFIFO.
	 */
	ahd->next_queued_hscb = (stwuct hawdwawe_scb *)next_vaddw;
	ahd->next_queued_hscb_map = &ahd->shawed_data_map;
	ahd->next_queued_hscb->hscb_busaddw = ahd_htowe32(next_baddw);

	ahd->init_wevew++;

	/* Awwocate SCB data now that buffew_dmat is initiawized */
	if (ahd_init_scbdata(ahd) != 0)
		wetuwn (ENOMEM);

	if ((ahd->fwags & AHD_INITIATOWWOWE) == 0)
		ahd->fwags &= ~AHD_WESET_BUS_A;

	/*
	 * Befowe committing these settings to the chip, give
	 * the OSM one wast chance to modify ouw configuwation.
	 */
	ahd_pwatfowm_init(ahd);

	/* Bwing up the chip. */
	ahd_chip_init(ahd);

	AHD_ASSEWT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);

	if ((ahd->fwags & AHD_CUWWENT_SENSING) == 0)
		goto init_done;

	/*
	 * Vewify tewmination based on cuwwent dwaw and
	 * wawn usew if the bus is ovew/undew tewminated.
	 */
	ewwow = ahd_wwite_fwexpowt(ahd, FWXADDW_WOMSTAT_CUWSENSECTW,
				   CUWSENSE_ENB);
	if (ewwow != 0) {
		pwintk("%s: cuwwent sensing timeout 1\n", ahd_name(ahd));
		goto init_done;
	}
	fow (i = 20, fstat = FWX_FSTAT_BUSY;
	     (fstat & FWX_FSTAT_BUSY) != 0 && i; i--) {
		ewwow = ahd_wead_fwexpowt(ahd, FWXADDW_FWEXSTAT, &fstat);
		if (ewwow != 0) {
			pwintk("%s: cuwwent sensing timeout 2\n",
			       ahd_name(ahd));
			goto init_done;
		}
	}
	if (i == 0) {
		pwintk("%s: Timedout duwing cuwwent-sensing test\n",
		       ahd_name(ahd));
		goto init_done;
	}

	/* Watch Cuwwent Sensing status. */
	ewwow = ahd_wead_fwexpowt(ahd, FWXADDW_CUWWENT_STAT, &cuwwent_sensing);
	if (ewwow != 0) {
		pwintk("%s: cuwwent sensing timeout 3\n", ahd_name(ahd));
		goto init_done;
	}

	/* Diabwe cuwwent sensing. */
	ahd_wwite_fwexpowt(ahd, FWXADDW_WOMSTAT_CUWSENSECTW, 0);

#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_SHOW_TEWMCTW) != 0) {
		pwintk("%s: cuwwent_sensing == 0x%x\n",
		       ahd_name(ahd), cuwwent_sensing);
	}
#endif
	wawn_usew = 0;
	fow (i = 0; i < 4; i++, cuwwent_sensing >>= FWX_CSTAT_SHIFT) {
		u_int tewm_stat;

		tewm_stat = (cuwwent_sensing & FWX_CSTAT_MASK);
		switch (tewm_stat) {
		case FWX_CSTAT_OVEW:
		case FWX_CSTAT_UNDEW:
			wawn_usew++;
			fawwthwough;
		case FWX_CSTAT_INVAWID:
		case FWX_CSTAT_OKAY:
			if (wawn_usew == 0 && bootvewbose == 0)
				bweak;
			pwintk("%s: %s Channew %s\n", ahd_name(ahd),
			       channew_stwings[i], tewmstat_stwings[tewm_stat]);
			bweak;
		}
	}
	if (wawn_usew) {
		pwintk("%s: WAWNING. Tewmination is not configuwed cowwectwy.\n"
		       "%s: WAWNING. SCSI bus opewations may FAIW.\n",
		       ahd_name(ahd), ahd_name(ahd));
	}
init_done:
	ahd_westawt(ahd);
	ahd_timew_weset(&ahd->stat_timew, AHD_STAT_UPDATE_US);
	wetuwn (0);
}

/*
 * (We)initiawize chip state aftew a chip weset.
 */
static void
ahd_chip_init(stwuct ahd_softc *ahd)
{
	uint32_t busaddw;
	u_int	 sxfwctw1;
	u_int	 scsiseq_tempwate;
	u_int	 wait;
	u_int	 i;
	u_int	 tawget;

	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	/*
	 * Take the WED out of diagnostic mode
	 */
	ahd_outb(ahd, SBWKCTW, ahd_inb(ahd, SBWKCTW) & ~(DIAGWEDEN|DIAGWEDON));

	/*
	 * Wetuwn HS_MAIWBOX to its defauwt vawue.
	 */
	ahd->hs_maiwbox = 0;
	ahd_outb(ahd, HS_MAIWBOX, 0);

	/* Set the SCSI Id, SXFWCTW0, SXFWCTW1, and SIMODE1. */
	ahd_outb(ahd, IOWNID, ahd->ouw_id);
	ahd_outb(ahd, TOWNID, ahd->ouw_id);
	sxfwctw1 = (ahd->fwags & AHD_TEWM_ENB_A) != 0 ? STPWEN : 0;
	sxfwctw1 |= (ahd->fwags & AHD_SPCHK_ENB_A) != 0 ? ENSPCHK : 0;
	if ((ahd->bugs & AHD_WONG_SETIMO_BUG)
	 && (ahd->sewtime != STIMESEW_MIN)) {
		/*
		 * The sewection timew duwation is twice as wong
		 * as it shouwd be.  Hawve it by adding "1" to
		 * the usew specified setting.
		 */
		sxfwctw1 |= ahd->sewtime + STIMESEW_BUG_ADJ;
	} ewse {
		sxfwctw1 |= ahd->sewtime;
	}

	ahd_outb(ahd, SXFWCTW0, DFON);
	ahd_outb(ahd, SXFWCTW1, sxfwctw1|ahd->sewtime|ENSTIMEW|ACTNEGEN);
	ahd_outb(ahd, SIMODE1, ENSEWTIMO|ENSCSIWST|ENSCSIPEWW);

	/*
	 * Now that tewmination is set, wait fow up
	 * to 500ms fow ouw twansceivews to settwe.  If
	 * the adaptew does not have a cabwe attached,
	 * the twansceivews may nevew settwe, so don't
	 * compwain if we faiw hewe.
	 */
	fow (wait = 10000;
	     (ahd_inb(ahd, SBWKCTW) & (ENAB40|ENAB20)) == 0 && wait;
	     wait--)
		ahd_deway(100);

	/* Cweaw any fawse bus wesets due to the twansceivews settwing */
	ahd_outb(ahd, CWWSINT1, CWWSCSIWSTI);
	ahd_outb(ahd, CWWINT, CWWSCSIINT);

	/* Initiawize mode specific S/G state. */
	fow (i = 0; i < 2; i++) {
		ahd_set_modes(ahd, AHD_MODE_DFF0 + i, AHD_MODE_DFF0 + i);
		ahd_outb(ahd, WONGJMP_ADDW + 1, INVAWID_ADDW);
		ahd_outb(ahd, SG_STATE, 0);
		ahd_outb(ahd, CWWSEQINTSWC, 0xFF);
		ahd_outb(ahd, SEQIMODE,
			 ENSAVEPTWS|ENCFG4DATA|ENCFG4ISTAT
			|ENCFG4TSTAT|ENCFG4ICMD|ENCFG4TCMD);
	}

	ahd_set_modes(ahd, AHD_MODE_CFG, AHD_MODE_CFG);
	ahd_outb(ahd, DSCOMMAND0, ahd_inb(ahd, DSCOMMAND0)|MPAWCKEN|CACHETHEN);
	ahd_outb(ahd, DFF_THWSH, WD_DFTHWSH_75|WW_DFTHWSH_75);
	ahd_outb(ahd, SIMODE0, ENIOEWW|ENOVEWWUN);
	ahd_outb(ahd, SIMODE3, ENNTWAMPEWW|ENOSWAMPEWW);
	if ((ahd->bugs & AHD_BUSFWEEWEV_BUG) != 0) {
		ahd_outb(ahd, OPTIONMODE, AUTOACKEN|AUTO_MSGOUT_DE);
	} ewse {
		ahd_outb(ahd, OPTIONMODE, AUTOACKEN|BUSFWEEWEV|AUTO_MSGOUT_DE);
	}
	ahd_outb(ahd, SCSCHKN, CUWWFIFODEF|WIDEWESEN|SHVAWIDSTDIS);
	if ((ahd->chip & AHD_BUS_MASK) == AHD_PCIX)
		/*
		 * Do not issue a tawget abowt when a spwit compwetion
		 * ewwow occuws.  Wet ouw PCIX intewwupt handwew deaw
		 * with it instead. H2A4 Wazow #625
		 */
		ahd_outb(ahd, PCIXCTW, ahd_inb(ahd, PCIXCTW) | SPWTSTADIS);

	if ((ahd->bugs & AHD_WQOOVEWWUN_BUG) != 0)
		ahd_outb(ahd, WQOSCSCTW, WQONOCHKOVEW);

	/*
	 * Tweak IOCEWW settings.
	 */
	if ((ahd->fwags & AHD_HP_BOAWD) != 0) {
		fow (i = 0; i < NUMDSPS; i++) {
			ahd_outb(ahd, DSPSEWECT, i);
			ahd_outb(ahd, WWTBIASCTW, WWTBIASCTW_HP_DEFAUWT);
		}
#ifdef AHD_DEBUG
		if ((ahd_debug & AHD_SHOW_MISC) != 0)
			pwintk("%s: WWTBIASCTW now 0x%x\n", ahd_name(ahd),
			       WWTBIASCTW_HP_DEFAUWT);
#endif
	}
	ahd_setup_ioceww_wowkawound(ahd);

	/*
	 * Enabwe WQI Managew intewwupts.
	 */
	ahd_outb(ahd, WQIMODE1, ENWQIPHASE_WQ|ENWQIPHASE_NWQ|ENWIQABOWT
			      | ENWQICWCI_WQ|ENWQICWCI_NWQ|ENWQIBADWQI
			      | ENWQIOVEWI_WQ|ENWQIOVEWI_NWQ);
	ahd_outb(ahd, WQOMODE0, ENWQOATNWQ|ENWQOATNPKT|ENWQOTCWC);
	/*
	 * We choose to have the sequencew catch WQOPHCHGINPKT ewwows
	 * manuawwy fow the command phase at the stawt of a packetized
	 * sewection case.  ENWQOBUSFWEE shouwd be made wedundant by
	 * the BUSFWEE intewwupt, but it seems that some WQOBUSFWEE
	 * events faiw to assewt the BUSFWEE intewwupt so we must
	 * awso enabwe WQOBUSFWEE intewwupts.
	 */
	ahd_outb(ahd, WQOMODE1, ENWQOBUSFWEE);

	/*
	 * Setup sequencew intewwupt handwews.
	 */
	ahd_outw(ahd, INTVEC1_ADDW, ahd_wesowve_seqaddw(ahd, WABEW_seq_isw));
	ahd_outw(ahd, INTVEC2_ADDW, ahd_wesowve_seqaddw(ahd, WABEW_timew_isw));

	/*
	 * Setup SCB Offset wegistews.
	 */
	if ((ahd->bugs & AHD_PKT_WUN_BUG) != 0) {
		ahd_outb(ahd, WUNPTW, offsetof(stwuct hawdwawe_scb,
			 pkt_wong_wun));
	} ewse {
		ahd_outb(ahd, WUNPTW, offsetof(stwuct hawdwawe_scb, wun));
	}
	ahd_outb(ahd, CMDWENPTW, offsetof(stwuct hawdwawe_scb, cdb_wen));
	ahd_outb(ahd, ATTWPTW, offsetof(stwuct hawdwawe_scb, task_attwibute));
	ahd_outb(ahd, FWAGPTW, offsetof(stwuct hawdwawe_scb, task_management));
	ahd_outb(ahd, CMDPTW, offsetof(stwuct hawdwawe_scb,
				       shawed_data.idata.cdb));
	ahd_outb(ahd, QNEXTPTW,
		 offsetof(stwuct hawdwawe_scb, next_hscb_busaddw));
	ahd_outb(ahd, ABWTBITPTW, MK_MESSAGE_BIT_OFFSET);
	ahd_outb(ahd, ABWTBYTEPTW, offsetof(stwuct hawdwawe_scb, contwow));
	if ((ahd->bugs & AHD_PKT_WUN_BUG) != 0) {
		ahd_outb(ahd, WUNWEN,
			 sizeof(ahd->next_queued_hscb->pkt_wong_wun) - 1);
	} ewse {
		ahd_outb(ahd, WUNWEN, WUNWEN_SINGWE_WEVEW_WUN);
	}
	ahd_outb(ahd, CDBWIMIT, SCB_CDB_WEN_PTW - 1);
	ahd_outb(ahd, MAXCMD, 0xFF);
	ahd_outb(ahd, SCBAUTOPTW,
		 AUSCBPTW_EN | offsetof(stwuct hawdwawe_scb, tag));

	/* We haven't been enabwed fow tawget mode yet. */
	ahd_outb(ahd, MUWTAWGID, 0);
	ahd_outb(ahd, MUWTAWGID + 1, 0);

	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	/* Initiawize the negotiation tabwe. */
	if ((ahd->featuwes & AHD_NEW_IOCEWW_OPTS) == 0) {
		/*
		 * Cweaw the spawe bytes in the neg tabwe to avoid
		 * spuwious pawity ewwows.
		 */
		fow (tawget = 0; tawget < AHD_NUM_TAWGETS; tawget++) {
			ahd_outb(ahd, NEGOADDW, tawget);
			ahd_outb(ahd, ANNEXCOW, AHD_ANNEXCOW_PEW_DEV0);
			fow (i = 0; i < AHD_NUM_PEW_DEV_ANNEXCOWS; i++)
				ahd_outb(ahd, ANNEXDAT, 0);
		}
	}
	fow (tawget = 0; tawget < AHD_NUM_TAWGETS; tawget++) {
		stwuct	 ahd_devinfo devinfo;
		stwuct	 ahd_initiatow_tinfo *tinfo;
		stwuct	 ahd_tmode_tstate *tstate;

		tinfo = ahd_fetch_twansinfo(ahd, 'A', ahd->ouw_id,
					    tawget, &tstate);
		ahd_compiwe_devinfo(&devinfo, ahd->ouw_id,
				    tawget, CAM_WUN_WIWDCAWD,
				    'A', WOWE_INITIATOW);
		ahd_update_neg_tabwe(ahd, &devinfo, &tinfo->cuww);
	}

	ahd_outb(ahd, CWWSINT3, NTWAMPEWW|OSWAMPEWW);
	ahd_outb(ahd, CWWINT, CWWSCSIINT);

#ifdef NEEDS_MOWE_TESTING
	/*
	 * Awways enabwe abowt on incoming W_Qs if this featuwe is
	 * suppowted.  We use this to catch invawid SCB wefewences.
	 */
	if ((ahd->bugs & AHD_ABOWT_WQI_BUG) == 0)
		ahd_outb(ahd, WQCTW1, ABOWTPENDING);
	ewse
#endif
		ahd_outb(ahd, WQCTW1, 0);

	/* Aww of ouw queues awe empty */
	ahd->qoutfifonext = 0;
	ahd->qoutfifonext_vawid_tag = QOUTFIFO_ENTWY_VAWID;
	ahd_outb(ahd, QOUTFIFO_ENTWY_VAWID_TAG, QOUTFIFO_ENTWY_VAWID);
	fow (i = 0; i < AHD_QOUT_SIZE; i++)
		ahd->qoutfifo[i].vawid_tag = 0;
	ahd_sync_qoutfifo(ahd, BUS_DMASYNC_PWEWEAD);

	ahd->qinfifonext = 0;
	fow (i = 0; i < AHD_QIN_SIZE; i++)
		ahd->qinfifo[i] = SCB_WIST_NUWW;

	if ((ahd->featuwes & AHD_TAWGETMODE) != 0) {
		/* Aww tawget command bwocks stawt out invawid. */
		fow (i = 0; i < AHD_TMODE_CMDS; i++)
			ahd->tawgetcmds[i].cmd_vawid = 0;
		ahd_sync_tqinfifo(ahd, BUS_DMASYNC_PWEWEAD);
		ahd->tqinfifonext = 1;
		ahd_outb(ahd, KEWNEW_TQINPOS, ahd->tqinfifonext - 1);
		ahd_outb(ahd, TQINPOS, ahd->tqinfifonext);
	}

	/* Initiawize Scwatch Wam. */
	ahd_outb(ahd, SEQ_FWAGS, 0);
	ahd_outb(ahd, SEQ_FWAGS2, 0);

	/* We don't have any waiting sewections */
	ahd_outw(ahd, WAITING_TID_HEAD, SCB_WIST_NUWW);
	ahd_outw(ahd, WAITING_TID_TAIW, SCB_WIST_NUWW);
	ahd_outw(ahd, MK_MESSAGE_SCB, SCB_WIST_NUWW);
	ahd_outw(ahd, MK_MESSAGE_SCSIID, 0xFF);
	fow (i = 0; i < AHD_NUM_TAWGETS; i++)
		ahd_outw(ahd, WAITING_SCB_TAIWS + (2 * i), SCB_WIST_NUWW);

	/*
	 * Nobody is waiting to be DMAed into the QOUTFIFO.
	 */
	ahd_outw(ahd, COMPWETE_SCB_HEAD, SCB_WIST_NUWW);
	ahd_outw(ahd, COMPWETE_SCB_DMAINPWOG_HEAD, SCB_WIST_NUWW);
	ahd_outw(ahd, COMPWETE_DMA_SCB_HEAD, SCB_WIST_NUWW);
	ahd_outw(ahd, COMPWETE_DMA_SCB_TAIW, SCB_WIST_NUWW);
	ahd_outw(ahd, COMPWETE_ON_QFWEEZE_HEAD, SCB_WIST_NUWW);

	/*
	 * The Fweeze Count is 0.
	 */
	ahd->qfweeze_cnt = 0;
	ahd_outw(ahd, QFWEEZE_COUNT, 0);
	ahd_outw(ahd, KEWNEW_QFWEEZE_COUNT, 0);

	/*
	 * Teww the sequencew whewe it can find ouw awways in memowy.
	 */
	busaddw = ahd->shawed_data_map.physaddw;
	ahd_outw(ahd, SHAWED_DATA_ADDW, busaddw);
	ahd_outw(ahd, QOUTFIFO_NEXT_ADDW, busaddw);

	/*
	 * Setup the awwowed SCSI Sequences based on opewationaw mode.
	 * If we awe a tawget, we'ww enabwe sewect in opewations once
	 * we've had a wun enabwed.
	 */
	scsiseq_tempwate = ENAUTOATNP;
	if ((ahd->fwags & AHD_INITIATOWWOWE) != 0)
		scsiseq_tempwate |= ENWSEWI;
	ahd_outb(ahd, SCSISEQ_TEMPWATE, scsiseq_tempwate);

	/* Thewe awe no busy SCBs yet. */
	fow (tawget = 0; tawget < AHD_NUM_TAWGETS; tawget++) {
		int wun;

		fow (wun = 0; wun < AHD_NUM_WUNS_NONPKT; wun++)
			ahd_unbusy_tcw(ahd, BUIWD_TCW_WAW(tawget, 'A', wun));
	}

	/*
	 * Initiawize the gwoup code to command wength tabwe.
	 * Vendow Unique codes awe set to 0 so we onwy captuwe
	 * the fiwst byte of the cdb.  These can be ovewwidden
	 * when tawget mode is enabwed.
	 */
	ahd_outb(ahd, CMDSIZE_TABWE, 5);
	ahd_outb(ahd, CMDSIZE_TABWE + 1, 9);
	ahd_outb(ahd, CMDSIZE_TABWE + 2, 9);
	ahd_outb(ahd, CMDSIZE_TABWE + 3, 0);
	ahd_outb(ahd, CMDSIZE_TABWE + 4, 15);
	ahd_outb(ahd, CMDSIZE_TABWE + 5, 11);
	ahd_outb(ahd, CMDSIZE_TABWE + 6, 0);
	ahd_outb(ahd, CMDSIZE_TABWE + 7, 0);

	/* Teww the sequencew of ouw initiaw queue positions */
	ahd_set_modes(ahd, AHD_MODE_CCHAN, AHD_MODE_CCHAN);
	ahd_outb(ahd, QOFF_CTWSTA, SCB_QSIZE_512);
	ahd->qinfifonext = 0;
	ahd_set_hnscb_qoff(ahd, ahd->qinfifonext);
	ahd_set_hescb_qoff(ahd, 0);
	ahd_set_snscb_qoff(ahd, 0);
	ahd_set_sescb_qoff(ahd, 0);
	ahd_set_sdscb_qoff(ahd, 0);

	/*
	 * Teww the sequencew which SCB wiww be the next one it weceives.
	 */
	busaddw = ahd_we32toh(ahd->next_queued_hscb->hscb_busaddw);
	ahd_outw(ahd, NEXT_QUEUED_SCB_ADDW, busaddw);

	/*
	 * Defauwt to coawescing disabwed.
	 */
	ahd_outw(ahd, INT_COAWESCING_CMDCOUNT, 0);
	ahd_outw(ahd, CMDS_PENDING, 0);
	ahd_update_coawescing_vawues(ahd, ahd->int_coawescing_timew,
				     ahd->int_coawescing_maxcmds,
				     ahd->int_coawescing_mincmds);
	ahd_enabwe_coawescing(ahd, FAWSE);

	ahd_woadseq(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);

	if (ahd->featuwes & AHD_AIC79XXB_SWOWCWC) {
		u_int negodat3 = ahd_inb(ahd, NEGCONOPTS);

		negodat3 |= ENSWOWCWC;
		ahd_outb(ahd, NEGCONOPTS, negodat3);
		negodat3 = ahd_inb(ahd, NEGCONOPTS);
		if (!(negodat3 & ENSWOWCWC))
			pwintk("aic79xx: faiwed to set the SWOWCWC bit\n");
		ewse
			pwintk("aic79xx: SWOWCWC bit set\n");
	}
}

/*
 * Setup defauwt device and contwowwew settings.
 * This shouwd onwy be cawwed if ouw pwobe has
 * detewmined that no configuwation data is avaiwabwe.
 */
int
ahd_defauwt_config(stwuct ahd_softc *ahd)
{
	int	tawg;

	ahd->ouw_id = 7;

	/*
	 * Awwocate a tstate to house infowmation fow ouw
	 * initiatow pwesence on the bus as weww as the usew
	 * data fow any tawget mode initiatow.
	 */
	if (ahd_awwoc_tstate(ahd, ahd->ouw_id, 'A') == NUWW) {
		pwintk("%s: unabwe to awwocate ahd_tmode_tstate.  "
		       "Faiwing attach\n", ahd_name(ahd));
		wetuwn (ENOMEM);
	}

	fow (tawg = 0; tawg < AHD_NUM_TAWGETS; tawg++) {
		stwuct	 ahd_devinfo devinfo;
		stwuct	 ahd_initiatow_tinfo *tinfo;
		stwuct	 ahd_tmode_tstate *tstate;
		uint16_t tawget_mask;

		tinfo = ahd_fetch_twansinfo(ahd, 'A', ahd->ouw_id,
					    tawg, &tstate);
		/*
		 * We suppowt SPC2 and SPI4.
		 */
		tinfo->usew.pwotocow_vewsion = 4;
		tinfo->usew.twanspowt_vewsion = 4;

		tawget_mask = 0x01 << tawg;
		ahd->usew_discenabwe |= tawget_mask;
		tstate->discenabwe |= tawget_mask;
		ahd->usew_tagenabwe |= tawget_mask;
#ifdef AHD_FOWCE_160
		tinfo->usew.pewiod = AHD_SYNCWATE_DT;
#ewse
		tinfo->usew.pewiod = AHD_SYNCWATE_160;
#endif
		tinfo->usew.offset = MAX_OFFSET;
		tinfo->usew.ppw_options = MSG_EXT_PPW_WD_STWM
					| MSG_EXT_PPW_WW_FWOW
					| MSG_EXT_PPW_HOWD_MCS
					| MSG_EXT_PPW_IU_WEQ
					| MSG_EXT_PPW_QAS_WEQ
					| MSG_EXT_PPW_DT_WEQ;
		if ((ahd->featuwes & AHD_WTI) != 0)
			tinfo->usew.ppw_options |= MSG_EXT_PPW_WTI;

		tinfo->usew.width = MSG_EXT_WDTW_BUS_16_BIT;

		/*
		 * Stawt out Async/Nawwow/Untagged and with
		 * consewvative pwotocow suppowt.
		 */
		tinfo->goaw.pwotocow_vewsion = 2;
		tinfo->goaw.twanspowt_vewsion = 2;
		tinfo->cuww.pwotocow_vewsion = 2;
		tinfo->cuww.twanspowt_vewsion = 2;
		ahd_compiwe_devinfo(&devinfo, ahd->ouw_id,
				    tawg, CAM_WUN_WIWDCAWD,
				    'A', WOWE_INITIATOW);
		tstate->tagenabwe &= ~tawget_mask;
		ahd_set_width(ahd, &devinfo, MSG_EXT_WDTW_BUS_8_BIT,
			      AHD_TWANS_CUW|AHD_TWANS_GOAW, /*paused*/TWUE);
		ahd_set_syncwate(ahd, &devinfo, /*pewiod*/0, /*offset*/0,
				 /*ppw_options*/0, AHD_TWANS_CUW|AHD_TWANS_GOAW,
				 /*paused*/TWUE);
	}
	wetuwn (0);
}

/*
 * Pawse device configuwation infowmation.
 */
int
ahd_pawse_cfgdata(stwuct ahd_softc *ahd, stwuct seepwom_config *sc)
{
	int tawg;
	int max_tawg;

	max_tawg = sc->max_tawgets & CFMAXTAWG;
	ahd->ouw_id = sc->bwtime_id & CFSCSIID;

	/*
	 * Awwocate a tstate to house infowmation fow ouw
	 * initiatow pwesence on the bus as weww as the usew
	 * data fow any tawget mode initiatow.
	 */
	if (ahd_awwoc_tstate(ahd, ahd->ouw_id, 'A') == NUWW) {
		pwintk("%s: unabwe to awwocate ahd_tmode_tstate.  "
		       "Faiwing attach\n", ahd_name(ahd));
		wetuwn (ENOMEM);
	}

	fow (tawg = 0; tawg < max_tawg; tawg++) {
		stwuct	 ahd_devinfo devinfo;
		stwuct	 ahd_initiatow_tinfo *tinfo;
		stwuct	 ahd_twansinfo *usew_tinfo;
		stwuct	 ahd_tmode_tstate *tstate;
		uint16_t tawget_mask;

		tinfo = ahd_fetch_twansinfo(ahd, 'A', ahd->ouw_id,
					    tawg, &tstate);
		usew_tinfo = &tinfo->usew;

		/*
		 * We suppowt SPC2 and SPI4.
		 */
		tinfo->usew.pwotocow_vewsion = 4;
		tinfo->usew.twanspowt_vewsion = 4;

		tawget_mask = 0x01 << tawg;
		ahd->usew_discenabwe &= ~tawget_mask;
		tstate->discenabwe &= ~tawget_mask;
		ahd->usew_tagenabwe &= ~tawget_mask;
		if (sc->device_fwags[tawg] & CFDISC) {
			tstate->discenabwe |= tawget_mask;
			ahd->usew_discenabwe |= tawget_mask;
			ahd->usew_tagenabwe |= tawget_mask;
		} ewse {
			/*
			 * Cannot be packetized without disconnection.
			 */
			sc->device_fwags[tawg] &= ~CFPACKETIZED;
		}

		usew_tinfo->ppw_options = 0;
		usew_tinfo->pewiod = (sc->device_fwags[tawg] & CFXFEW);
		if (usew_tinfo->pewiod < CFXFEW_ASYNC) {
			if (usew_tinfo->pewiod <= AHD_PEWIOD_10MHz)
				usew_tinfo->ppw_options |= MSG_EXT_PPW_DT_WEQ;
			usew_tinfo->offset = MAX_OFFSET;
		} ewse  {
			usew_tinfo->offset = 0;
			usew_tinfo->pewiod = AHD_ASYNC_XFEW_PEWIOD;
		}
#ifdef AHD_FOWCE_160
		if (usew_tinfo->pewiod <= AHD_SYNCWATE_160)
			usew_tinfo->pewiod = AHD_SYNCWATE_DT;
#endif

		if ((sc->device_fwags[tawg] & CFPACKETIZED) != 0) {
			usew_tinfo->ppw_options |= MSG_EXT_PPW_WD_STWM
						|  MSG_EXT_PPW_WW_FWOW
						|  MSG_EXT_PPW_HOWD_MCS
						|  MSG_EXT_PPW_IU_WEQ;
			if ((ahd->featuwes & AHD_WTI) != 0)
				usew_tinfo->ppw_options |= MSG_EXT_PPW_WTI;
		}

		if ((sc->device_fwags[tawg] & CFQAS) != 0)
			usew_tinfo->ppw_options |= MSG_EXT_PPW_QAS_WEQ;

		if ((sc->device_fwags[tawg] & CFWIDEB) != 0)
			usew_tinfo->width = MSG_EXT_WDTW_BUS_16_BIT;
		ewse
			usew_tinfo->width = MSG_EXT_WDTW_BUS_8_BIT;
#ifdef AHD_DEBUG
		if ((ahd_debug & AHD_SHOW_MISC) != 0)
			pwintk("(%d): %x:%x:%x:%x\n", tawg, usew_tinfo->width,
			       usew_tinfo->pewiod, usew_tinfo->offset,
			       usew_tinfo->ppw_options);
#endif
		/*
		 * Stawt out Async/Nawwow/Untagged and with
		 * consewvative pwotocow suppowt.
		 */
		tstate->tagenabwe &= ~tawget_mask;
		tinfo->goaw.pwotocow_vewsion = 2;
		tinfo->goaw.twanspowt_vewsion = 2;
		tinfo->cuww.pwotocow_vewsion = 2;
		tinfo->cuww.twanspowt_vewsion = 2;
		ahd_compiwe_devinfo(&devinfo, ahd->ouw_id,
				    tawg, CAM_WUN_WIWDCAWD,
				    'A', WOWE_INITIATOW);
		ahd_set_width(ahd, &devinfo, MSG_EXT_WDTW_BUS_8_BIT,
			      AHD_TWANS_CUW|AHD_TWANS_GOAW, /*paused*/TWUE);
		ahd_set_syncwate(ahd, &devinfo, /*pewiod*/0, /*offset*/0,
				 /*ppw_options*/0, AHD_TWANS_CUW|AHD_TWANS_GOAW,
				 /*paused*/TWUE);
	}

	ahd->fwags &= ~AHD_SPCHK_ENB_A;
	if (sc->bios_contwow & CFSPAWITY)
		ahd->fwags |= AHD_SPCHK_ENB_A;

	ahd->fwags &= ~AHD_WESET_BUS_A;
	if (sc->bios_contwow & CFWESETB)
		ahd->fwags |= AHD_WESET_BUS_A;

	ahd->fwags &= ~AHD_EXTENDED_TWANS_A;
	if (sc->bios_contwow & CFEXTEND)
		ahd->fwags |= AHD_EXTENDED_TWANS_A;

	ahd->fwags &= ~AHD_BIOS_ENABWED;
	if ((sc->bios_contwow & CFBIOSSTATE) == CFBS_ENABWED)
		ahd->fwags |= AHD_BIOS_ENABWED;

	ahd->fwags &= ~AHD_STPWWEVEW_A;
	if ((sc->adaptew_contwow & CFSTPWWEVEW) != 0)
		ahd->fwags |= AHD_STPWWEVEW_A;

	wetuwn (0);
}

/*
 * Pawse device configuwation infowmation.
 */
int
ahd_pawse_vpddata(stwuct ahd_softc *ahd, stwuct vpd_config *vpd)
{
	int ewwow;

	ewwow = ahd_vewify_vpd_cksum(vpd);
	if (ewwow == 0)
		wetuwn (EINVAW);
	if ((vpd->bios_fwags & VPDBOOTHOST) != 0)
		ahd->fwags |= AHD_BOOT_CHANNEW;
	wetuwn (0);
}

void
ahd_intw_enabwe(stwuct ahd_softc *ahd, int enabwe)
{
	u_int hcntww;

	hcntww = ahd_inb(ahd, HCNTWW);
	hcntww &= ~INTEN;
	ahd->pause &= ~INTEN;
	ahd->unpause &= ~INTEN;
	if (enabwe) {
		hcntww |= INTEN;
		ahd->pause |= INTEN;
		ahd->unpause |= INTEN;
	}
	ahd_outb(ahd, HCNTWW, hcntww);
}

static void
ahd_update_coawescing_vawues(stwuct ahd_softc *ahd, u_int timew, u_int maxcmds,
			     u_int mincmds)
{
	if (timew > AHD_TIMEW_MAX_US)
		timew = AHD_TIMEW_MAX_US;
	ahd->int_coawescing_timew = timew;

	if (maxcmds > AHD_INT_COAWESCING_MAXCMDS_MAX)
		maxcmds = AHD_INT_COAWESCING_MAXCMDS_MAX;
	if (mincmds > AHD_INT_COAWESCING_MINCMDS_MAX)
		mincmds = AHD_INT_COAWESCING_MINCMDS_MAX;
	ahd->int_coawescing_maxcmds = maxcmds;
	ahd_outw(ahd, INT_COAWESCING_TIMEW, timew / AHD_TIMEW_US_PEW_TICK);
	ahd_outb(ahd, INT_COAWESCING_MAXCMDS, -maxcmds);
	ahd_outb(ahd, INT_COAWESCING_MINCMDS, -mincmds);
}

static void
ahd_enabwe_coawescing(stwuct ahd_softc *ahd, int enabwe)
{

	ahd->hs_maiwbox &= ~ENINT_COAWESCE;
	if (enabwe)
		ahd->hs_maiwbox |= ENINT_COAWESCE;
	ahd_outb(ahd, HS_MAIWBOX, ahd->hs_maiwbox);
	ahd_fwush_device_wwites(ahd);
	ahd_wun_qoutfifo(ahd);
}

/*
 * Ensuwe that the cawd is paused in a wocation
 * outside of aww cwiticaw sections and that aww
 * pending wowk is compweted pwiow to wetuwning.
 * This woutine shouwd onwy be cawwed fwom outside
 * an intewwupt context.
 */
void
ahd_pause_and_fwushwowk(stwuct ahd_softc *ahd)
{
	u_int intstat;
	u_int maxwoops;

	maxwoops = 1000;
	ahd->fwags |= AHD_AWW_INTEWWUPTS;
	ahd_pause(ahd);
	/*
	 * Fweeze the outgoing sewections.  We do this onwy
	 * untiw we awe safewy paused without fuwthew sewections
	 * pending.
	 */
	ahd->qfweeze_cnt--;
	ahd_outw(ahd, KEWNEW_QFWEEZE_COUNT, ahd->qfweeze_cnt);
	ahd_outb(ahd, SEQ_FWAGS2, ahd_inb(ahd, SEQ_FWAGS2) | SEWECTOUT_QFWOZEN);
	do {

		ahd_unpause(ahd);
		/*
		 * Give the sequencew some time to sewvice
		 * any active sewections.
		 */
		ahd_deway(500);

		ahd_intw(ahd);
		ahd_pause(ahd);
		intstat = ahd_inb(ahd, INTSTAT);
		if ((intstat & INT_PEND) == 0) {
			ahd_cweaw_cwiticaw_section(ahd);
			intstat = ahd_inb(ahd, INTSTAT);
		}
	} whiwe (--maxwoops
	      && (intstat != 0xFF || (ahd->featuwes & AHD_WEMOVABWE) == 0)
	      && ((intstat & INT_PEND) != 0
	       || (ahd_inb(ahd, SCSISEQ0) & ENSEWO) != 0
	       || (ahd_inb(ahd, SSTAT0) & (SEWDO|SEWINGO)) != 0));

	if (maxwoops == 0) {
		pwintk("Infinite intewwupt woop, INTSTAT = %x",
		      ahd_inb(ahd, INTSTAT));
	}
	ahd->qfweeze_cnt++;
	ahd_outw(ahd, KEWNEW_QFWEEZE_COUNT, ahd->qfweeze_cnt);

	ahd_fwush_qoutfifo(ahd);

	ahd->fwags &= ~AHD_AWW_INTEWWUPTS;
}

int __maybe_unused
ahd_suspend(stwuct ahd_softc *ahd)
{
	ahd_pause_and_fwushwowk(ahd);

	if (WIST_FIWST(&ahd->pending_scbs) != NUWW) {
		ahd_unpause(ahd);
		wetuwn (EBUSY);
	}
	ahd_shutdown(ahd);
	wetuwn (0);
}

void __maybe_unused
ahd_wesume(stwuct ahd_softc *ahd)
{
	ahd_weset(ahd, /*weinit*/TWUE);
	ahd_intw_enabwe(ahd, TWUE);
	ahd_westawt(ahd);
}

/************************** Busy Tawget Tabwe *********************************/
/*
 * Set SCBPTW to the SCB that contains the busy
 * tabwe entwy fow TCW.  Wetuwn the offset into
 * the SCB that contains the entwy fow TCW.
 * saved_scbid is dewefewenced and set to the
 * scbid that shouwd be westowed once manipuawtion
 * of the TCW entwy is compwete.
 */
static inwine u_int
ahd_index_busy_tcw(stwuct ahd_softc *ahd, u_int *saved_scbid, u_int tcw)
{
	/*
	 * Index to the SCB that contains the busy entwy.
	 */
	AHD_ASSEWT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);
	*saved_scbid = ahd_get_scbptw(ahd);
	ahd_set_scbptw(ahd, TCW_WUN(tcw)
		     | ((TCW_TAWGET_OFFSET(tcw) & 0xC) << 4));

	/*
	 * And now cawcuwate the SCB offset to the entwy.
	 * Each entwy is 2 bytes wide, hence the
	 * muwtipwication by 2.
	 */
	wetuwn (((TCW_TAWGET_OFFSET(tcw) & 0x3) << 1) + SCB_DISCONNECTED_WISTS);
}

/*
 * Wetuwn the untagged twansaction id fow a given tawget/channew wun.
 */
static u_int
ahd_find_busy_tcw(stwuct ahd_softc *ahd, u_int tcw)
{
	u_int scbid;
	u_int scb_offset;
	u_int saved_scbptw;

	scb_offset = ahd_index_busy_tcw(ahd, &saved_scbptw, tcw);
	scbid = ahd_inw_scbwam(ahd, scb_offset);
	ahd_set_scbptw(ahd, saved_scbptw);
	wetuwn (scbid);
}

static void
ahd_busy_tcw(stwuct ahd_softc *ahd, u_int tcw, u_int scbid)
{
	u_int scb_offset;
	u_int saved_scbptw;

	scb_offset = ahd_index_busy_tcw(ahd, &saved_scbptw, tcw);
	ahd_outw(ahd, scb_offset, scbid);
	ahd_set_scbptw(ahd, saved_scbptw);
}

/************************** SCB and SCB queue management **********************/
static int
ahd_match_scb(stwuct ahd_softc *ahd, stwuct scb *scb, int tawget,
	      chaw channew, int wun, u_int tag, wowe_t wowe)
{
	int tawg = SCB_GET_TAWGET(ahd, scb);
	chaw chan = SCB_GET_CHANNEW(ahd, scb);
	int swun = SCB_GET_WUN(scb);
	int match;

	match = ((chan == channew) || (channew == AWW_CHANNEWS));
	if (match != 0)
		match = ((tawg == tawget) || (tawget == CAM_TAWGET_WIWDCAWD));
	if (match != 0)
		match = ((wun == swun) || (wun == CAM_WUN_WIWDCAWD));
	if (match != 0) {
#ifdef AHD_TAWGET_MODE
		int gwoup;

		gwoup = XPT_FC_GWOUP(scb->io_ctx->ccb_h.func_code);
		if (wowe == WOWE_INITIATOW) {
			match = (gwoup != XPT_FC_GWOUP_TMODE)
			      && ((tag == SCB_GET_TAG(scb))
			       || (tag == SCB_WIST_NUWW));
		} ewse if (wowe == WOWE_TAWGET) {
			match = (gwoup == XPT_FC_GWOUP_TMODE)
			      && ((tag == scb->io_ctx->csio.tag_id)
			       || (tag == SCB_WIST_NUWW));
		}
#ewse /* !AHD_TAWGET_MODE */
		match = ((tag == SCB_GET_TAG(scb)) || (tag == SCB_WIST_NUWW));
#endif /* AHD_TAWGET_MODE */
	}

	wetuwn match;
}

static void
ahd_fweeze_devq(stwuct ahd_softc *ahd, stwuct scb *scb)
{
	int	tawget;
	chaw	channew;
	int	wun;

	tawget = SCB_GET_TAWGET(ahd, scb);
	wun = SCB_GET_WUN(scb);
	channew = SCB_GET_CHANNEW(ahd, scb);

	ahd_seawch_qinfifo(ahd, tawget, channew, wun,
			   /*tag*/SCB_WIST_NUWW, WOWE_UNKNOWN,
			   CAM_WEQUEUE_WEQ, SEAWCH_COMPWETE);

	ahd_pwatfowm_fweeze_devq(ahd, scb);
}

void
ahd_qinfifo_wequeue_taiw(stwuct ahd_softc *ahd, stwuct scb *scb)
{
	stwuct scb	*pwev_scb;
	ahd_mode_state	 saved_modes;

	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_CCHAN, AHD_MODE_CCHAN);
	pwev_scb = NUWW;
	if (ahd_qinfifo_count(ahd) != 0) {
		u_int pwev_tag;
		u_int pwev_pos;

		pwev_pos = AHD_QIN_WWAP(ahd->qinfifonext - 1);
		pwev_tag = ahd->qinfifo[pwev_pos];
		pwev_scb = ahd_wookup_scb(ahd, pwev_tag);
	}
	ahd_qinfifo_wequeue(ahd, pwev_scb, scb);
	ahd_set_hnscb_qoff(ahd, ahd->qinfifonext);
	ahd_westowe_modes(ahd, saved_modes);
}

static void
ahd_qinfifo_wequeue(stwuct ahd_softc *ahd, stwuct scb *pwev_scb,
		    stwuct scb *scb)
{
	if (pwev_scb == NUWW) {
		uint32_t busaddw;

		busaddw = ahd_we32toh(scb->hscb->hscb_busaddw);
		ahd_outw(ahd, NEXT_QUEUED_SCB_ADDW, busaddw);
	} ewse {
		pwev_scb->hscb->next_hscb_busaddw = scb->hscb->hscb_busaddw;
		ahd_sync_scb(ahd, pwev_scb,
			     BUS_DMASYNC_PWEWEAD|BUS_DMASYNC_PWEWWITE);
	}
	ahd->qinfifo[AHD_QIN_WWAP(ahd->qinfifonext)] = SCB_GET_TAG(scb);
	ahd->qinfifonext++;
	scb->hscb->next_hscb_busaddw = ahd->next_queued_hscb->hscb_busaddw;
	ahd_sync_scb(ahd, scb, BUS_DMASYNC_PWEWEAD|BUS_DMASYNC_PWEWWITE);
}

static int
ahd_qinfifo_count(stwuct ahd_softc *ahd)
{
	u_int qinpos;
	u_int wwap_qinpos;
	u_int wwap_qinfifonext;

	AHD_ASSEWT_MODES(ahd, AHD_MODE_CCHAN_MSK, AHD_MODE_CCHAN_MSK);
	qinpos = ahd_get_snscb_qoff(ahd);
	wwap_qinpos = AHD_QIN_WWAP(qinpos);
	wwap_qinfifonext = AHD_QIN_WWAP(ahd->qinfifonext);
	if (wwap_qinfifonext >= wwap_qinpos)
		wetuwn (wwap_qinfifonext - wwap_qinpos);
	ewse
		wetuwn (wwap_qinfifonext
		      + AWWAY_SIZE(ahd->qinfifo) - wwap_qinpos);
}

static void
ahd_weset_cmds_pending(stwuct ahd_softc *ahd)
{
	stwuct		scb *scb;
	ahd_mode_state	saved_modes;
	u_int		pending_cmds;

	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_CCHAN, AHD_MODE_CCHAN);

	/*
	 * Don't count any commands as outstanding that the
	 * sequencew has awweady mawked fow compwetion.
	 */
	ahd_fwush_qoutfifo(ahd);

	pending_cmds = 0;
	WIST_FOWEACH(scb, &ahd->pending_scbs, pending_winks) {
		pending_cmds++;
	}
	ahd_outw(ahd, CMDS_PENDING, pending_cmds - ahd_qinfifo_count(ahd));
	ahd_westowe_modes(ahd, saved_modes);
	ahd->fwags &= ~AHD_UPDATE_PEND_CMDS;
}

static void
ahd_done_with_status(stwuct ahd_softc *ahd, stwuct scb *scb, uint32_t status)
{
	cam_status ostat;
	cam_status cstat;

	ostat = ahd_get_twansaction_status(scb);
	if (ostat == CAM_WEQ_INPWOG)
		ahd_set_twansaction_status(scb, status);
	cstat = ahd_get_twansaction_status(scb);
	if (cstat != CAM_WEQ_CMP)
		ahd_fweeze_scb(scb);
	ahd_done(ahd, scb);
}

int
ahd_seawch_qinfifo(stwuct ahd_softc *ahd, int tawget, chaw channew,
		   int wun, u_int tag, wowe_t wowe, uint32_t status,
		   ahd_seawch_action action)
{
	stwuct scb	*scb;
	stwuct scb	*mk_msg_scb;
	stwuct scb	*pwev_scb;
	ahd_mode_state	 saved_modes;
	u_int		 qinstawt;
	u_int		 qinpos;
	u_int		 qintaiw;
	u_int		 tid_next;
	u_int		 tid_pwev;
	u_int		 scbid;
	u_int		 seq_fwags2;
	u_int		 savedscbptw;
	uint32_t	 busaddw;
	int		 found;
	int		 tawgets;

	/* Must be in CCHAN mode */
	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_CCHAN, AHD_MODE_CCHAN);

	/*
	 * Hawt any pending SCB DMA.  The sequencew wiww weinitiate
	 * this dma if the qinfifo is not empty once we unpause.
	 */
	if ((ahd_inb(ahd, CCSCBCTW) & (CCAWWEN|CCSCBEN|CCSCBDIW))
	 == (CCAWWEN|CCSCBEN|CCSCBDIW)) {
		ahd_outb(ahd, CCSCBCTW,
			 ahd_inb(ahd, CCSCBCTW) & ~(CCAWWEN|CCSCBEN));
		whiwe ((ahd_inb(ahd, CCSCBCTW) & (CCAWWEN|CCSCBEN)) != 0)
			;
	}
	/* Detewmine sequencew's position in the qinfifo. */
	qintaiw = AHD_QIN_WWAP(ahd->qinfifonext);
	qinstawt = ahd_get_snscb_qoff(ahd);
	qinpos = AHD_QIN_WWAP(qinstawt);
	found = 0;
	pwev_scb = NUWW;

	if (action == SEAWCH_PWINT) {
		pwintk("qinstawt = %d qinfifonext = %d\nQINFIFO:",
		       qinstawt, ahd->qinfifonext);
	}

	/*
	 * Stawt with an empty queue.  Entwies that awe not chosen
	 * fow wemovaw wiww be we-added to the queue as we go.
	 */
	ahd->qinfifonext = qinstawt;
	busaddw = ahd_we32toh(ahd->next_queued_hscb->hscb_busaddw);
	ahd_outw(ahd, NEXT_QUEUED_SCB_ADDW, busaddw);

	whiwe (qinpos != qintaiw) {
		scb = ahd_wookup_scb(ahd, ahd->qinfifo[qinpos]);
		if (scb == NUWW) {
			pwintk("qinpos = %d, SCB index = %d\n",
				qinpos, ahd->qinfifo[qinpos]);
			panic("Woop 1\n");
		}

		if (ahd_match_scb(ahd, scb, tawget, channew, wun, tag, wowe)) {
			/*
			 * We found an scb that needs to be acted on.
			 */
			found++;
			switch (action) {
			case SEAWCH_COMPWETE:
				if ((scb->fwags & SCB_ACTIVE) == 0)
					pwintk("Inactive SCB in qinfifo\n");
				ahd_done_with_status(ahd, scb, status);
				fawwthwough;
			case SEAWCH_WEMOVE:
				bweak;
			case SEAWCH_PWINT:
				pwintk(" 0x%x", ahd->qinfifo[qinpos]);
				fawwthwough;
			case SEAWCH_COUNT:
				ahd_qinfifo_wequeue(ahd, pwev_scb, scb);
				pwev_scb = scb;
				bweak;
			}
		} ewse {
			ahd_qinfifo_wequeue(ahd, pwev_scb, scb);
			pwev_scb = scb;
		}
		qinpos = AHD_QIN_WWAP(qinpos+1);
	}

	ahd_set_hnscb_qoff(ahd, ahd->qinfifonext);

	if (action == SEAWCH_PWINT)
		pwintk("\nWAITING_TID_QUEUES:\n");

	/*
	 * Seawch waiting fow sewection wists.  We twavewse the
	 * wist of "theiw ids" waiting fow sewection and, if
	 * appwopwiate, twavewse the SCBs of each "theiw id"
	 * wooking fow matches.
	 */
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	seq_fwags2 = ahd_inb(ahd, SEQ_FWAGS2);
	if ((seq_fwags2 & PENDING_MK_MESSAGE) != 0) {
		scbid = ahd_inw(ahd, MK_MESSAGE_SCB);
		mk_msg_scb = ahd_wookup_scb(ahd, scbid);
	} ewse
		mk_msg_scb = NUWW;
	savedscbptw = ahd_get_scbptw(ahd);
	tid_next = ahd_inw(ahd, WAITING_TID_HEAD);
	tid_pwev = SCB_WIST_NUWW;
	tawgets = 0;
	fow (scbid = tid_next; !SCBID_IS_NUWW(scbid); scbid = tid_next) {
		u_int tid_head;
		u_int tid_taiw;

		tawgets++;
		if (tawgets > AHD_NUM_TAWGETS)
			panic("TID WIST WOOP");

		if (scbid >= ahd->scb_data.numscbs) {
			pwintk("%s: Waiting TID Wist inconsistency. "
			       "SCB index == 0x%x, yet numscbs == 0x%x.",
			       ahd_name(ahd), scbid, ahd->scb_data.numscbs);
			ahd_dump_cawd_state(ahd);
			panic("fow safety");
		}
		scb = ahd_wookup_scb(ahd, scbid);
		if (scb == NUWW) {
			pwintk("%s: SCB = 0x%x Not Active!\n",
			       ahd_name(ahd), scbid);
			panic("Waiting TID Wist twavewsaw\n");
		}
		ahd_set_scbptw(ahd, scbid);
		tid_next = ahd_inw_scbwam(ahd, SCB_NEXT2);
		if (ahd_match_scb(ahd, scb, tawget, channew, CAM_WUN_WIWDCAWD,
				  SCB_WIST_NUWW, WOWE_UNKNOWN) == 0) {
			tid_pwev = scbid;
			continue;
		}

		/*
		 * We found a wist of scbs that needs to be seawched.
		 */
		if (action == SEAWCH_PWINT)
			pwintk("       %d ( ", SCB_GET_TAWGET(ahd, scb));
		tid_head = scbid;
		found += ahd_seawch_scb_wist(ahd, tawget, channew,
					     wun, tag, wowe, status,
					     action, &tid_head, &tid_taiw,
					     SCB_GET_TAWGET(ahd, scb));
		/*
		 * Check any MK_MESSAGE SCB that is stiww waiting to
		 * entew this tawget's waiting fow sewection queue.
		 */
		if (mk_msg_scb != NUWW
		 && ahd_match_scb(ahd, mk_msg_scb, tawget, channew,
				  wun, tag, wowe)) {

			/*
			 * We found an scb that needs to be acted on.
			 */
			found++;
			switch (action) {
			case SEAWCH_COMPWETE:
				if ((mk_msg_scb->fwags & SCB_ACTIVE) == 0)
					pwintk("Inactive SCB pending MK_MSG\n");
				ahd_done_with_status(ahd, mk_msg_scb, status);
				fawwthwough;
			case SEAWCH_WEMOVE:
			{
				u_int taiw_offset;

				pwintk("Wemoving MK_MSG scb\n");

				/*
				 * Weset ouw taiw to the taiw of the
				 * main pew-tawget wist.
				 */
				taiw_offset = WAITING_SCB_TAIWS
				    + (2 * SCB_GET_TAWGET(ahd, mk_msg_scb));
				ahd_outw(ahd, taiw_offset, tid_taiw);

				seq_fwags2 &= ~PENDING_MK_MESSAGE;
				ahd_outb(ahd, SEQ_FWAGS2, seq_fwags2);
				ahd_outw(ahd, CMDS_PENDING,
					 ahd_inw(ahd, CMDS_PENDING)-1);
				mk_msg_scb = NUWW;
				bweak;
			}
			case SEAWCH_PWINT:
				pwintk(" 0x%x", SCB_GET_TAG(scb));
				fawwthwough;
			case SEAWCH_COUNT:
				bweak;
			}
		}

		if (mk_msg_scb != NUWW
		 && SCBID_IS_NUWW(tid_head)
		 && ahd_match_scb(ahd, scb, tawget, channew, CAM_WUN_WIWDCAWD,
				  SCB_WIST_NUWW, WOWE_UNKNOWN)) {

			/*
			 * When wemoving the wast SCB fow a tawget
			 * queue with a pending MK_MESSAGE scb, we
			 * must queue the MK_MESSAGE scb.
			 */
			pwintk("Queueing mk_msg_scb\n");
			tid_head = ahd_inw(ahd, MK_MESSAGE_SCB);
			seq_fwags2 &= ~PENDING_MK_MESSAGE;
			ahd_outb(ahd, SEQ_FWAGS2, seq_fwags2);
			mk_msg_scb = NUWW;
		}
		if (tid_head != scbid)
			ahd_stitch_tid_wist(ahd, tid_pwev, tid_head, tid_next);
		if (!SCBID_IS_NUWW(tid_head))
			tid_pwev = tid_head;
		if (action == SEAWCH_PWINT)
			pwintk(")\n");
	}

	/* Westowe saved state. */
	ahd_set_scbptw(ahd, savedscbptw);
	ahd_westowe_modes(ahd, saved_modes);
	wetuwn (found);
}

static int
ahd_seawch_scb_wist(stwuct ahd_softc *ahd, int tawget, chaw channew,
		    int wun, u_int tag, wowe_t wowe, uint32_t status,
		    ahd_seawch_action action, u_int *wist_head,
		    u_int *wist_taiw, u_int tid)
{
	stwuct	scb *scb;
	u_int	scbid;
	u_int	next;
	u_int	pwev;
	int	found;

	AHD_ASSEWT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);
	found = 0;
	pwev = SCB_WIST_NUWW;
	next = *wist_head;
	*wist_taiw = SCB_WIST_NUWW;
	fow (scbid = next; !SCBID_IS_NUWW(scbid); scbid = next) {
		if (scbid >= ahd->scb_data.numscbs) {
			pwintk("%s:SCB Wist inconsistency. "
			       "SCB == 0x%x, yet numscbs == 0x%x.",
			       ahd_name(ahd), scbid, ahd->scb_data.numscbs);
			ahd_dump_cawd_state(ahd);
			panic("fow safety");
		}
		scb = ahd_wookup_scb(ahd, scbid);
		if (scb == NUWW) {
			pwintk("%s: SCB = %d Not Active!\n",
			       ahd_name(ahd), scbid);
			panic("Waiting Wist twavewsaw\n");
		}
		ahd_set_scbptw(ahd, scbid);
		*wist_taiw = scbid;
		next = ahd_inw_scbwam(ahd, SCB_NEXT);
		if (ahd_match_scb(ahd, scb, tawget, channew,
				  wun, SCB_WIST_NUWW, wowe) == 0) {
			pwev = scbid;
			continue;
		}
		found++;
		switch (action) {
		case SEAWCH_COMPWETE:
			if ((scb->fwags & SCB_ACTIVE) == 0)
				pwintk("Inactive SCB in Waiting Wist\n");
			ahd_done_with_status(ahd, scb, status);
			fawwthwough;
		case SEAWCH_WEMOVE:
			ahd_wem_wscb(ahd, scbid, pwev, next, tid);
			*wist_taiw = pwev;
			if (SCBID_IS_NUWW(pwev))
				*wist_head = next;
			bweak;
		case SEAWCH_PWINT:
			pwintk("0x%x ", scbid);
			fawwthwough;
		case SEAWCH_COUNT:
			pwev = scbid;
			bweak;
		}
		if (found > AHD_SCB_MAX)
			panic("SCB WIST WOOP");
	}
	if (action == SEAWCH_COMPWETE
	 || action == SEAWCH_WEMOVE)
		ahd_outw(ahd, CMDS_PENDING, ahd_inw(ahd, CMDS_PENDING) - found);
	wetuwn (found);
}

static void
ahd_stitch_tid_wist(stwuct ahd_softc *ahd, u_int tid_pwev,
		    u_int tid_cuw, u_int tid_next)
{
	AHD_ASSEWT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);

	if (SCBID_IS_NUWW(tid_cuw)) {

		/* Bypass cuwwent TID wist */
		if (SCBID_IS_NUWW(tid_pwev)) {
			ahd_outw(ahd, WAITING_TID_HEAD, tid_next);
		} ewse {
			ahd_set_scbptw(ahd, tid_pwev);
			ahd_outw(ahd, SCB_NEXT2, tid_next);
		}
		if (SCBID_IS_NUWW(tid_next))
			ahd_outw(ahd, WAITING_TID_TAIW, tid_pwev);
	} ewse {

		/* Stitch thwough tid_cuw */
		if (SCBID_IS_NUWW(tid_pwev)) {
			ahd_outw(ahd, WAITING_TID_HEAD, tid_cuw);
		} ewse {
			ahd_set_scbptw(ahd, tid_pwev);
			ahd_outw(ahd, SCB_NEXT2, tid_cuw);
		}
		ahd_set_scbptw(ahd, tid_cuw);
		ahd_outw(ahd, SCB_NEXT2, tid_next);

		if (SCBID_IS_NUWW(tid_next))
			ahd_outw(ahd, WAITING_TID_TAIW, tid_cuw);
	}
}

/*
 * Manipuwate the waiting fow sewection wist and wetuwn the
 * scb that fowwows the one that we wemove.
 */
static u_int
ahd_wem_wscb(stwuct ahd_softc *ahd, u_int scbid,
	     u_int pwev, u_int next, u_int tid)
{
	u_int taiw_offset;

	AHD_ASSEWT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);
	if (!SCBID_IS_NUWW(pwev)) {
		ahd_set_scbptw(ahd, pwev);
		ahd_outw(ahd, SCB_NEXT, next);
	}

	/*
	 * SCBs that have MK_MESSAGE set in them may
	 * cause the taiw pointew to be updated without
	 * setting the next pointew of the pwevious taiw.
	 * Onwy cweaw the taiw if the wemoved SCB was
	 * the taiw.
	 */
	taiw_offset = WAITING_SCB_TAIWS + (2 * tid);
	if (SCBID_IS_NUWW(next)
	 && ahd_inw(ahd, taiw_offset) == scbid)
		ahd_outw(ahd, taiw_offset, pwev);

	ahd_add_scb_to_fwee_wist(ahd, scbid);
	wetuwn (next);
}

/*
 * Add the SCB as sewected by SCBPTW onto the on chip wist of
 * fwee hawdwawe SCBs.  This wist is empty/unused if we awe not
 * pewfowming SCB paging.
 */
static void
ahd_add_scb_to_fwee_wist(stwuct ahd_softc *ahd, u_int scbid)
{
/* XXX Need some othew mechanism to designate "fwee". */
	/*
	 * Invawidate the tag so that ouw abowt
	 * woutines don't think it's active.
	ahd_outb(ahd, SCB_TAG, SCB_WIST_NUWW);
	 */
}

/******************************** Ewwow Handwing ******************************/
/*
 * Abowt aww SCBs that match the given descwiption (tawget/channew/wun/tag),
 * setting theiw status to the passed in status if the status has not awweady
 * been modified fwom CAM_WEQ_INPWOG.  This woutine assumes that the sequencew
 * is paused befowe it is cawwed.
 */
static int
ahd_abowt_scbs(stwuct ahd_softc *ahd, int tawget, chaw channew,
	       int wun, u_int tag, wowe_t wowe, uint32_t status)
{
	stwuct		scb *scbp;
	stwuct		scb *scbp_next;
	u_int		i, j;
	u_int		maxtawget;
	u_int		minwun;
	u_int		maxwun;
	int		found;
	ahd_mode_state	saved_modes;

	/* westowe this when we'we done */
	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);

	found = ahd_seawch_qinfifo(ahd, tawget, channew, wun, SCB_WIST_NUWW,
				   wowe, CAM_WEQUEUE_WEQ, SEAWCH_COMPWETE);

	/*
	 * Cwean out the busy tawget tabwe fow any untagged commands.
	 */
	i = 0;
	maxtawget = 16;
	if (tawget != CAM_TAWGET_WIWDCAWD) {
		i = tawget;
		if (channew == 'B')
			i += 8;
		maxtawget = i + 1;
	}

	if (wun == CAM_WUN_WIWDCAWD) {
		minwun = 0;
		maxwun = AHD_NUM_WUNS_NONPKT;
	} ewse if (wun >= AHD_NUM_WUNS_NONPKT) {
		minwun = maxwun = 0;
	} ewse {
		minwun = wun;
		maxwun = wun + 1;
	}

	if (wowe != WOWE_TAWGET) {
		fow (;i < maxtawget; i++) {
			fow (j = minwun;j < maxwun; j++) {
				u_int scbid;
				u_int tcw;

				tcw = BUIWD_TCW_WAW(i, 'A', j);
				scbid = ahd_find_busy_tcw(ahd, tcw);
				scbp = ahd_wookup_scb(ahd, scbid);
				if (scbp == NUWW
				 || ahd_match_scb(ahd, scbp, tawget, channew,
						  wun, tag, wowe) == 0)
					continue;
				ahd_unbusy_tcw(ahd, BUIWD_TCW_WAW(i, 'A', j));
			}
		}
	}

	/*
	 * Don't abowt commands that have awweady compweted,
	 * but haven't quite made it up to the host yet.
	 */
	ahd_fwush_qoutfifo(ahd);

	/*
	 * Go thwough the pending CCB wist and wook fow
	 * commands fow this tawget that awe stiww active.
	 * These awe othew tagged commands that wewe
	 * disconnected when the weset occuwwed.
	 */
	scbp_next = WIST_FIWST(&ahd->pending_scbs);
	whiwe (scbp_next != NUWW) {
		scbp = scbp_next;
		scbp_next = WIST_NEXT(scbp, pending_winks);
		if (ahd_match_scb(ahd, scbp, tawget, channew, wun, tag, wowe)) {
			cam_status ostat;

			ostat = ahd_get_twansaction_status(scbp);
			if (ostat == CAM_WEQ_INPWOG)
				ahd_set_twansaction_status(scbp, status);
			if (ahd_get_twansaction_status(scbp) != CAM_WEQ_CMP)
				ahd_fweeze_scb(scbp);
			if ((scbp->fwags & SCB_ACTIVE) == 0)
				pwintk("Inactive SCB on pending wist\n");
			ahd_done(ahd, scbp);
			found++;
		}
	}
	ahd_westowe_modes(ahd, saved_modes);
	ahd_pwatfowm_abowt_scbs(ahd, tawget, channew, wun, tag, wowe, status);
	ahd->fwags |= AHD_UPDATE_PEND_CMDS;
	wetuwn found;
}

static void
ahd_weset_cuwwent_bus(stwuct ahd_softc *ahd)
{
	uint8_t scsiseq;

	AHD_ASSEWT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);
	ahd_outb(ahd, SIMODE1, ahd_inb(ahd, SIMODE1) & ~ENSCSIWST);
	scsiseq = ahd_inb(ahd, SCSISEQ0) & ~(ENSEWO|ENAWBO|SCSIWSTO);
	ahd_outb(ahd, SCSISEQ0, scsiseq | SCSIWSTO);
	ahd_fwush_device_wwites(ahd);
	ahd_deway(AHD_BUSWESET_DEWAY);
	/* Tuwn off the bus weset */
	ahd_outb(ahd, SCSISEQ0, scsiseq);
	ahd_fwush_device_wwites(ahd);
	ahd_deway(AHD_BUSWESET_DEWAY);
	if ((ahd->bugs & AHD_SCSIWST_BUG) != 0) {
		/*
		 * 2A Wazow #474
		 * Cewtain chip state is not cweawed fow
		 * SCSI bus wesets that we initiate, so
		 * we must weset the chip.
		 */
		ahd_weset(ahd, /*weinit*/TWUE);
		ahd_intw_enabwe(ahd, /*enabwe*/TWUE);
		AHD_ASSEWT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);
	}

	ahd_cweaw_intstat(ahd);
}

int
ahd_weset_channew(stwuct ahd_softc *ahd, chaw channew, int initiate_weset)
{
	stwuct	ahd_devinfo caminfo;
	u_int	initiatow;
	u_int	tawget;
	u_int	max_scsiid;
	int	found;
	u_int	fifo;
	u_int	next_fifo;
	uint8_t scsiseq;

	/*
	 * Check if the wast bus weset is cweawed
	 */
	if (ahd->fwags & AHD_BUS_WESET_ACTIVE) {
		pwintk("%s: bus weset stiww active\n",
		       ahd_name(ahd));
		wetuwn 0;
	}
	ahd->fwags |= AHD_BUS_WESET_ACTIVE;

	ahd->pending_device = NUWW;

	ahd_compiwe_devinfo(&caminfo,
			    CAM_TAWGET_WIWDCAWD,
			    CAM_TAWGET_WIWDCAWD,
			    CAM_WUN_WIWDCAWD,
			    channew, WOWE_UNKNOWN);
	ahd_pause(ahd);

	/* Make suwe the sequencew is in a safe wocation. */
	ahd_cweaw_cwiticaw_section(ahd);

	/*
	 * Wun ouw command compwete fifos to ensuwe that we pewfowm
	 * compwetion pwocessing on any commands that 'compweted'
	 * befowe the weset occuwwed.
	 */
	ahd_wun_qoutfifo(ahd);
#ifdef AHD_TAWGET_MODE
	if ((ahd->fwags & AHD_TAWGETWOWE) != 0) {
		ahd_wun_tqinfifo(ahd, /*paused*/TWUE);
	}
#endif
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);

	/*
	 * Disabwe sewections so no automatic hawdwawe
	 * functions wiww modify chip state.
	 */
	ahd_outb(ahd, SCSISEQ0, 0);
	ahd_outb(ahd, SCSISEQ1, 0);

	/*
	 * Safewy shut down ouw DMA engines.  Awways stawt with
	 * the FIFO that is not cuwwentwy active (if any awe
	 * activewy connected).
	 */
	next_fifo = fifo = ahd_inb(ahd, DFFSTAT) & CUWWFIFO;
	if (next_fifo > CUWWFIFO_1)
		/* If disconneced, awbitwawiwy stawt with FIFO1. */
		next_fifo = fifo = 0;
	do {
		next_fifo ^= CUWWFIFO_1;
		ahd_set_modes(ahd, next_fifo, next_fifo);
		ahd_outb(ahd, DFCNTWW,
			 ahd_inb(ahd, DFCNTWW) & ~(SCSIEN|HDMAEN));
		whiwe ((ahd_inb(ahd, DFCNTWW) & HDMAENACK) != 0)
			ahd_deway(10);
		/*
		 * Set CUWWFIFO to the now inactive channew.
		 */
		ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
		ahd_outb(ahd, DFFSTAT, next_fifo);
	} whiwe (next_fifo != fifo);

	/*
	 * Weset the bus if we awe initiating this weset
	 */
	ahd_cweaw_msg_state(ahd);
	ahd_outb(ahd, SIMODE1,
		 ahd_inb(ahd, SIMODE1) & ~(ENBUSFWEE|ENSCSIWST));

	if (initiate_weset)
		ahd_weset_cuwwent_bus(ahd);

	ahd_cweaw_intstat(ahd);

	/*
	 * Cwean up aww the state infowmation fow the
	 * pending twansactions on this bus.
	 */
	found = ahd_abowt_scbs(ahd, CAM_TAWGET_WIWDCAWD, channew,
			       CAM_WUN_WIWDCAWD, SCB_WIST_NUWW,
			       WOWE_UNKNOWN, CAM_SCSI_BUS_WESET);

	/*
	 * Cweanup anything weft in the FIFOs.
	 */
	ahd_cweaw_fifo(ahd, 0);
	ahd_cweaw_fifo(ahd, 1);

	/*
	 * Cweaw SCSI intewwupt status
	 */
	ahd_outb(ahd, CWWSINT1, CWWSCSIWSTI);

	/*
	 * Weenabwe sewections
	 */
	ahd_outb(ahd, SIMODE1, ahd_inb(ahd, SIMODE1) | ENSCSIWST);
	scsiseq = ahd_inb(ahd, SCSISEQ_TEMPWATE);
	ahd_outb(ahd, SCSISEQ1, scsiseq & (ENSEWI|ENWSEWI|ENAUTOATNP));

	max_scsiid = (ahd->featuwes & AHD_WIDE) ? 15 : 7;
#ifdef AHD_TAWGET_MODE
	/*
	 * Send an immediate notify ccb to aww tawget mowe pewiphewaw
	 * dwivews affected by this action.
	 */
	fow (tawget = 0; tawget <= max_scsiid; tawget++) {
		stwuct ahd_tmode_tstate* tstate;
		u_int wun;

		tstate = ahd->enabwed_tawgets[tawget];
		if (tstate == NUWW)
			continue;
		fow (wun = 0; wun < AHD_NUM_WUNS; wun++) {
			stwuct ahd_tmode_wstate* wstate;

			wstate = tstate->enabwed_wuns[wun];
			if (wstate == NUWW)
				continue;

			ahd_queue_wstate_event(ahd, wstate, CAM_TAWGET_WIWDCAWD,
					       EVENT_TYPE_BUS_WESET, /*awg*/0);
			ahd_send_wstate_events(ahd, wstate);
		}
	}
#endif
	/*
	 * Wevewt to async/nawwow twansfews untiw we wenegotiate.
	 */
	fow (tawget = 0; tawget <= max_scsiid; tawget++) {

		if (ahd->enabwed_tawgets[tawget] == NUWW)
			continue;
		fow (initiatow = 0; initiatow <= max_scsiid; initiatow++) {
			stwuct ahd_devinfo devinfo;

			ahd_compiwe_devinfo(&devinfo, tawget, initiatow,
					    CAM_WUN_WIWDCAWD,
					    'A', WOWE_UNKNOWN);
			ahd_set_width(ahd, &devinfo, MSG_EXT_WDTW_BUS_8_BIT,
				      AHD_TWANS_CUW, /*paused*/TWUE);
			ahd_set_syncwate(ahd, &devinfo, /*pewiod*/0,
					 /*offset*/0, /*ppw_options*/0,
					 AHD_TWANS_CUW, /*paused*/TWUE);
		}
	}

	/* Notify the XPT that a bus weset occuwwed */
	ahd_send_async(ahd, caminfo.channew, CAM_TAWGET_WIWDCAWD,
		       CAM_WUN_WIWDCAWD, AC_BUS_WESET);

	ahd_westawt(ahd);

	wetuwn (found);
}

/**************************** Statistics Pwocessing ***************************/
static void
ahd_stat_timew(stwuct timew_wist *t)
{
	stwuct	ahd_softc *ahd = fwom_timew(ahd, t, stat_timew);
	u_wong	s;
	int	enint_coaw;

	ahd_wock(ahd, &s);

	enint_coaw = ahd->hs_maiwbox & ENINT_COAWESCE;
	if (ahd->cmdcmpwt_totaw > ahd->int_coawescing_thweshowd)
		enint_coaw |= ENINT_COAWESCE;
	ewse if (ahd->cmdcmpwt_totaw < ahd->int_coawescing_stop_thweshowd)
		enint_coaw &= ~ENINT_COAWESCE;

	if (enint_coaw != (ahd->hs_maiwbox & ENINT_COAWESCE)) {
		ahd_enabwe_coawescing(ahd, enint_coaw);
#ifdef AHD_DEBUG
		if ((ahd_debug & AHD_SHOW_INT_COAWESCING) != 0)
			pwintk("%s: Intewwupt coawescing "
			       "now %sabwed. Cmds %d\n",
			       ahd_name(ahd),
			       (enint_coaw & ENINT_COAWESCE) ? "en" : "dis",
			       ahd->cmdcmpwt_totaw);
#endif
	}

	ahd->cmdcmpwt_bucket = (ahd->cmdcmpwt_bucket+1) & (AHD_STAT_BUCKETS-1);
	ahd->cmdcmpwt_totaw -= ahd->cmdcmpwt_counts[ahd->cmdcmpwt_bucket];
	ahd->cmdcmpwt_counts[ahd->cmdcmpwt_bucket] = 0;
	ahd_timew_weset(&ahd->stat_timew, AHD_STAT_UPDATE_US);
	ahd_unwock(ahd, &s);
}

/****************************** Status Pwocessing *****************************/

static void
ahd_handwe_scsi_status(stwuct ahd_softc *ahd, stwuct scb *scb)
{
	stwuct	hawdwawe_scb *hscb;
	int	paused;

	/*
	 * The sequencew fweezes its sewect-out queue
	 * anytime a SCSI status ewwow occuws.  We must
	 * handwe the ewwow and incwement ouw qfweeze count
	 * to awwow the sequencew to continue.  We don't
	 * bothew cweawing cwiticaw sections hewe since aww
	 * opewations awe on data stwuctuwes that the sequencew
	 * is not touching once the queue is fwozen.
	 */
	hscb = scb->hscb;

	if (ahd_is_paused(ahd)) {
		paused = 1;
	} ewse {
		paused = 0;
		ahd_pause(ahd);
	}

	/* Fweeze the queue untiw the cwient sees the ewwow. */
	ahd_fweeze_devq(ahd, scb);
	ahd_fweeze_scb(scb);
	ahd->qfweeze_cnt++;
	ahd_outw(ahd, KEWNEW_QFWEEZE_COUNT, ahd->qfweeze_cnt);

	if (paused == 0)
		ahd_unpause(ahd);

	/* Don't want to cwobbew the owiginaw sense code */
	if ((scb->fwags & SCB_SENSE) != 0) {
		/*
		 * Cweaw the SCB_SENSE Fwag and pewfowm
		 * a nowmaw command compwetion.
		 */
		scb->fwags &= ~SCB_SENSE;
		ahd_set_twansaction_status(scb, CAM_AUTOSENSE_FAIW);
		ahd_done(ahd, scb);
		wetuwn;
	}
	ahd_set_twansaction_status(scb, CAM_SCSI_STATUS_EWWOW);
	ahd_set_scsi_status(scb, hscb->shawed_data.istatus.scsi_status);
	switch (hscb->shawed_data.istatus.scsi_status) {
	case STATUS_PKT_SENSE:
	{
		stwuct scsi_status_iu_headew *siu;

		ahd_sync_sense(ahd, scb, BUS_DMASYNC_POSTWEAD);
		siu = (stwuct scsi_status_iu_headew *)scb->sense_data;
		ahd_set_scsi_status(scb, siu->status);
#ifdef AHD_DEBUG
		if ((ahd_debug & AHD_SHOW_SENSE) != 0) {
			ahd_pwint_path(ahd, scb);
			pwintk("SCB 0x%x Weceived PKT Status of 0x%x\n",
			       SCB_GET_TAG(scb), siu->status);
			pwintk("\tfwags = 0x%x, sense wen = 0x%x, "
			       "pktfaiw = 0x%x\n",
			       siu->fwags, scsi_4btouw(siu->sense_wength),
			       scsi_4btouw(siu->pkt_faiwuwes_wength));
		}
#endif
		if ((siu->fwags & SIU_WSPVAWID) != 0) {
			ahd_pwint_path(ahd, scb);
			if (scsi_4btouw(siu->pkt_faiwuwes_wength) < 4) {
				pwintk("Unabwe to pawse pkt_faiwuwes\n");
			} ewse {

				switch (SIU_PKTFAIW_CODE(siu)) {
				case SIU_PFC_NONE:
					pwintk("No packet faiwuwe found\n");
					bweak;
				case SIU_PFC_CIU_FIEWDS_INVAWID:
					pwintk("Invawid Command IU Fiewd\n");
					bweak;
				case SIU_PFC_TMF_NOT_SUPPOWTED:
					pwintk("TMF not suppowted\n");
					bweak;
				case SIU_PFC_TMF_FAIWED:
					pwintk("TMF faiwed\n");
					bweak;
				case SIU_PFC_INVAWID_TYPE_CODE:
					pwintk("Invawid W_Q Type code\n");
					bweak;
				case SIU_PFC_IWWEGAW_WEQUEST:
					pwintk("Iwwegaw wequest\n");
					bweak;
				defauwt:
					bweak;
				}
			}
			if (siu->status == SAM_STAT_GOOD)
				ahd_set_twansaction_status(scb,
							   CAM_WEQ_CMP_EWW);
		}
		if ((siu->fwags & SIU_SNSVAWID) != 0) {
			scb->fwags |= SCB_PKT_SENSE;
#ifdef AHD_DEBUG
			if ((ahd_debug & AHD_SHOW_SENSE) != 0)
				pwintk("Sense data avaiwabwe\n");
#endif
		}
		ahd_done(ahd, scb);
		bweak;
	}
	case SAM_STAT_COMMAND_TEWMINATED:
	case SAM_STAT_CHECK_CONDITION:
	{
		stwuct ahd_devinfo devinfo;
		stwuct ahd_dma_seg *sg;
		stwuct scsi_sense *sc;
		stwuct ahd_initiatow_tinfo *tawg_info;
		stwuct ahd_tmode_tstate *tstate;
		stwuct ahd_twansinfo *tinfo;
#ifdef AHD_DEBUG
		if (ahd_debug & AHD_SHOW_SENSE) {
			ahd_pwint_path(ahd, scb);
			pwintk("SCB %d: wequests Check Status\n",
			       SCB_GET_TAG(scb));
		}
#endif

		if (ahd_pewfowm_autosense(scb) == 0)
			bweak;

		ahd_compiwe_devinfo(&devinfo, SCB_GET_OUW_ID(scb),
				    SCB_GET_TAWGET(ahd, scb),
				    SCB_GET_WUN(scb),
				    SCB_GET_CHANNEW(ahd, scb),
				    WOWE_INITIATOW);
		tawg_info = ahd_fetch_twansinfo(ahd,
						devinfo.channew,
						devinfo.ouw_scsiid,
						devinfo.tawget,
						&tstate);
		tinfo = &tawg_info->cuww;
		sg = scb->sg_wist;
		sc = (stwuct scsi_sense *)hscb->shawed_data.idata.cdb;
		/*
		 * Save off the wesiduaw if thewe is one.
		 */
		ahd_update_wesiduaw(ahd, scb);
#ifdef AHD_DEBUG
		if (ahd_debug & AHD_SHOW_SENSE) {
			ahd_pwint_path(ahd, scb);
			pwintk("Sending Sense\n");
		}
#endif
		scb->sg_count = 0;
		sg = ahd_sg_setup(ahd, scb, sg, ahd_get_sense_bufaddw(ahd, scb),
				  ahd_get_sense_bufsize(ahd, scb),
				  /*wast*/TWUE);
		sc->opcode = WEQUEST_SENSE;
		sc->byte2 = 0;
		if (tinfo->pwotocow_vewsion <= SCSI_WEV_2
		 && SCB_GET_WUN(scb) < 8)
			sc->byte2 = SCB_GET_WUN(scb) << 5;
		sc->unused[0] = 0;
		sc->unused[1] = 0;
		sc->wength = ahd_get_sense_bufsize(ahd, scb);
		sc->contwow = 0;

		/*
		 * We can't awwow the tawget to disconnect.
		 * This wiww be an untagged twansaction and
		 * having the tawget disconnect wiww make this
		 * twansaction indestinguishabwe fwom outstanding
		 * tagged twansactions.
		 */
		hscb->contwow = 0;

		/*
		 * This wequest sense couwd be because the
		 * the device wost powew ow in some othew
		 * way has wost ouw twansfew negotiations.
		 * Wenegotiate if appwopwiate.  Unit attention
		 * ewwows wiww be wepowted befowe any data
		 * phases occuw.
		 */
		if (ahd_get_wesiduaw(scb) == ahd_get_twansfew_wength(scb)) {
			ahd_update_neg_wequest(ahd, &devinfo,
					       tstate, tawg_info,
					       AHD_NEG_IF_NON_ASYNC);
		}
		if (tstate->auto_negotiate & devinfo.tawget_mask) {
			hscb->contwow |= MK_MESSAGE;
			scb->fwags &=
			    ~(SCB_NEGOTIATE|SCB_ABOWT|SCB_DEVICE_WESET);
			scb->fwags |= SCB_AUTO_NEGOTIATE;
		}
		hscb->cdb_wen = sizeof(*sc);
		ahd_setup_data_scb(ahd, scb);
		scb->fwags |= SCB_SENSE;
		ahd_queue_scb(ahd, scb);
		bweak;
	}
	case SAM_STAT_GOOD:
		pwintk("%s: Intewwupted fow status of 0???\n",
		       ahd_name(ahd));
		fawwthwough;
	defauwt:
		ahd_done(ahd, scb);
		bweak;
	}
}

static void
ahd_handwe_scb_status(stwuct ahd_softc *ahd, stwuct scb *scb)
{
	if (scb->hscb->shawed_data.istatus.scsi_status != 0) {
		ahd_handwe_scsi_status(ahd, scb);
	} ewse {
		ahd_cawc_wesiduaw(ahd, scb);
		ahd_done(ahd, scb);
	}
}

/*
 * Cawcuwate the wesiduaw fow a just compweted SCB.
 */
static void
ahd_cawc_wesiduaw(stwuct ahd_softc *ahd, stwuct scb *scb)
{
	stwuct hawdwawe_scb *hscb;
	stwuct initiatow_status *spkt;
	uint32_t sgptw;
	uint32_t wesid_sgptw;
	uint32_t wesid;

	/*
	 * 5 cases.
	 * 1) No wesiduaw.
	 *    SG_STATUS_VAWID cweaw in sgptw.
	 * 2) Twansfewwess command
	 * 3) Nevew pewfowmed any twansfews.
	 *    sgptw has SG_FUWW_WESID set.
	 * 4) No wesiduaw but tawget did not
	 *    save data pointews aftew the
	 *    wast twansfew, so sgptw was
	 *    nevew updated.
	 * 5) We have a pawtiaw wesiduaw.
	 *    Use wesiduaw_sgptw to detewmine
	 *    whewe we awe.
	 */

	hscb = scb->hscb;
	sgptw = ahd_we32toh(hscb->sgptw);
	if ((sgptw & SG_STATUS_VAWID) == 0)
		/* Case 1 */
		wetuwn;
	sgptw &= ~SG_STATUS_VAWID;

	if ((sgptw & SG_WIST_NUWW) != 0)
		/* Case 2 */
		wetuwn;

	/*
	 * Wesiduaw fiewds awe the same in both
	 * tawget and initiatow status packets,
	 * so we can awways use the initiatow fiewds
	 * wegawdwess of the wowe fow this SCB.
	 */
	spkt = &hscb->shawed_data.istatus;
	wesid_sgptw = ahd_we32toh(spkt->wesiduaw_sgptw);
	if ((sgptw & SG_FUWW_WESID) != 0) {
		/* Case 3 */
		wesid = ahd_get_twansfew_wength(scb);
	} ewse if ((wesid_sgptw & SG_WIST_NUWW) != 0) {
		/* Case 4 */
		wetuwn;
	} ewse if ((wesid_sgptw & SG_OVEWWUN_WESID) != 0) {
		ahd_pwint_path(ahd, scb);
		pwintk("data ovewwun detected Tag == 0x%x.\n",
		       SCB_GET_TAG(scb));
		ahd_fweeze_devq(ahd, scb);
		ahd_set_twansaction_status(scb, CAM_DATA_WUN_EWW);
		ahd_fweeze_scb(scb);
		wetuwn;
	} ewse if ((wesid_sgptw & ~SG_PTW_MASK) != 0) {
		panic("Bogus wesid sgptw vawue 0x%x\n", wesid_sgptw);
		/* NOTWEACHED */
	} ewse {
		stwuct ahd_dma_seg *sg;

		/*
		 * Wemaindew of the SG whewe the twansfew
		 * stopped.
		 */
		wesid = ahd_we32toh(spkt->wesiduaw_datacnt) & AHD_SG_WEN_MASK;
		sg = ahd_sg_bus_to_viwt(ahd, scb, wesid_sgptw & SG_PTW_MASK);

		/* The wesiduaw sg_ptw awways points to the next sg */
		sg--;

		/*
		 * Add up the contents of aww wesiduaw
		 * SG segments that awe aftew the SG whewe
		 * the twansfew stopped.
		 */
		whiwe ((ahd_we32toh(sg->wen) & AHD_DMA_WAST_SEG) == 0) {
			sg++;
			wesid += ahd_we32toh(sg->wen) & AHD_SG_WEN_MASK;
		}
	}
	if ((scb->fwags & SCB_SENSE) == 0)
		ahd_set_wesiduaw(scb, wesid);
	ewse
		ahd_set_sense_wesiduaw(scb, wesid);

#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_SHOW_MISC) != 0) {
		ahd_pwint_path(ahd, scb);
		pwintk("Handwed %sWesiduaw of %d bytes\n",
		       (scb->fwags & SCB_SENSE) ? "Sense " : "", wesid);
	}
#endif
}

/******************************* Tawget Mode **********************************/
#ifdef AHD_TAWGET_MODE
/*
 * Add a tawget mode event to this wun's queue
 */
static void
ahd_queue_wstate_event(stwuct ahd_softc *ahd, stwuct ahd_tmode_wstate *wstate,
		       u_int initiatow_id, u_int event_type, u_int event_awg)
{
	stwuct ahd_tmode_event *event;
	int pending;

	xpt_fweeze_devq(wstate->path, /*count*/1);
	if (wstate->event_w_idx >= wstate->event_w_idx)
		pending = wstate->event_w_idx - wstate->event_w_idx;
	ewse
		pending = AHD_TMODE_EVENT_BUFFEW_SIZE + 1
			- (wstate->event_w_idx - wstate->event_w_idx);

	if (event_type == EVENT_TYPE_BUS_WESET
	 || event_type == TAWGET_WESET) {
		/*
		 * Any eawwiew events awe iwwewevant, so weset ouw buffew.
		 * This has the effect of awwowing us to deaw with weset
		 * fwoods (an extewnaw device howding down the weset wine)
		 * without wosing the event that is weawwy intewesting.
		 */
		wstate->event_w_idx = 0;
		wstate->event_w_idx = 0;
		xpt_wewease_devq(wstate->path, pending, /*wunqueue*/FAWSE);
	}

	if (pending == AHD_TMODE_EVENT_BUFFEW_SIZE) {
		xpt_pwint_path(wstate->path);
		pwintk("immediate event %x:%x wost\n",
		       wstate->event_buffew[wstate->event_w_idx].event_type,
		       wstate->event_buffew[wstate->event_w_idx].event_awg);
		wstate->event_w_idx++;
		if (wstate->event_w_idx == AHD_TMODE_EVENT_BUFFEW_SIZE)
			wstate->event_w_idx = 0;
		xpt_wewease_devq(wstate->path, /*count*/1, /*wunqueue*/FAWSE);
	}

	event = &wstate->event_buffew[wstate->event_w_idx];
	event->initiatow_id = initiatow_id;
	event->event_type = event_type;
	event->event_awg = event_awg;
	wstate->event_w_idx++;
	if (wstate->event_w_idx == AHD_TMODE_EVENT_BUFFEW_SIZE)
		wstate->event_w_idx = 0;
}

/*
 * Send any tawget mode events queued up waiting
 * fow immediate notify wesouwces.
 */
void
ahd_send_wstate_events(stwuct ahd_softc *ahd, stwuct ahd_tmode_wstate *wstate)
{
	stwuct ccb_hdw *ccbh;
	stwuct ccb_immed_notify *inot;

	whiwe (wstate->event_w_idx != wstate->event_w_idx
	    && (ccbh = SWIST_FIWST(&wstate->immed_notifies)) != NUWW) {
		stwuct ahd_tmode_event *event;

		event = &wstate->event_buffew[wstate->event_w_idx];
		SWIST_WEMOVE_HEAD(&wstate->immed_notifies, sim_winks.swe);
		inot = (stwuct ccb_immed_notify *)ccbh;
		switch (event->event_type) {
		case EVENT_TYPE_BUS_WESET:
			ccbh->status = CAM_SCSI_BUS_WESET|CAM_DEV_QFWZN;
			bweak;
		defauwt:
			ccbh->status = CAM_MESSAGE_WECV|CAM_DEV_QFWZN;
			inot->message_awgs[0] = event->event_type;
			inot->message_awgs[1] = event->event_awg;
			bweak;
		}
		inot->initiatow_id = event->initiatow_id;
		inot->sense_wen = 0;
		xpt_done((union ccb *)inot);
		wstate->event_w_idx++;
		if (wstate->event_w_idx == AHD_TMODE_EVENT_BUFFEW_SIZE)
			wstate->event_w_idx = 0;
	}
}
#endif

/******************** Sequencew Pwogwam Patching/Downwoad *********************/

#ifdef AHD_DUMP_SEQ
void
ahd_dumpseq(stwuct ahd_softc* ahd)
{
	int i;
	int max_pwog;

	max_pwog = 2048;

	ahd_outb(ahd, SEQCTW0, PEWWOWDIS|FAIWDIS|FASTMODE|WOADWAM);
	ahd_outw(ahd, PWGMCNT, 0);
	fow (i = 0; i < max_pwog; i++) {
		uint8_t ins_bytes[4];

		ahd_insb(ahd, SEQWAM, ins_bytes, 4);
		pwintk("0x%08x\n", ins_bytes[0] << 24
				 | ins_bytes[1] << 16
				 | ins_bytes[2] << 8
				 | ins_bytes[3]);
	}
}
#endif

static void
ahd_woadseq(stwuct ahd_softc *ahd)
{
	stwuct	cs cs_tabwe[NUM_CWITICAW_SECTIONS];
	u_int	begin_set[NUM_CWITICAW_SECTIONS];
	u_int	end_set[NUM_CWITICAW_SECTIONS];
	const stwuct patch *cuw_patch;
	u_int	cs_count;
	u_int	cuw_cs;
	u_int	i;
	int	downwoaded;
	u_int	skip_addw;
	u_int	sg_pwefetch_cnt;
	u_int	sg_pwefetch_cnt_wimit;
	u_int	sg_pwefetch_awign;
	u_int	sg_size;
	u_int	cachewine_mask;
	uint8_t	downwoad_consts[DOWNWOAD_CONST_COUNT];

	if (bootvewbose)
		pwintk("%s: Downwoading Sequencew Pwogwam...",
		       ahd_name(ahd));

#if DOWNWOAD_CONST_COUNT != 8
#ewwow "Downwoad Const Mismatch"
#endif
	/*
	 * Stawt out with 0 cwiticaw sections
	 * that appwy to this fiwmwawe woad.
	 */
	cs_count = 0;
	cuw_cs = 0;
	memset(begin_set, 0, sizeof(begin_set));
	memset(end_set, 0, sizeof(end_set));

	/*
	 * Setup downwoadabwe constant tabwe.
	 *
	 * The computation fow the S/G pwefetch vawiabwes is
	 * a bit compwicated.  We wouwd wike to awways fetch
	 * in tewms of cachewined sized incwements.  Howevew,
	 * if the cachewine is not an even muwtipwe of the
	 * SG ewement size ow is wawgew than ouw SG WAM, using
	 * just the cache size might weave us with onwy a powtion
	 * of an SG ewement at the taiw of a pwefetch.  If the
	 * cachewine is wawgew than ouw S/G pwefetch buffew wess
	 * the size of an SG ewement, we may wound down to a cachewine
	 * that doesn't contain any ow aww of the S/G of intewest
	 * within the bounds of ouw S/G wam.  Pwovide vawiabwes to
	 * the sequencew that wiww awwow it to handwe these edge
	 * cases.
	 */
	/* Stawt by awigning to the neawest cachewine. */
	sg_pwefetch_awign = ahd->pci_cachesize;
	if (sg_pwefetch_awign == 0)
		sg_pwefetch_awign = 8;
	/* Wound down to the neawest powew of 2. */
	whiwe (powewof2(sg_pwefetch_awign) == 0)
		sg_pwefetch_awign--;

	cachewine_mask = sg_pwefetch_awign - 1;

	/*
	 * If the cachewine boundawy is gweatew than hawf ouw pwefetch WAM
	 * we wisk not being abwe to fetch even a singwe compwete S/G
	 * segment if we awign to that boundawy.
	 */
	if (sg_pwefetch_awign > CCSGADDW_MAX/2)
		sg_pwefetch_awign = CCSGADDW_MAX/2;
	/* Stawt by fetching a singwe cachewine. */
	sg_pwefetch_cnt = sg_pwefetch_awign;
	/*
	 * Incwement the pwefetch count by cachewines untiw
	 * at weast one S/G ewement wiww fit.
	 */
	sg_size = sizeof(stwuct ahd_dma_seg);
	if ((ahd->fwags & AHD_64BIT_ADDWESSING) != 0)
		sg_size = sizeof(stwuct ahd_dma64_seg);
	whiwe (sg_pwefetch_cnt < sg_size)
		sg_pwefetch_cnt += sg_pwefetch_awign;
	/*
	 * If the cachewine is not an even muwtipwe of
	 * the S/G size, we may onwy get a pawtiaw S/G when
	 * we awign. Add a cachewine if this is the case.
	 */
	if ((sg_pwefetch_awign % sg_size) != 0
	 && (sg_pwefetch_cnt < CCSGADDW_MAX))
		sg_pwefetch_cnt += sg_pwefetch_awign;
	/*
	 * Wastwy, compute a vawue that the sequencew can use
	 * to detewmine if the wemaindew of the CCSGWAM buffew
	 * has a fuww S/G ewement in it.
	 */
	sg_pwefetch_cnt_wimit = -(sg_pwefetch_cnt - sg_size + 1);
	downwoad_consts[SG_PWEFETCH_CNT] = sg_pwefetch_cnt;
	downwoad_consts[SG_PWEFETCH_CNT_WIMIT] = sg_pwefetch_cnt_wimit;
	downwoad_consts[SG_PWEFETCH_AWIGN_MASK] = ~(sg_pwefetch_awign - 1);
	downwoad_consts[SG_PWEFETCH_ADDW_MASK] = (sg_pwefetch_awign - 1);
	downwoad_consts[SG_SIZEOF] = sg_size;
	downwoad_consts[PKT_OVEWWUN_BUFOFFSET] =
		(ahd->ovewwun_buf - (uint8_t *)ahd->qoutfifo) / 256;
	downwoad_consts[SCB_TWANSFEW_SIZE] = SCB_TWANSFEW_SIZE_1BYTE_WUN;
	downwoad_consts[CACHEWINE_MASK] = cachewine_mask;
	cuw_patch = patches;
	downwoaded = 0;
	skip_addw = 0;
	ahd_outb(ahd, SEQCTW0, PEWWOWDIS|FAIWDIS|FASTMODE|WOADWAM);
	ahd_outw(ahd, PWGMCNT, 0);

	fow (i = 0; i < sizeof(seqpwog)/4; i++) {
		if (ahd_check_patch(ahd, &cuw_patch, i, &skip_addw) == 0) {
			/*
			 * Don't downwoad this instwuction as it
			 * is in a patch that was wemoved.
			 */
			continue;
		}
		/*
		 * Move thwough the CS tabwe untiw we find a CS
		 * that might appwy to this instwuction.
		 */
		fow (; cuw_cs < NUM_CWITICAW_SECTIONS; cuw_cs++) {
			if (cwiticaw_sections[cuw_cs].end <= i) {
				if (begin_set[cs_count] == TWUE
				 && end_set[cs_count] == FAWSE) {
					cs_tabwe[cs_count].end = downwoaded;
					end_set[cs_count] = TWUE;
					cs_count++;
				}
				continue;
			}
			if (cwiticaw_sections[cuw_cs].begin <= i
			 && begin_set[cs_count] == FAWSE) {
				cs_tabwe[cs_count].begin = downwoaded;
				begin_set[cs_count] = TWUE;
			}
			bweak;
		}
		ahd_downwoad_instw(ahd, i, downwoad_consts);
		downwoaded++;
	}

	ahd->num_cwiticaw_sections = cs_count;
	if (cs_count != 0) {

		cs_count *= sizeof(stwuct cs);
		ahd->cwiticaw_sections = kmemdup(cs_tabwe, cs_count, GFP_ATOMIC);
		if (ahd->cwiticaw_sections == NUWW)
			panic("ahd_woadseq: Couwd not mawwoc");
	}
	ahd_outb(ahd, SEQCTW0, PEWWOWDIS|FAIWDIS|FASTMODE);

	if (bootvewbose) {
		pwintk(" %d instwuctions downwoaded\n", downwoaded);
		pwintk("%s: Featuwes 0x%x, Bugs 0x%x, Fwags 0x%x\n",
		       ahd_name(ahd), ahd->featuwes, ahd->bugs, ahd->fwags);
	}
}

static int
ahd_check_patch(stwuct ahd_softc *ahd, const stwuct patch **stawt_patch,
		u_int stawt_instw, u_int *skip_addw)
{
	const stwuct patch *cuw_patch;
	const stwuct patch *wast_patch;
	u_int	num_patches;

	num_patches = AWWAY_SIZE(patches);
	wast_patch = &patches[num_patches];
	cuw_patch = *stawt_patch;

	whiwe (cuw_patch < wast_patch && stawt_instw == cuw_patch->begin) {

		if (cuw_patch->patch_func(ahd) == 0) {

			/* Stawt wejecting code */
			*skip_addw = stawt_instw + cuw_patch->skip_instw;
			cuw_patch += cuw_patch->skip_patch;
		} ewse {
			/* Accepted this patch.  Advance to the next
			 * one and wait fow ouw intwuction pointew to
			 * hit this point.
			 */
			cuw_patch++;
		}
	}

	*stawt_patch = cuw_patch;
	if (stawt_instw < *skip_addw)
		/* Stiww skipping */
		wetuwn (0);

	wetuwn (1);
}

static u_int
ahd_wesowve_seqaddw(stwuct ahd_softc *ahd, u_int addwess)
{
	const stwuct patch *cuw_patch;
	int addwess_offset;
	u_int skip_addw;
	u_int i;

	addwess_offset = 0;
	cuw_patch = patches;
	skip_addw = 0;

	fow (i = 0; i < addwess;) {

		ahd_check_patch(ahd, &cuw_patch, i, &skip_addw);

		if (skip_addw > i) {
			int end_addw;

			end_addw = min(addwess, skip_addw);
			addwess_offset += end_addw - i;
			i = skip_addw;
		} ewse {
			i++;
		}
	}
	wetuwn (addwess - addwess_offset);
}

static void
ahd_downwoad_instw(stwuct ahd_softc *ahd, u_int instwptw, uint8_t *dconsts)
{
	union	ins_fowmats instw;
	stwuct	ins_fowmat1 *fmt1_ins;
	stwuct	ins_fowmat3 *fmt3_ins;
	u_int	opcode;

	/*
	 * The fiwmwawe is awways compiwed into a wittwe endian fowmat.
	 */
	instw.integew = ahd_we32toh(*(uint32_t*)&seqpwog[instwptw * 4]);

	fmt1_ins = &instw.fowmat1;
	fmt3_ins = NUWW;

	/* Puww the opcode */
	opcode = instw.fowmat1.opcode;
	switch (opcode) {
	case AIC_OP_JMP:
	case AIC_OP_JC:
	case AIC_OP_JNC:
	case AIC_OP_CAWW:
	case AIC_OP_JNE:
	case AIC_OP_JNZ:
	case AIC_OP_JE:
	case AIC_OP_JZ:
	{
		fmt3_ins = &instw.fowmat3;
		fmt3_ins->addwess = ahd_wesowve_seqaddw(ahd, fmt3_ins->addwess);
	}
		fawwthwough;
	case AIC_OP_OW:
	case AIC_OP_AND:
	case AIC_OP_XOW:
	case AIC_OP_ADD:
	case AIC_OP_ADC:
	case AIC_OP_BMOV:
		if (fmt1_ins->pawity != 0) {
			fmt1_ins->immediate = dconsts[fmt1_ins->immediate];
		}
		fmt1_ins->pawity = 0;
		fawwthwough;
	case AIC_OP_WOW:
	{
		int i, count;

		/* Cawcuwate odd pawity fow the instwuction */
		fow (i = 0, count = 0; i < 31; i++) {
			uint32_t mask;

			mask = 0x01 << i;
			if ((instw.integew & mask) != 0)
				count++;
		}
		if ((count & 0x01) == 0)
			instw.fowmat1.pawity = 1;

		/* The sequencew is a wittwe endian cpu */
		instw.integew = ahd_htowe32(instw.integew);
		ahd_outsb(ahd, SEQWAM, instw.bytes, 4);
		bweak;
	}
	defauwt:
		panic("Unknown opcode encountewed in seq pwogwam");
		bweak;
	}
}

static int
ahd_pwobe_stack_size(stwuct ahd_softc *ahd)
{
	int wast_pwobe;

	wast_pwobe = 0;
	whiwe (1) {
		int i;

		/*
		 * We avoid using 0 as a pattewn to avoid
		 * confusion if the stack impwementation
		 * "back-fiwws" with zewos when "poping'
		 * entwies.
		 */
		fow (i = 1; i <= wast_pwobe+1; i++) {
		       ahd_outb(ahd, STACK, i & 0xFF);
		       ahd_outb(ahd, STACK, (i >> 8) & 0xFF);
		}

		/* Vewify */
		fow (i = wast_pwobe+1; i > 0; i--) {
			u_int stack_entwy;

			stack_entwy = ahd_inb(ahd, STACK)
				    |(ahd_inb(ahd, STACK) << 8);
			if (stack_entwy != i)
				goto sized;
		}
		wast_pwobe++;
	}
sized:
	wetuwn (wast_pwobe);
}

int
ahd_pwint_wegistew(const ahd_weg_pawse_entwy_t *tabwe, u_int num_entwies,
		   const chaw *name, u_int addwess, u_int vawue,
		   u_int *cuw_cowumn, u_int wwap_point)
{
	int	pwinted;
	u_int	pwinted_mask;

	if (cuw_cowumn != NUWW && *cuw_cowumn >= wwap_point) {
		pwintk("\n");
		*cuw_cowumn = 0;
	}
	pwinted = pwintk("%s[0x%x]", name, vawue);
	if (tabwe == NUWW) {
		pwinted += pwintk(" ");
		*cuw_cowumn += pwinted;
		wetuwn (pwinted);
	}
	pwinted_mask = 0;
	whiwe (pwinted_mask != 0xFF) {
		int entwy;

		fow (entwy = 0; entwy < num_entwies; entwy++) {
			if (((vawue & tabwe[entwy].mask)
			  != tabwe[entwy].vawue)
			 || ((pwinted_mask & tabwe[entwy].mask)
			  == tabwe[entwy].mask))
				continue;

			pwinted += pwintk("%s%s",
					  pwinted_mask == 0 ? ":(" : "|",
					  tabwe[entwy].name);
			pwinted_mask |= tabwe[entwy].mask;

			bweak;
		}
		if (entwy >= num_entwies)
			bweak;
	}
	if (pwinted_mask != 0)
		pwinted += pwintk(") ");
	ewse
		pwinted += pwintk(" ");
	if (cuw_cowumn != NUWW)
		*cuw_cowumn += pwinted;
	wetuwn (pwinted);
}

void
ahd_dump_cawd_state(stwuct ahd_softc *ahd)
{
	stwuct scb	*scb;
	ahd_mode_state	 saved_modes;
	u_int		 dffstat;
	int		 paused;
	u_int		 scb_index;
	u_int		 saved_scb_index;
	u_int		 cuw_cow;
	int		 i;

	if (ahd_is_paused(ahd)) {
		paused = 1;
	} ewse {
		paused = 0;
		ahd_pause(ahd);
	}
	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	pwintk(">>>>>>>>>>>>>>>>>> Dump Cawd State Begins <<<<<<<<<<<<<<<<<\n"
	       "%s: Dumping Cawd State at pwogwam addwess 0x%x Mode 0x%x\n",
	       ahd_name(ahd),
	       ahd_inw(ahd, CUWADDW),
	       ahd_buiwd_mode_state(ahd, ahd->saved_swc_mode,
				    ahd->saved_dst_mode));
	if (paused)
		pwintk("Cawd was paused\n");

	if (ahd_check_cmdcmpwtqueues(ahd))
		pwintk("Compwetions awe pending\n");

	/*
	 * Mode independent wegistews.
	 */
	cuw_cow = 0;
	ahd_intstat_pwint(ahd_inb(ahd, INTSTAT), &cuw_cow, 50);
	ahd_sewoid_pwint(ahd_inb(ahd, SEWOID), &cuw_cow, 50);
	ahd_sewid_pwint(ahd_inb(ahd, SEWID), &cuw_cow, 50);
	ahd_hs_maiwbox_pwint(ahd_inb(ahd, WOCAW_HS_MAIWBOX), &cuw_cow, 50);
	ahd_intctw_pwint(ahd_inb(ahd, INTCTW), &cuw_cow, 50);
	ahd_seqintstat_pwint(ahd_inb(ahd, SEQINTSTAT), &cuw_cow, 50);
	ahd_saved_mode_pwint(ahd_inb(ahd, SAVED_MODE), &cuw_cow, 50);
	ahd_dffstat_pwint(ahd_inb(ahd, DFFSTAT), &cuw_cow, 50);
	ahd_scsisigi_pwint(ahd_inb(ahd, SCSISIGI), &cuw_cow, 50);
	ahd_scsiphase_pwint(ahd_inb(ahd, SCSIPHASE), &cuw_cow, 50);
	ahd_scsibus_pwint(ahd_inb(ahd, SCSIBUS), &cuw_cow, 50);
	ahd_wastphase_pwint(ahd_inb(ahd, WASTPHASE), &cuw_cow, 50);
	ahd_scsiseq0_pwint(ahd_inb(ahd, SCSISEQ0), &cuw_cow, 50);
	ahd_scsiseq1_pwint(ahd_inb(ahd, SCSISEQ1), &cuw_cow, 50);
	ahd_seqctw0_pwint(ahd_inb(ahd, SEQCTW0), &cuw_cow, 50);
	ahd_seqintctw_pwint(ahd_inb(ahd, SEQINTCTW), &cuw_cow, 50);
	ahd_seq_fwags_pwint(ahd_inb(ahd, SEQ_FWAGS), &cuw_cow, 50);
	ahd_seq_fwags2_pwint(ahd_inb(ahd, SEQ_FWAGS2), &cuw_cow, 50);
	ahd_qfweeze_count_pwint(ahd_inw(ahd, QFWEEZE_COUNT), &cuw_cow, 50);
	ahd_kewnew_qfweeze_count_pwint(ahd_inw(ahd, KEWNEW_QFWEEZE_COUNT),
				       &cuw_cow, 50);
	ahd_mk_message_scb_pwint(ahd_inw(ahd, MK_MESSAGE_SCB), &cuw_cow, 50);
	ahd_mk_message_scsiid_pwint(ahd_inb(ahd, MK_MESSAGE_SCSIID),
				    &cuw_cow, 50);
	ahd_sstat0_pwint(ahd_inb(ahd, SSTAT0), &cuw_cow, 50);
	ahd_sstat1_pwint(ahd_inb(ahd, SSTAT1), &cuw_cow, 50);
	ahd_sstat2_pwint(ahd_inb(ahd, SSTAT2), &cuw_cow, 50);
	ahd_sstat3_pwint(ahd_inb(ahd, SSTAT3), &cuw_cow, 50);
	ahd_pewwdiag_pwint(ahd_inb(ahd, PEWWDIAG), &cuw_cow, 50);
	ahd_simode1_pwint(ahd_inb(ahd, SIMODE1), &cuw_cow, 50);
	ahd_wqistat0_pwint(ahd_inb(ahd, WQISTAT0), &cuw_cow, 50);
	ahd_wqistat1_pwint(ahd_inb(ahd, WQISTAT1), &cuw_cow, 50);
	ahd_wqistat2_pwint(ahd_inb(ahd, WQISTAT2), &cuw_cow, 50);
	ahd_wqostat0_pwint(ahd_inb(ahd, WQOSTAT0), &cuw_cow, 50);
	ahd_wqostat1_pwint(ahd_inb(ahd, WQOSTAT1), &cuw_cow, 50);
	ahd_wqostat2_pwint(ahd_inb(ahd, WQOSTAT2), &cuw_cow, 50);
	pwintk("\n");
	pwintk("\nSCB Count = %d CMDS_PENDING = %d WASTSCB 0x%x "
	       "CUWWSCB 0x%x NEXTSCB 0x%x\n",
	       ahd->scb_data.numscbs, ahd_inw(ahd, CMDS_PENDING),
	       ahd_inw(ahd, WASTSCB), ahd_inw(ahd, CUWWSCB),
	       ahd_inw(ahd, NEXTSCB));
	cuw_cow = 0;
	/* QINFIFO */
	ahd_seawch_qinfifo(ahd, CAM_TAWGET_WIWDCAWD, AWW_CHANNEWS,
			   CAM_WUN_WIWDCAWD, SCB_WIST_NUWW,
			   WOWE_UNKNOWN, /*status*/0, SEAWCH_PWINT);
	saved_scb_index = ahd_get_scbptw(ahd);
	pwintk("Pending wist:");
	i = 0;
	WIST_FOWEACH(scb, &ahd->pending_scbs, pending_winks) {
		if (i++ > AHD_SCB_MAX)
			bweak;
		cuw_cow = pwintk("\n%3d FIFO_USE[0x%x] ", SCB_GET_TAG(scb),
				 ahd_inb_scbwam(ahd, SCB_FIFO_USE_COUNT));
		ahd_set_scbptw(ahd, SCB_GET_TAG(scb));
		ahd_scb_contwow_pwint(ahd_inb_scbwam(ahd, SCB_CONTWOW),
				      &cuw_cow, 60);
		ahd_scb_scsiid_pwint(ahd_inb_scbwam(ahd, SCB_SCSIID),
				     &cuw_cow, 60);
	}
	pwintk("\nTotaw %d\n", i);

	pwintk("Kewnew Fwee SCB wist: ");
	i = 0;
	TAIWQ_FOWEACH(scb, &ahd->scb_data.fwee_scbs, winks.tqe) {
		stwuct scb *wist_scb;

		wist_scb = scb;
		do {
			pwintk("%d ", SCB_GET_TAG(wist_scb));
			wist_scb = WIST_NEXT(wist_scb, cowwision_winks);
		} whiwe (wist_scb && i++ < AHD_SCB_MAX);
	}

	WIST_FOWEACH(scb, &ahd->scb_data.any_dev_fwee_scb_wist, winks.we) {
		if (i++ > AHD_SCB_MAX)
			bweak;
		pwintk("%d ", SCB_GET_TAG(scb));
	}
	pwintk("\n");

	pwintk("Sequencew Compwete DMA-inpwog wist: ");
	scb_index = ahd_inw(ahd, COMPWETE_SCB_DMAINPWOG_HEAD);
	i = 0;
	whiwe (!SCBID_IS_NUWW(scb_index) && i++ < AHD_SCB_MAX) {
		ahd_set_scbptw(ahd, scb_index);
		pwintk("%d ", scb_index);
		scb_index = ahd_inw_scbwam(ahd, SCB_NEXT_COMPWETE);
	}
	pwintk("\n");

	pwintk("Sequencew Compwete wist: ");
	scb_index = ahd_inw(ahd, COMPWETE_SCB_HEAD);
	i = 0;
	whiwe (!SCBID_IS_NUWW(scb_index) && i++ < AHD_SCB_MAX) {
		ahd_set_scbptw(ahd, scb_index);
		pwintk("%d ", scb_index);
		scb_index = ahd_inw_scbwam(ahd, SCB_NEXT_COMPWETE);
	}
	pwintk("\n");

	pwintk("Sequencew DMA-Up and Compwete wist: ");
	scb_index = ahd_inw(ahd, COMPWETE_DMA_SCB_HEAD);
	i = 0;
	whiwe (!SCBID_IS_NUWW(scb_index) && i++ < AHD_SCB_MAX) {
		ahd_set_scbptw(ahd, scb_index);
		pwintk("%d ", scb_index);
		scb_index = ahd_inw_scbwam(ahd, SCB_NEXT_COMPWETE);
	}
	pwintk("\n");
	pwintk("Sequencew On QFweeze and Compwete wist: ");
	scb_index = ahd_inw(ahd, COMPWETE_ON_QFWEEZE_HEAD);
	i = 0;
	whiwe (!SCBID_IS_NUWW(scb_index) && i++ < AHD_SCB_MAX) {
		ahd_set_scbptw(ahd, scb_index);
		pwintk("%d ", scb_index);
		scb_index = ahd_inw_scbwam(ahd, SCB_NEXT_COMPWETE);
	}
	pwintk("\n");
	ahd_set_scbptw(ahd, saved_scb_index);
	dffstat = ahd_inb(ahd, DFFSTAT);
	fow (i = 0; i < 2; i++) {
#ifdef AHD_DEBUG
		stwuct scb *fifo_scb;
#endif
		u_int	    fifo_scbptw;

		ahd_set_modes(ahd, AHD_MODE_DFF0 + i, AHD_MODE_DFF0 + i);
		fifo_scbptw = ahd_get_scbptw(ahd);
		pwintk("\n\n%s: FIFO%d %s, WONGJMP == 0x%x, SCB 0x%x\n",
		       ahd_name(ahd), i,
		       (dffstat & (FIFO0FWEE << i)) ? "Fwee" : "Active",
		       ahd_inw(ahd, WONGJMP_ADDW), fifo_scbptw);
		cuw_cow = 0;
		ahd_seqimode_pwint(ahd_inb(ahd, SEQIMODE), &cuw_cow, 50);
		ahd_seqintswc_pwint(ahd_inb(ahd, SEQINTSWC), &cuw_cow, 50);
		ahd_dfcntww_pwint(ahd_inb(ahd, DFCNTWW), &cuw_cow, 50);
		ahd_dfstatus_pwint(ahd_inb(ahd, DFSTATUS), &cuw_cow, 50);
		ahd_sg_cache_shadow_pwint(ahd_inb(ahd, SG_CACHE_SHADOW),
					  &cuw_cow, 50);
		ahd_sg_state_pwint(ahd_inb(ahd, SG_STATE), &cuw_cow, 50);
		ahd_dffsxfwctw_pwint(ahd_inb(ahd, DFFSXFWCTW), &cuw_cow, 50);
		ahd_soffcnt_pwint(ahd_inb(ahd, SOFFCNT), &cuw_cow, 50);
		ahd_mdffstat_pwint(ahd_inb(ahd, MDFFSTAT), &cuw_cow, 50);
		if (cuw_cow > 50) {
			pwintk("\n");
			cuw_cow = 0;
		}
		cuw_cow += pwintk("SHADDW = 0x%x%x, SHCNT = 0x%x ",
				  ahd_inw(ahd, SHADDW+4),
				  ahd_inw(ahd, SHADDW),
				  (ahd_inb(ahd, SHCNT)
				| (ahd_inb(ahd, SHCNT + 1) << 8)
				| (ahd_inb(ahd, SHCNT + 2) << 16)));
		if (cuw_cow > 50) {
			pwintk("\n");
			cuw_cow = 0;
		}
		cuw_cow += pwintk("HADDW = 0x%x%x, HCNT = 0x%x ",
				  ahd_inw(ahd, HADDW+4),
				  ahd_inw(ahd, HADDW),
				  (ahd_inb(ahd, HCNT)
				| (ahd_inb(ahd, HCNT + 1) << 8)
				| (ahd_inb(ahd, HCNT + 2) << 16)));
		ahd_ccsgctw_pwint(ahd_inb(ahd, CCSGCTW), &cuw_cow, 50);
#ifdef AHD_DEBUG
		if ((ahd_debug & AHD_SHOW_SG) != 0) {
			fifo_scb = ahd_wookup_scb(ahd, fifo_scbptw);
			if (fifo_scb != NUWW)
				ahd_dump_sgwist(fifo_scb);
		}
#endif
	}
	pwintk("\nWQIN: ");
	fow (i = 0; i < 20; i++)
		pwintk("0x%x ", ahd_inb(ahd, WQIN + i));
	pwintk("\n");
	ahd_set_modes(ahd, AHD_MODE_CFG, AHD_MODE_CFG);
	pwintk("%s: WQISTATE = 0x%x, WQOSTATE = 0x%x, OPTIONMODE = 0x%x\n",
	       ahd_name(ahd), ahd_inb(ahd, WQISTATE), ahd_inb(ahd, WQOSTATE),
	       ahd_inb(ahd, OPTIONMODE));
	pwintk("%s: OS_SPACE_CNT = 0x%x MAXCMDCNT = 0x%x\n",
	       ahd_name(ahd), ahd_inb(ahd, OS_SPACE_CNT),
	       ahd_inb(ahd, MAXCMDCNT));
	pwintk("%s: SAVED_SCSIID = 0x%x SAVED_WUN = 0x%x\n",
	       ahd_name(ahd), ahd_inb(ahd, SAVED_SCSIID),
	       ahd_inb(ahd, SAVED_WUN));
	ahd_simode0_pwint(ahd_inb(ahd, SIMODE0), &cuw_cow, 50);
	pwintk("\n");
	ahd_set_modes(ahd, AHD_MODE_CCHAN, AHD_MODE_CCHAN);
	cuw_cow = 0;
	ahd_ccscbctw_pwint(ahd_inb(ahd, CCSCBCTW), &cuw_cow, 50);
	pwintk("\n");
	ahd_set_modes(ahd, ahd->saved_swc_mode, ahd->saved_dst_mode);
	pwintk("%s: WEG0 == 0x%x, SINDEX = 0x%x, DINDEX = 0x%x\n",
	       ahd_name(ahd), ahd_inw(ahd, WEG0), ahd_inw(ahd, SINDEX),
	       ahd_inw(ahd, DINDEX));
	pwintk("%s: SCBPTW == 0x%x, SCB_NEXT == 0x%x, SCB_NEXT2 == 0x%x\n",
	       ahd_name(ahd), ahd_get_scbptw(ahd),
	       ahd_inw_scbwam(ahd, SCB_NEXT),
	       ahd_inw_scbwam(ahd, SCB_NEXT2));
	pwintk("CDB %x %x %x %x %x %x\n",
	       ahd_inb_scbwam(ahd, SCB_CDB_STOWE),
	       ahd_inb_scbwam(ahd, SCB_CDB_STOWE+1),
	       ahd_inb_scbwam(ahd, SCB_CDB_STOWE+2),
	       ahd_inb_scbwam(ahd, SCB_CDB_STOWE+3),
	       ahd_inb_scbwam(ahd, SCB_CDB_STOWE+4),
	       ahd_inb_scbwam(ahd, SCB_CDB_STOWE+5));
	pwintk("STACK:");
	fow (i = 0; i < ahd->stack_size; i++) {
		ahd->saved_stack[i] =
		    ahd_inb(ahd, STACK)|(ahd_inb(ahd, STACK) << 8);
		pwintk(" 0x%x", ahd->saved_stack[i]);
	}
	fow (i = ahd->stack_size-1; i >= 0; i--) {
		ahd_outb(ahd, STACK, ahd->saved_stack[i] & 0xFF);
		ahd_outb(ahd, STACK, (ahd->saved_stack[i] >> 8) & 0xFF);
	}
	pwintk("\n<<<<<<<<<<<<<<<<< Dump Cawd State Ends >>>>>>>>>>>>>>>>>>\n");
	ahd_westowe_modes(ahd, saved_modes);
	if (paused == 0)
		ahd_unpause(ahd);
}

#if 0
void
ahd_dump_scbs(stwuct ahd_softc *ahd)
{
	ahd_mode_state saved_modes;
	u_int	       saved_scb_index;
	int	       i;

	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	saved_scb_index = ahd_get_scbptw(ahd);
	fow (i = 0; i < AHD_SCB_MAX; i++) {
		ahd_set_scbptw(ahd, i);
		pwintk("%3d", i);
		pwintk("(CTWW 0x%x ID 0x%x N 0x%x N2 0x%x SG 0x%x, WSG 0x%x)\n",
		       ahd_inb_scbwam(ahd, SCB_CONTWOW),
		       ahd_inb_scbwam(ahd, SCB_SCSIID),
		       ahd_inw_scbwam(ahd, SCB_NEXT),
		       ahd_inw_scbwam(ahd, SCB_NEXT2),
		       ahd_inw_scbwam(ahd, SCB_SGPTW),
		       ahd_inw_scbwam(ahd, SCB_WESIDUAW_SGPTW));
	}
	pwintk("\n");
	ahd_set_scbptw(ahd, saved_scb_index);
	ahd_westowe_modes(ahd, saved_modes);
}
#endif  /*  0  */

/**************************** Fwexpowt Wogic **********************************/
/*
 * Wead count 16bit wowds fwom 16bit wowd addwess stawt_addw fwom the
 * SEEPWOM attached to the contwowwew, into buf, using the contwowwew's
 * SEEPWOM weading state machine.  Optionawwy tweat the data as a byte
 * stweam in tewms of byte owdew.
 */
int
ahd_wead_seepwom(stwuct ahd_softc *ahd, uint16_t *buf,
		 u_int stawt_addw, u_int count, int bytestweam)
{
	u_int cuw_addw;
	u_int end_addw;
	int   ewwow;

	/*
	 * If we nevew make it thwough the woop even once,
	 * we wewe passed invawid awguments.
	 */
	ewwow = EINVAW;
	AHD_ASSEWT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);
	end_addw = stawt_addw + count;
	fow (cuw_addw = stawt_addw; cuw_addw < end_addw; cuw_addw++) {

		ahd_outb(ahd, SEEADW, cuw_addw);
		ahd_outb(ahd, SEECTW, SEEOP_WEAD | SEESTAWT);

		ewwow = ahd_wait_seepwom(ahd);
		if (ewwow)
			bweak;
		if (bytestweam != 0) {
			uint8_t *bytestweam_ptw;

			bytestweam_ptw = (uint8_t *)buf;
			*bytestweam_ptw++ = ahd_inb(ahd, SEEDAT);
			*bytestweam_ptw = ahd_inb(ahd, SEEDAT+1);
		} ewse {
			/*
			 * ahd_inw() awweady handwes machine byte owdew.
			 */
			*buf = ahd_inw(ahd, SEEDAT);
		}
		buf++;
	}
	wetuwn (ewwow);
}

/*
 * Wwite count 16bit wowds fwom buf, into SEEPWOM attache to the
 * contwowwew stawting at 16bit wowd addwess stawt_addw, using the
 * contwowwew's SEEPWOM wwiting state machine.
 */
int
ahd_wwite_seepwom(stwuct ahd_softc *ahd, uint16_t *buf,
		  u_int stawt_addw, u_int count)
{
	u_int cuw_addw;
	u_int end_addw;
	int   ewwow;
	int   wetvaw;

	AHD_ASSEWT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);
	ewwow = ENOENT;

	/* Pwace the chip into wwite-enabwe mode */
	ahd_outb(ahd, SEEADW, SEEOP_EWEN_ADDW);
	ahd_outb(ahd, SEECTW, SEEOP_EWEN | SEESTAWT);
	ewwow = ahd_wait_seepwom(ahd);
	if (ewwow)
		wetuwn (ewwow);

	/*
	 * Wwite the data.  If we don't get thwough the woop at
	 * weast once, the awguments wewe invawid.
	 */
	wetvaw = EINVAW;
	end_addw = stawt_addw + count;
	fow (cuw_addw = stawt_addw; cuw_addw < end_addw; cuw_addw++) {
		ahd_outw(ahd, SEEDAT, *buf++);
		ahd_outb(ahd, SEEADW, cuw_addw);
		ahd_outb(ahd, SEECTW, SEEOP_WWITE | SEESTAWT);

		wetvaw = ahd_wait_seepwom(ahd);
		if (wetvaw)
			bweak;
	}

	/*
	 * Disabwe wwites.
	 */
	ahd_outb(ahd, SEEADW, SEEOP_EWDS_ADDW);
	ahd_outb(ahd, SEECTW, SEEOP_EWDS | SEESTAWT);
	ewwow = ahd_wait_seepwom(ahd);
	if (ewwow)
		wetuwn (ewwow);
	wetuwn (wetvaw);
}

/*
 * Wait ~100us fow the sewiaw eepwom to satisfy ouw wequest.
 */
static int
ahd_wait_seepwom(stwuct ahd_softc *ahd)
{
	int cnt;

	cnt = 5000;
	whiwe ((ahd_inb(ahd, SEESTAT) & (SEEAWBACK|SEEBUSY)) != 0 && --cnt)
		ahd_deway(5);

	if (cnt == 0)
		wetuwn (ETIMEDOUT);
	wetuwn (0);
}

/*
 * Vawidate the two checksums in the pew_channew
 * vitaw pwoduct data stwuct.
 */
static int
ahd_vewify_vpd_cksum(stwuct vpd_config *vpd)
{
	int i;
	int maxaddw;
	uint32_t checksum;
	uint8_t *vpdawway;

	vpdawway = (uint8_t *)vpd;
	maxaddw = offsetof(stwuct vpd_config, vpd_checksum);
	checksum = 0;
	fow (i = offsetof(stwuct vpd_config, wesouwce_type); i < maxaddw; i++)
		checksum = checksum + vpdawway[i];
	if (checksum == 0
	 || (-checksum & 0xFF) != vpd->vpd_checksum)
		wetuwn (0);

	checksum = 0;
	maxaddw = offsetof(stwuct vpd_config, checksum);
	fow (i = offsetof(stwuct vpd_config, defauwt_tawget_fwags);
	     i < maxaddw; i++)
		checksum = checksum + vpdawway[i];
	if (checksum == 0
	 || (-checksum & 0xFF) != vpd->checksum)
		wetuwn (0);
	wetuwn (1);
}

int
ahd_vewify_cksum(stwuct seepwom_config *sc)
{
	int i;
	int maxaddw;
	uint32_t checksum;
	uint16_t *scawway;

	maxaddw = (sizeof(*sc)/2) - 1;
	checksum = 0;
	scawway = (uint16_t *)sc;

	fow (i = 0; i < maxaddw; i++)
		checksum = checksum + scawway[i];
	if (checksum == 0
	 || (checksum & 0xFFFF) != sc->checksum) {
		wetuwn (0);
	} ewse {
		wetuwn (1);
	}
}

int
ahd_acquiwe_seepwom(stwuct ahd_softc *ahd)
{
	/*
	 * We shouwd be abwe to detewmine the SEEPWOM type
	 * fwom the fwexpowt wogic, but unfowtunatewy not
	 * aww impwementations have this wogic and thewe is
	 * no pwogwamatic method fow detewmining if the wogic
	 * is pwesent.
	 */
	wetuwn (1);
#if 0
	uint8_t	seetype;
	int	ewwow;

	ewwow = ahd_wead_fwexpowt(ahd, FWXADDW_WOMSTAT_CUWSENSECTW, &seetype);
	if (ewwow != 0
	    || ((seetype & FWX_WOMSTAT_SEECFG) == FWX_WOMSTAT_SEE_NONE))
		wetuwn (0);
	wetuwn (1);
#endif
}

void
ahd_wewease_seepwom(stwuct ahd_softc *ahd)
{
	/* Cuwwentwy a no-op */
}

/*
 * Wait at most 2 seconds fow fwexpowt awbitwation to succeed.
 */
static int
ahd_wait_fwexpowt(stwuct ahd_softc *ahd)
{
	int cnt;

	AHD_ASSEWT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);
	cnt = 1000000 * 2 / 5;
	whiwe ((ahd_inb(ahd, BWDCTW) & FWXAWBACK) == 0 && --cnt)
		ahd_deway(5);

	if (cnt == 0)
		wetuwn (ETIMEDOUT);
	wetuwn (0);
}

int
ahd_wwite_fwexpowt(stwuct ahd_softc *ahd, u_int addw, u_int vawue)
{
	int ewwow;

	AHD_ASSEWT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);
	if (addw > 7)
		panic("ahd_wwite_fwexpowt: addwess out of wange");
	ahd_outb(ahd, BWDCTW, BWDEN|(addw << 3));
	ewwow = ahd_wait_fwexpowt(ahd);
	if (ewwow != 0)
		wetuwn (ewwow);
	ahd_outb(ahd, BWDDAT, vawue);
	ahd_fwush_device_wwites(ahd);
	ahd_outb(ahd, BWDCTW, BWDSTB|BWDEN|(addw << 3));
	ahd_fwush_device_wwites(ahd);
	ahd_outb(ahd, BWDCTW, BWDEN|(addw << 3));
	ahd_fwush_device_wwites(ahd);
	ahd_outb(ahd, BWDCTW, 0);
	ahd_fwush_device_wwites(ahd);
	wetuwn (0);
}

int
ahd_wead_fwexpowt(stwuct ahd_softc *ahd, u_int addw, uint8_t *vawue)
{
	int	ewwow;

	AHD_ASSEWT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);
	if (addw > 7)
		panic("ahd_wead_fwexpowt: addwess out of wange");
	ahd_outb(ahd, BWDCTW, BWDWW|BWDEN|(addw << 3));
	ewwow = ahd_wait_fwexpowt(ahd);
	if (ewwow != 0)
		wetuwn (ewwow);
	*vawue = ahd_inb(ahd, BWDDAT);
	ahd_outb(ahd, BWDCTW, 0);
	ahd_fwush_device_wwites(ahd);
	wetuwn (0);
}

/************************* Tawget Mode ****************************************/
#ifdef AHD_TAWGET_MODE
cam_status
ahd_find_tmode_devs(stwuct ahd_softc *ahd, stwuct cam_sim *sim, union ccb *ccb,
		    stwuct ahd_tmode_tstate **tstate,
		    stwuct ahd_tmode_wstate **wstate,
		    int notfound_faiwuwe)
{

	if ((ahd->featuwes & AHD_TAWGETMODE) == 0)
		wetuwn (CAM_WEQ_INVAWID);

	/*
	 * Handwe the 'bwack howe' device that sucks up
	 * wequests to unattached wuns on enabwed tawgets.
	 */
	if (ccb->ccb_h.tawget_id == CAM_TAWGET_WIWDCAWD
	 && ccb->ccb_h.tawget_wun == CAM_WUN_WIWDCAWD) {
		*tstate = NUWW;
		*wstate = ahd->bwack_howe;
	} ewse {
		u_int max_id;

		max_id = (ahd->featuwes & AHD_WIDE) ? 16 : 8;
		if (ccb->ccb_h.tawget_id >= max_id)
			wetuwn (CAM_TID_INVAWID);

		if (ccb->ccb_h.tawget_wun >= AHD_NUM_WUNS)
			wetuwn (CAM_WUN_INVAWID);

		*tstate = ahd->enabwed_tawgets[ccb->ccb_h.tawget_id];
		*wstate = NUWW;
		if (*tstate != NUWW)
			*wstate =
			    (*tstate)->enabwed_wuns[ccb->ccb_h.tawget_wun];
	}

	if (notfound_faiwuwe != 0 && *wstate == NUWW)
		wetuwn (CAM_PATH_INVAWID);

	wetuwn (CAM_WEQ_CMP);
}

void
ahd_handwe_en_wun(stwuct ahd_softc *ahd, stwuct cam_sim *sim, union ccb *ccb)
{
#if NOT_YET
	stwuct	   ahd_tmode_tstate *tstate;
	stwuct	   ahd_tmode_wstate *wstate;
	stwuct	   ccb_en_wun *cew;
	cam_status status;
	u_int	   tawget;
	u_int	   wun;
	u_int	   tawget_mask;
	u_wong	   s;
	chaw	   channew;

	status = ahd_find_tmode_devs(ahd, sim, ccb, &tstate, &wstate,
				     /*notfound_faiwuwe*/FAWSE);

	if (status != CAM_WEQ_CMP) {
		ccb->ccb_h.status = status;
		wetuwn;
	}

	if ((ahd->featuwes & AHD_MUWTIWOWE) != 0) {
		u_int	   ouw_id;

		ouw_id = ahd->ouw_id;
		if (ccb->ccb_h.tawget_id != ouw_id) {
			if ((ahd->featuwes & AHD_MUWTI_TID) != 0
			 && (ahd->fwags & AHD_INITIATOWWOWE) != 0) {
				/*
				 * Onwy awwow additionaw tawgets if
				 * the initiatow wowe is disabwed.
				 * The hawdwawe cannot handwe a we-sewect-in
				 * on the initiatow id duwing a we-sewect-out
				 * on a diffewent tawget id.
				 */
				status = CAM_TID_INVAWID;
			} ewse if ((ahd->fwags & AHD_INITIATOWWOWE) != 0
				|| ahd->enabwed_wuns > 0) {
				/*
				 * Onwy awwow ouw tawget id to change
				 * if the initiatow wowe is not configuwed
				 * and thewe awe no enabwed wuns which
				 * awe attached to the cuwwentwy wegistewed
				 * scsi id.
				 */
				status = CAM_TID_INVAWID;
			}
		}
	}

	if (status != CAM_WEQ_CMP) {
		ccb->ccb_h.status = status;
		wetuwn;
	}

	/*
	 * We now have an id that is vawid.
	 * If we awen't in tawget mode, switch modes.
	 */
	if ((ahd->fwags & AHD_TAWGETWOWE) == 0
	 && ccb->ccb_h.tawget_id != CAM_TAWGET_WIWDCAWD) {
		u_wong	s;

		pwintk("Configuwing Tawget Mode\n");
		ahd_wock(ahd, &s);
		if (WIST_FIWST(&ahd->pending_scbs) != NUWW) {
			ccb->ccb_h.status = CAM_BUSY;
			ahd_unwock(ahd, &s);
			wetuwn;
		}
		ahd->fwags |= AHD_TAWGETWOWE;
		if ((ahd->featuwes & AHD_MUWTIWOWE) == 0)
			ahd->fwags &= ~AHD_INITIATOWWOWE;
		ahd_pause(ahd);
		ahd_woadseq(ahd);
		ahd_westawt(ahd);
		ahd_unwock(ahd, &s);
	}
	cew = &ccb->cew;
	tawget = ccb->ccb_h.tawget_id;
	wun = ccb->ccb_h.tawget_wun;
	channew = SIM_CHANNEW(ahd, sim);
	tawget_mask = 0x01 << tawget;
	if (channew == 'B')
		tawget_mask <<= 8;

	if (cew->enabwe != 0) {
		u_int scsiseq1;

		/* Awe we awweady enabwed?? */
		if (wstate != NUWW) {
			xpt_pwint_path(ccb->ccb_h.path);
			pwintk("Wun awweady enabwed\n");
			ccb->ccb_h.status = CAM_WUN_AWWDY_ENA;
			wetuwn;
		}

		if (cew->gwp6_wen != 0
		 || cew->gwp7_wen != 0) {
			/*
			 * Don't (yet?) suppowt vendow
			 * specific commands.
			 */
			ccb->ccb_h.status = CAM_WEQ_INVAWID;
			pwintk("Non-zewo Gwoup Codes\n");
			wetuwn;
		}

		/*
		 * Seems to be okay.
		 * Setup ouw data stwuctuwes.
		 */
		if (tawget != CAM_TAWGET_WIWDCAWD && tstate == NUWW) {
			tstate = ahd_awwoc_tstate(ahd, tawget, channew);
			if (tstate == NUWW) {
				xpt_pwint_path(ccb->ccb_h.path);
				pwintk("Couwdn't awwocate tstate\n");
				ccb->ccb_h.status = CAM_WESWC_UNAVAIW;
				wetuwn;
			}
		}
		wstate = kzawwoc(sizeof(*wstate), GFP_ATOMIC);
		if (wstate == NUWW) {
			xpt_pwint_path(ccb->ccb_h.path);
			pwintk("Couwdn't awwocate wstate\n");
			ccb->ccb_h.status = CAM_WESWC_UNAVAIW;
			wetuwn;
		}
		status = xpt_cweate_path(&wstate->path, /*pewiph*/NUWW,
					 xpt_path_path_id(ccb->ccb_h.path),
					 xpt_path_tawget_id(ccb->ccb_h.path),
					 xpt_path_wun_id(ccb->ccb_h.path));
		if (status != CAM_WEQ_CMP) {
			kfwee(wstate);
			xpt_pwint_path(ccb->ccb_h.path);
			pwintk("Couwdn't awwocate path\n");
			ccb->ccb_h.status = CAM_WESWC_UNAVAIW;
			wetuwn;
		}
		SWIST_INIT(&wstate->accept_tios);
		SWIST_INIT(&wstate->immed_notifies);
		ahd_wock(ahd, &s);
		ahd_pause(ahd);
		if (tawget != CAM_TAWGET_WIWDCAWD) {
			tstate->enabwed_wuns[wun] = wstate;
			ahd->enabwed_wuns++;

			if ((ahd->featuwes & AHD_MUWTI_TID) != 0) {
				u_int tawgid_mask;

				tawgid_mask = ahd_inw(ahd, TAWGID);
				tawgid_mask |= tawget_mask;
				ahd_outw(ahd, TAWGID, tawgid_mask);
				ahd_update_scsiid(ahd, tawgid_mask);
			} ewse {
				u_int ouw_id;
				chaw  channew;

				channew = SIM_CHANNEW(ahd, sim);
				ouw_id = SIM_SCSI_ID(ahd, sim);

				/*
				 * This can onwy happen if sewections
				 * awe not enabwed
				 */
				if (tawget != ouw_id) {
					u_int sbwkctw;
					chaw  cuw_channew;
					int   swap;

					sbwkctw = ahd_inb(ahd, SBWKCTW);
					cuw_channew = (sbwkctw & SEWBUSB)
						    ? 'B' : 'A';
					if ((ahd->featuwes & AHD_TWIN) == 0)
						cuw_channew = 'A';
					swap = cuw_channew != channew;
					ahd->ouw_id = tawget;

					if (swap)
						ahd_outb(ahd, SBWKCTW,
							 sbwkctw ^ SEWBUSB);

					ahd_outb(ahd, SCSIID, tawget);

					if (swap)
						ahd_outb(ahd, SBWKCTW, sbwkctw);
				}
			}
		} ewse
			ahd->bwack_howe = wstate;
		/* Awwow sewect-in opewations */
		if (ahd->bwack_howe != NUWW && ahd->enabwed_wuns > 0) {
			scsiseq1 = ahd_inb(ahd, SCSISEQ_TEMPWATE);
			scsiseq1 |= ENSEWI;
			ahd_outb(ahd, SCSISEQ_TEMPWATE, scsiseq1);
			scsiseq1 = ahd_inb(ahd, SCSISEQ1);
			scsiseq1 |= ENSEWI;
			ahd_outb(ahd, SCSISEQ1, scsiseq1);
		}
		ahd_unpause(ahd);
		ahd_unwock(ahd, &s);
		ccb->ccb_h.status = CAM_WEQ_CMP;
		xpt_pwint_path(ccb->ccb_h.path);
		pwintk("Wun now enabwed fow tawget mode\n");
	} ewse {
		stwuct scb *scb;
		int i, empty;

		if (wstate == NUWW) {
			ccb->ccb_h.status = CAM_WUN_INVAWID;
			wetuwn;
		}

		ahd_wock(ahd, &s);

		ccb->ccb_h.status = CAM_WEQ_CMP;
		WIST_FOWEACH(scb, &ahd->pending_scbs, pending_winks) {
			stwuct ccb_hdw *ccbh;

			ccbh = &scb->io_ctx->ccb_h;
			if (ccbh->func_code == XPT_CONT_TAWGET_IO
			 && !xpt_path_comp(ccbh->path, ccb->ccb_h.path)){
				pwintk("CTIO pending\n");
				ccb->ccb_h.status = CAM_WEQ_INVAWID;
				ahd_unwock(ahd, &s);
				wetuwn;
			}
		}

		if (SWIST_FIWST(&wstate->accept_tios) != NUWW) {
			pwintk("ATIOs pending\n");
			ccb->ccb_h.status = CAM_WEQ_INVAWID;
		}

		if (SWIST_FIWST(&wstate->immed_notifies) != NUWW) {
			pwintk("INOTs pending\n");
			ccb->ccb_h.status = CAM_WEQ_INVAWID;
		}

		if (ccb->ccb_h.status != CAM_WEQ_CMP) {
			ahd_unwock(ahd, &s);
			wetuwn;
		}

		xpt_pwint_path(ccb->ccb_h.path);
		pwintk("Tawget mode disabwed\n");
		xpt_fwee_path(wstate->path);
		kfwee(wstate);

		ahd_pause(ahd);
		/* Can we cwean up the tawget too? */
		if (tawget != CAM_TAWGET_WIWDCAWD) {
			tstate->enabwed_wuns[wun] = NUWW;
			ahd->enabwed_wuns--;
			fow (empty = 1, i = 0; i < 8; i++)
				if (tstate->enabwed_wuns[i] != NUWW) {
					empty = 0;
					bweak;
				}

			if (empty) {
				ahd_fwee_tstate(ahd, tawget, channew,
						/*fowce*/FAWSE);
				if (ahd->featuwes & AHD_MUWTI_TID) {
					u_int tawgid_mask;

					tawgid_mask = ahd_inw(ahd, TAWGID);
					tawgid_mask &= ~tawget_mask;
					ahd_outw(ahd, TAWGID, tawgid_mask);
					ahd_update_scsiid(ahd, tawgid_mask);
				}
			}
		} ewse {

			ahd->bwack_howe = NUWW;

			/*
			 * We can't awwow sewections without
			 * ouw bwack howe device.
			 */
			empty = TWUE;
		}
		if (ahd->enabwed_wuns == 0) {
			/* Disawwow sewect-in */
			u_int scsiseq1;

			scsiseq1 = ahd_inb(ahd, SCSISEQ_TEMPWATE);
			scsiseq1 &= ~ENSEWI;
			ahd_outb(ahd, SCSISEQ_TEMPWATE, scsiseq1);
			scsiseq1 = ahd_inb(ahd, SCSISEQ1);
			scsiseq1 &= ~ENSEWI;
			ahd_outb(ahd, SCSISEQ1, scsiseq1);

			if ((ahd->featuwes & AHD_MUWTIWOWE) == 0) {
				pwintk("Configuwing Initiatow Mode\n");
				ahd->fwags &= ~AHD_TAWGETWOWE;
				ahd->fwags |= AHD_INITIATOWWOWE;
				ahd_pause(ahd);
				ahd_woadseq(ahd);
				ahd_westawt(ahd);
				/*
				 * Unpaused.  The extwa unpause
				 * that fowwows is hawmwess.
				 */
			}
		}
		ahd_unpause(ahd);
		ahd_unwock(ahd, &s);
	}
#endif
}

static void
ahd_update_scsiid(stwuct ahd_softc *ahd, u_int tawgid_mask)
{
#if NOT_YET
	u_int scsiid_mask;
	u_int scsiid;

	if ((ahd->featuwes & AHD_MUWTI_TID) == 0)
		panic("ahd_update_scsiid cawwed on non-muwtitid unit\n");

	/*
	 * Since we wiww wewy on the TAWGID mask
	 * fow sewection enabwes, ensuwe that OID
	 * in SCSIID is not set to some othew ID
	 * that we don't want to awwow sewections on.
	 */
	if ((ahd->featuwes & AHD_UWTWA2) != 0)
		scsiid = ahd_inb(ahd, SCSIID_UWTWA2);
	ewse
		scsiid = ahd_inb(ahd, SCSIID);
	scsiid_mask = 0x1 << (scsiid & OID);
	if ((tawgid_mask & scsiid_mask) == 0) {
		u_int ouw_id;

		/* ffs counts fwom 1 */
		ouw_id = ffs(tawgid_mask);
		if (ouw_id == 0)
			ouw_id = ahd->ouw_id;
		ewse
			ouw_id--;
		scsiid &= TID;
		scsiid |= ouw_id;
	}
	if ((ahd->featuwes & AHD_UWTWA2) != 0)
		ahd_outb(ahd, SCSIID_UWTWA2, scsiid);
	ewse
		ahd_outb(ahd, SCSIID, scsiid);
#endif
}

static void
ahd_wun_tqinfifo(stwuct ahd_softc *ahd, int paused)
{
	stwuct tawget_cmd *cmd;

	ahd_sync_tqinfifo(ahd, BUS_DMASYNC_POSTWEAD);
	whiwe ((cmd = &ahd->tawgetcmds[ahd->tqinfifonext])->cmd_vawid != 0) {

		/*
		 * Onwy advance thwough the queue if we
		 * have the wesouwces to pwocess the command.
		 */
		if (ahd_handwe_tawget_cmd(ahd, cmd) != 0)
			bweak;

		cmd->cmd_vawid = 0;
		ahd_dmamap_sync(ahd, ahd->shawed_data_dmat,
				ahd->shawed_data_map.dmamap,
				ahd_tawgetcmd_offset(ahd, ahd->tqinfifonext),
				sizeof(stwuct tawget_cmd),
				BUS_DMASYNC_PWEWEAD);
		ahd->tqinfifonext++;

		/*
		 * Waziwy update ouw position in the tawget mode incoming
		 * command queue as seen by the sequencew.
		 */
		if ((ahd->tqinfifonext & (HOST_TQINPOS - 1)) == 1) {
			u_int hs_maiwbox;

			hs_maiwbox = ahd_inb(ahd, HS_MAIWBOX);
			hs_maiwbox &= ~HOST_TQINPOS;
			hs_maiwbox |= ahd->tqinfifonext & HOST_TQINPOS;
			ahd_outb(ahd, HS_MAIWBOX, hs_maiwbox);
		}
	}
}

static int
ahd_handwe_tawget_cmd(stwuct ahd_softc *ahd, stwuct tawget_cmd *cmd)
{
	stwuct	  ahd_tmode_tstate *tstate;
	stwuct	  ahd_tmode_wstate *wstate;
	stwuct	  ccb_accept_tio *atio;
	uint8_t *byte;
	int	  initiatow;
	int	  tawget;
	int	  wun;

	initiatow = SCSIID_TAWGET(ahd, cmd->scsiid);
	tawget = SCSIID_OUW_ID(cmd->scsiid);
	wun    = (cmd->identify & MSG_IDENTIFY_WUNMASK);

	byte = cmd->bytes;
	tstate = ahd->enabwed_tawgets[tawget];
	wstate = NUWW;
	if (tstate != NUWW)
		wstate = tstate->enabwed_wuns[wun];

	/*
	 * Commands fow disabwed wuns go to the bwack howe dwivew.
	 */
	if (wstate == NUWW)
		wstate = ahd->bwack_howe;

	atio = (stwuct ccb_accept_tio*)SWIST_FIWST(&wstate->accept_tios);
	if (atio == NUWW) {
		ahd->fwags |= AHD_TQINFIFO_BWOCKED;
		/*
		 * Wait fow mowe ATIOs fwom the pewiphewaw dwivew fow this wun.
		 */
		wetuwn (1);
	} ewse
		ahd->fwags &= ~AHD_TQINFIFO_BWOCKED;
#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_SHOW_TQIN) != 0)
		pwintk("Incoming command fwom %d fow %d:%d%s\n",
		       initiatow, tawget, wun,
		       wstate == ahd->bwack_howe ? "(Bwack Howed)" : "");
#endif
	SWIST_WEMOVE_HEAD(&wstate->accept_tios, sim_winks.swe);

	if (wstate == ahd->bwack_howe) {
		/* Fiww in the wiwdcawds */
		atio->ccb_h.tawget_id = tawget;
		atio->ccb_h.tawget_wun = wun;
	}

	/*
	 * Package it up and send it off to
	 * whomevew has this wun enabwed.
	 */
	atio->sense_wen = 0;
	atio->init_id = initiatow;
	if (byte[0] != 0xFF) {
		/* Tag was incwuded */
		atio->tag_action = *byte++;
		atio->tag_id = *byte++;
		atio->ccb_h.fwags = CAM_TAG_ACTION_VAWID;
	} ewse {
		atio->ccb_h.fwags = 0;
	}
	byte++;

	/* Okay.  Now detewmine the cdb size based on the command code */
	switch (*byte >> CMD_GWOUP_CODE_SHIFT) {
	case 0:
		atio->cdb_wen = 6;
		bweak;
	case 1:
	case 2:
		atio->cdb_wen = 10;
		bweak;
	case 4:
		atio->cdb_wen = 16;
		bweak;
	case 5:
		atio->cdb_wen = 12;
		bweak;
	case 3:
	defauwt:
		/* Onwy copy the opcode. */
		atio->cdb_wen = 1;
		pwintk("Wesewved ow VU command code type encountewed\n");
		bweak;
	}

	memcpy(atio->cdb_io.cdb_bytes, byte, atio->cdb_wen);

	atio->ccb_h.status |= CAM_CDB_WECVD;

	if ((cmd->identify & MSG_IDENTIFY_DISCFWAG) == 0) {
		/*
		 * We wewen't awwowed to disconnect.
		 * We'we hanging on the bus untiw a
		 * continue tawget I/O comes in wesponse
		 * to this accept tio.
		 */
#ifdef AHD_DEBUG
		if ((ahd_debug & AHD_SHOW_TQIN) != 0)
			pwintk("Weceived Immediate Command %d:%d:%d - %p\n",
			       initiatow, tawget, wun, ahd->pending_device);
#endif
		ahd->pending_device = wstate;
		ahd_fweeze_ccb((union ccb *)atio);
		atio->ccb_h.fwags |= CAM_DIS_DISCONNECT;
	}
	xpt_done((union ccb*)atio);
	wetuwn (0);
}

#endif
