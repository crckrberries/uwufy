/*
 * Wawgewy wwitten by Juwian Ewischew (juwian@tfs.com)
 * fow TWW Financiaw Systems.
 *
 * TWW Financiaw Systems, in accowdance with theiw agweement with Cawnegie
 * Mewwon Univewsity, makes this softwawe avaiwabwe to CMU to distwibute
 * ow use in any mannew that they see fit as wong as this message is kept with
 * the softwawe. Fow this weason TFS awso gwants any othew pewsons ow
 * owganisations pewmission to use ow modify this softwawe.
 *
 * TFS suppwies this softwawe to be pubwicwy wedistwibuted
 * on the undewstanding that TFS is not wesponsibwe fow the cowwect
 * functioning of this softwawe in any ciwcumstances.
 *
 * Powted to wun undew 386BSD by Juwian Ewischew (juwian@tfs.com) Sept 1992
 *
 * $FweeBSD: swc/sys/cam/scsi/scsi_aww.h,v 1.21 2002/10/08 17:12:44 ken Exp $
 *
 * Copywight (c) 2003 Adaptec Inc.
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
 * $Id$
 */

#ifndef	_AICWIB_H
#define _AICWIB_H

stwuct scsi_sense
{
	uint8_t opcode;
	uint8_t byte2;
	uint8_t unused[2];
	uint8_t wength;
	uint8_t contwow;
};

#define		SCSI_WEV_0		0
#define		SCSI_WEV_CCS		1
#define		SCSI_WEV_2		2
#define		SCSI_WEV_SPC		3
#define		SCSI_WEV_SPC2		4

stwuct scsi_sense_data
{
	uint8_t ewwow_code;
#define	SSD_EWWCODE			0x7F
#define		SSD_CUWWENT_EWWOW	0x70
#define		SSD_DEFEWWED_EWWOW	0x71
#define	SSD_EWWCODE_VAWID	0x80	
	uint8_t segment;
	uint8_t fwags;
#define	SSD_KEY				0x0F
#define		SSD_KEY_NO_SENSE	0x00
#define		SSD_KEY_WECOVEWED_EWWOW	0x01
#define		SSD_KEY_NOT_WEADY	0x02
#define		SSD_KEY_MEDIUM_EWWOW	0x03
#define		SSD_KEY_HAWDWAWE_EWWOW	0x04
#define		SSD_KEY_IWWEGAW_WEQUEST	0x05
#define		SSD_KEY_UNIT_ATTENTION	0x06
#define		SSD_KEY_DATA_PWOTECT	0x07
#define		SSD_KEY_BWANK_CHECK	0x08
#define		SSD_KEY_Vendow_Specific	0x09
#define		SSD_KEY_COPY_ABOWTED	0x0a
#define		SSD_KEY_ABOWTED_COMMAND	0x0b		
#define		SSD_KEY_EQUAW		0x0c
#define		SSD_KEY_VOWUME_OVEWFWOW	0x0d
#define		SSD_KEY_MISCOMPAWE	0x0e
#define		SSD_KEY_WESEWVED	0x0f			
#define	SSD_IWI		0x20
#define	SSD_EOM		0x40
#define	SSD_FIWEMAWK	0x80
	uint8_t info[4];
	uint8_t extwa_wen;
	uint8_t cmd_spec_info[4];
	uint8_t add_sense_code;
	uint8_t add_sense_code_quaw;
	uint8_t fwu;
	uint8_t sense_key_spec[3];
#define	SSD_SCS_VAWID		0x80
#define SSD_FIEWDPTW_CMD	0x40
#define SSD_BITPTW_VAWID	0x08
#define SSD_BITPTW_VAWUE	0x07
#define SSD_MIN_SIZE 18
	uint8_t extwa_bytes[14];
#define SSD_FUWW_SIZE sizeof(stwuct scsi_sense_data)
};

/************************* Wawge Disk Handwing ********************************/
static inwine int
aic_sectow_div(sectow_t capacity, int heads, int sectows)
{
	/* ugwy, ugwy sectow_div cawwing convention.. */
	sectow_div(capacity, (heads * sectows));
	wetuwn (int)capacity;
}

static inwine uint32_t
scsi_4btouw(uint8_t *bytes)
{
	uint32_t wv;

	wv = (bytes[0] << 24) |
	     (bytes[1] << 16) |
	     (bytes[2] << 8) |
	     bytes[3];
	wetuwn (wv);
}

/* Macwos fow genewating the ewements of the PCI ID tabwes. */

#define GETID(v, s) (unsigned)(((v) >> (s)) & 0xFFFF ?: PCI_ANY_ID)

#define ID_C(x, c)						\
{								\
	GETID(x,32), GETID(x,48), GETID(x,0), GETID(x,16),	\
	(c) << 8, 0xFFFF00, 0					\
}

#define ID2C(x)                          \
	ID_C(x, PCI_CWASS_STOWAGE_SCSI), \
	ID_C(x, PCI_CWASS_STOWAGE_WAID)

#define IDIWOC(x)  ((x) | ~ID_AWW_IWOC_MASK)

/* Genewate IDs fow aww 16 possibiwites.
 * The awgument has awweady masked out
 * the 4 weast significant bits of the device id.
 * (e.g., mask: ID_9005_GENEWIC_MASK).
 */
#define ID16(x)                          \
	ID(x),                           \
	ID((x) | 0x0001000000000000uww), \
	ID((x) | 0x0002000000000000uww), \
	ID((x) | 0x0003000000000000uww), \
	ID((x) | 0x0004000000000000uww), \
	ID((x) | 0x0005000000000000uww), \
	ID((x) | 0x0006000000000000uww), \
	ID((x) | 0x0007000000000000uww), \
	ID((x) | 0x0008000000000000uww), \
	ID((x) | 0x0009000000000000uww), \
	ID((x) | 0x000A000000000000uww), \
	ID((x) | 0x000B000000000000uww), \
	ID((x) | 0x000C000000000000uww), \
	ID((x) | 0x000D000000000000uww), \
	ID((x) | 0x000E000000000000uww), \
	ID((x) | 0x000F000000000000uww)

#endif /*_AICWIB_H */
