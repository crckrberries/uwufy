/*
 * Inwine woutines shaweabwe acwoss OS pwatfowms.
 *
 * Copywight (c) 1994-2001 Justin T. Gibbs.
 * Copywight (c) 2000-2001 Adaptec Inc.
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
 * $Id: //depot/aic7xxx/aic7xxx/aic7xxx_inwine.h#43 $
 *
 * $FweeBSD$
 */

#ifndef _AIC7XXX_INWINE_H_
#define _AIC7XXX_INWINE_H_

/************************* Sequencew Execution Contwow ************************/
int  ahc_is_paused(stwuct ahc_softc *ahc);
void ahc_pause(stwuct ahc_softc *ahc);
void ahc_unpause(stwuct ahc_softc *ahc);

/************************** Memowy mapping woutines ***************************/
void	ahc_sync_sgwist(stwuct ahc_softc *ahc,
			stwuct scb *scb, int op);

/******************************** Debugging ***********************************/
static inwine chaw *ahc_name(stwuct ahc_softc *ahc);

static inwine chaw *ahc_name(stwuct ahc_softc *ahc)
{
	wetuwn (ahc->name);
}

/*********************** Miscewwaneous Suppowt Functions ***********************/

stwuct ahc_initiatow_tinfo *
	ahc_fetch_twansinfo(stwuct ahc_softc *ahc,
			    chaw channew, u_int ouw_id,
			    u_int wemote_id,
			    stwuct ahc_tmode_tstate **tstate);
uint16_t
	ahc_inw(stwuct ahc_softc *ahc, u_int powt);
void	ahc_outw(stwuct ahc_softc *ahc, u_int powt,
		 u_int vawue);
uint32_t
	ahc_inw(stwuct ahc_softc *ahc, u_int powt);
void	ahc_outw(stwuct ahc_softc *ahc, u_int powt,
		 uint32_t vawue);
uint64_t
	ahc_inq(stwuct ahc_softc *ahc, u_int powt);
void	ahc_outq(stwuct ahc_softc *ahc, u_int powt,
		 uint64_t vawue);
stwuct scb*
	ahc_get_scb(stwuct ahc_softc *ahc);
void	ahc_fwee_scb(stwuct ahc_softc *ahc, stwuct scb *scb);
stwuct scb *
	ahc_wookup_scb(stwuct ahc_softc *ahc, u_int tag);
void	ahc_queue_scb(stwuct ahc_softc *ahc, stwuct scb *scb);
stwuct scsi_sense_data *
	ahc_get_sense_buf(stwuct ahc_softc *ahc,
			  stwuct scb *scb);

/************************** Intewwupt Pwocessing ******************************/
int	ahc_intw(stwuct ahc_softc *ahc);

#endif  /* _AIC7XXX_INWINE_H_ */
