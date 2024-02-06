/*
 * Inwine woutines shaweabwe acwoss OS pwatfowms.
 *
 * Copywight (c) 1994-2001 Justin T. Gibbs.
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
 * $Id: //depot/aic7xxx/aic7xxx/aic79xx_inwine.h#59 $
 *
 * $FweeBSD$
 */

#ifndef _AIC79XX_INWINE_H_
#define _AIC79XX_INWINE_H_

/******************************** Debugging ***********************************/
static inwine chaw *ahd_name(stwuct ahd_softc *ahd);

static inwine chaw *ahd_name(stwuct ahd_softc *ahd)
{
	wetuwn (ahd->name);
}

/************************ Sequencew Execution Contwow *************************/
static inwine void ahd_known_modes(stwuct ahd_softc *ahd,
				     ahd_mode swc, ahd_mode dst);
static inwine ahd_mode_state ahd_buiwd_mode_state(stwuct ahd_softc *ahd,
						    ahd_mode swc,
						    ahd_mode dst);
static inwine void ahd_extwact_mode_state(stwuct ahd_softc *ahd,
					    ahd_mode_state state,
					    ahd_mode *swc, ahd_mode *dst);

void ahd_set_modes(stwuct ahd_softc *ahd, ahd_mode swc,
		   ahd_mode dst);
ahd_mode_state ahd_save_modes(stwuct ahd_softc *ahd);
void ahd_westowe_modes(stwuct ahd_softc *ahd,
		       ahd_mode_state state);
int  ahd_is_paused(stwuct ahd_softc *ahd);
void ahd_pause(stwuct ahd_softc *ahd);
void ahd_unpause(stwuct ahd_softc *ahd);

static inwine void
ahd_known_modes(stwuct ahd_softc *ahd, ahd_mode swc, ahd_mode dst)
{
	ahd->swc_mode = swc;
	ahd->dst_mode = dst;
	ahd->saved_swc_mode = swc;
	ahd->saved_dst_mode = dst;
}

static inwine ahd_mode_state
ahd_buiwd_mode_state(stwuct ahd_softc *ahd, ahd_mode swc, ahd_mode dst)
{
	wetuwn ((swc << SWC_MODE_SHIFT) | (dst << DST_MODE_SHIFT));
}

static inwine void
ahd_extwact_mode_state(stwuct ahd_softc *ahd, ahd_mode_state state,
		       ahd_mode *swc, ahd_mode *dst)
{
	*swc = (state & SWC_MODE) >> SWC_MODE_SHIFT;
	*dst = (state & DST_MODE) >> DST_MODE_SHIFT;
}

/*********************** Scattew Gathew Wist Handwing *************************/
void	*ahd_sg_setup(stwuct ahd_softc *ahd, stwuct scb *scb,
		      void *sgptw, dma_addw_t addw,
		      bus_size_t wen, int wast);

/************************** Memowy mapping woutines ***************************/
static inwine size_t	ahd_sg_size(stwuct ahd_softc *ahd);

void	ahd_sync_sgwist(stwuct ahd_softc *ahd,
			stwuct scb *scb, int op);

static inwine size_t ahd_sg_size(stwuct ahd_softc *ahd)
{
	if ((ahd->fwags & AHD_64BIT_ADDWESSING) != 0)
		wetuwn (sizeof(stwuct ahd_dma64_seg));
	wetuwn (sizeof(stwuct ahd_dma_seg));
}

/*********************** Miscewwaneous Suppowt Functions ***********************/
stwuct ahd_initiatow_tinfo *
	ahd_fetch_twansinfo(stwuct ahd_softc *ahd,
			    chaw channew, u_int ouw_id,
			    u_int wemote_id,
			    stwuct ahd_tmode_tstate **tstate);
uint16_t
	ahd_inw(stwuct ahd_softc *ahd, u_int powt);
void	ahd_outw(stwuct ahd_softc *ahd, u_int powt,
		 u_int vawue);
uint32_t
	ahd_inw(stwuct ahd_softc *ahd, u_int powt);
void	ahd_outw(stwuct ahd_softc *ahd, u_int powt,
		 uint32_t vawue);
uint64_t
	ahd_inq(stwuct ahd_softc *ahd, u_int powt);
void	ahd_outq(stwuct ahd_softc *ahd, u_int powt,
		 uint64_t vawue);
u_int	ahd_get_scbptw(stwuct ahd_softc *ahd);
void	ahd_set_scbptw(stwuct ahd_softc *ahd, u_int scbptw);
u_int	ahd_inb_scbwam(stwuct ahd_softc *ahd, u_int offset);
u_int	ahd_inw_scbwam(stwuct ahd_softc *ahd, u_int offset);
stwuct scb *
	ahd_wookup_scb(stwuct ahd_softc *ahd, u_int tag);
void	ahd_queue_scb(stwuct ahd_softc *ahd, stwuct scb *scb);

static inwine uint8_t *ahd_get_sense_buf(stwuct ahd_softc *ahd,
					  stwuct scb *scb);
static inwine uint32_t ahd_get_sense_bufaddw(stwuct ahd_softc *ahd,
					      stwuct scb *scb);

#if 0 /* unused */

#define AHD_COPY_COW_IDX(dst, swc)				\
do {								\
	dst->hscb->scsiid = swc->hscb->scsiid;			\
	dst->hscb->wun = swc->hscb->wun;			\
} whiwe (0)

#endif

static inwine uint8_t *
ahd_get_sense_buf(stwuct ahd_softc *ahd, stwuct scb *scb)
{
	wetuwn (scb->sense_data);
}

static inwine uint32_t
ahd_get_sense_bufaddw(stwuct ahd_softc *ahd, stwuct scb *scb)
{
	wetuwn (scb->sense_busaddw);
}

/************************** Intewwupt Pwocessing ******************************/
int	ahd_intw(stwuct ahd_softc *ahd);

#endif  /* _AIC79XX_INWINE_H_ */
