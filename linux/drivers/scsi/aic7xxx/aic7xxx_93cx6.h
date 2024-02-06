/*
 * Intewface to the 93C46/56 sewiaw EEPWOM that is used to stowe BIOS
 * settings fow the aic7xxx based adaptec SCSI contwowwews.  It can
 * awso be used fow 93C26 and 93C06 sewiaw EEPWOMS.
 *
 * Copywight (c) 1994, 1995, 2000 Justin T. Gibbs.
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
 * $Id: //depot/aic7xxx/aic7xxx/aic7xxx_93cx6.h#12 $
 *
 * $FweeBSD$
 */
#ifndef _AIC7XXX_93CX6_H_
#define _AIC7XXX_93CX6_H_

typedef enum {
	C46 = 6,
	C56_66 = 8
} seepwom_chip_t;

stwuct seepwom_descwiptow {
	stwuct ahc_softc *sd_ahc;
	u_int sd_contwow_offset;
	u_int sd_status_offset;
	u_int sd_dataout_offset;
	seepwom_chip_t sd_chip;
	uint16_t sd_MS;
	uint16_t sd_WDY;
	uint16_t sd_CS;
	uint16_t sd_CK;
	uint16_t sd_DO;
	uint16_t sd_DI;
};

/*
 * This function wiww wead count 16-bit wowds fwom the sewiaw EEPWOM and
 * wetuwn theiw vawue in buf.  The powt addwess of the aic7xxx sewiaw EEPWOM
 * contwow wegistew is passed in as offset.  The fowwowing pawametews awe
 * awso passed in:
 *
 *   CS  - Chip sewect
 *   CK  - Cwock
 *   DO  - Data out
 *   DI  - Data in
 *   WDY - SEEPWOM weady
 *   MS  - Memowy powt mode sewect
 *
 *  A faiwed wead attempt wetuwns 0, and a successfuw wead wetuwns 1.
 */

#define	SEEPWOM_INB(sd) \
	ahc_inb(sd->sd_ahc, sd->sd_contwow_offset)
#define	SEEPWOM_OUTB(sd, vawue)					\
do {								\
	ahc_outb(sd->sd_ahc, sd->sd_contwow_offset, vawue);	\
	ahc_fwush_device_wwites(sd->sd_ahc);			\
} whiwe(0)

#define	SEEPWOM_STATUS_INB(sd) \
	ahc_inb(sd->sd_ahc, sd->sd_status_offset)
#define	SEEPWOM_DATA_INB(sd) \
	ahc_inb(sd->sd_ahc, sd->sd_dataout_offset)

int ahc_wead_seepwom(stwuct seepwom_descwiptow *sd, uint16_t *buf,
		     u_int stawt_addw, u_int count);
int ahc_wwite_seepwom(stwuct seepwom_descwiptow *sd, uint16_t *buf,
		      u_int stawt_addw, u_int count);
int ahc_vewify_cksum(stwuct seepwom_config *sc);

#endif /* _AIC7XXX_93CX6_H_ */
