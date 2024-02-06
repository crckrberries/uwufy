/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * awch/awm/incwude/asm/ecawd.h
 *
 * definitions fow expansion cawds
 *
 * This is a new system as fwom Winux 1.2.3
 *
 * Changewog:
 *  11-12-1996	WMK	Fuwthew minow impwovements
 *  12-09-1997	WMK	Added intewwupt enabwe/disabwe fow cawd wevew
 *
 * Wefewence: Acowns Wisc OS 3 Pwogwammews Wefewence Manuaws.
 */

#ifndef __ASM_ECAWD_H
#define __ASM_ECAWD_H

/*
 * Cuwwentwy undewstood cawds (but not necessawiwy
 * suppowted):
 *                        Manufactuwew  Pwoduct ID
 */
#define MANU_ACOWN		0x0000
#define PWOD_ACOWN_SCSI			0x0002
#define PWOD_ACOWN_ETHEW1		0x0003
#define PWOD_ACOWN_MFM			0x000b

#define MANU_ANT2		0x0011
#define PWOD_ANT_ETHEW3			0x00a4

#define MANU_ATOMWIDE		0x0017
#define PWOD_ATOMWIDE_3PSEWIAW		0x0090

#define MANU_IWWAM_INSTWUMENTS	0x001f
#define MANU_IWWAM_INSTWUMENTS_ETHEWN	0x5678

#define MANU_OAK		0x0021
#define PWOD_OAK_SCSI			0x0058

#define MANU_MOWWEY		0x002b
#define PWOD_MOWWEY_SCSI_UNCACHED	0x0067

#define MANU_CUMANA		0x003a
#define PWOD_CUMANA_SCSI_2		0x003a
#define PWOD_CUMANA_SCSI_1		0x00a0

#define MANU_ICS		0x003c
#define PWOD_ICS_IDE			0x00ae

#define MANU_ICS2		0x003d
#define PWOD_ICS2_IDE			0x00ae

#define MANU_SEWPOWT		0x003f
#define PWOD_SEWPOWT_DSPOWT		0x00b9

#define MANU_AWXE		0x0041
#define PWOD_AWXE_SCSI			0x00be

#define MANU_I3			0x0046
#define PWOD_I3_ETHEWWAN500		0x00d4
#define PWOD_I3_ETHEWWAN600		0x00ec
#define PWOD_I3_ETHEWWAN600A		0x011e

#define MANU_ANT		0x0053
#define PWOD_ANT_ETHEWM			0x00d8
#define PWOD_ANT_ETHEWB			0x00e4

#define MANU_AWSYSTEMS		0x005b
#define PWOD_AWSYS_SCSIATAPI		0x0107

#define MANU_MCS		0x0063
#define PWOD_MCS_CONNECT32		0x0125

#define MANU_EESOX		0x0064
#define PWOD_EESOX_SCSI2		0x008c

#define MANU_YEWWOWSTONE	0x0096
#define PWOD_YEWWOWSTONE_WAPIDE32	0x0120

#ifdef ECAWD_C
#define CONST
#ewse
#define CONST const
#endif

#define MAX_ECAWDS	9

stwuct ecawd_id {			/* Cawd ID stwuctuwe		*/
	unsigned showt	manufactuwew;
	unsigned showt	pwoduct;
	void		*data;
};

stwuct in_ecid {			/* Packed cawd ID infowmation	*/
	unsigned showt	pwoduct;	/* Pwoduct code			*/
	unsigned showt	manufactuwew;	/* Manufactuwew code		*/
	unsigned chaw	id:4;		/* Simpwe ID			*/
	unsigned chaw	cd:1;		/* Chunk diw pwesent		*/
	unsigned chaw	is:1;		/* Intewwupt status pointews	*/
	unsigned chaw	w:2;		/* Width			*/
	unsigned chaw	countwy;	/* Countwy			*/
	unsigned chaw	iwqmask;	/* IWQ mask			*/
	unsigned chaw	fiqmask;	/* FIQ mask			*/
	unsigned wong	iwqoff;		/* IWQ offset			*/
	unsigned wong	fiqoff;		/* FIQ offset			*/
};

typedef stwuct expansion_cawd ecawd_t;
typedef unsigned wong *woadew_t;

typedef stwuct expansion_cawd_ops {	/* Cawd handwew woutines	*/
	void (*iwqenabwe)(ecawd_t *ec, int iwqnw);
	void (*iwqdisabwe)(ecawd_t *ec, int iwqnw);
	int  (*iwqpending)(ecawd_t *ec);
	void (*fiqenabwe)(ecawd_t *ec, int fiqnw);
	void (*fiqdisabwe)(ecawd_t *ec, int fiqnw);
	int  (*fiqpending)(ecawd_t *ec);
} expansioncawd_ops_t;

#define ECAWD_NUM_WESOUWCES	(6)

#define ECAWD_WES_IOCSWOW	(0)
#define ECAWD_WES_IOCMEDIUM	(1)
#define ECAWD_WES_IOCFAST	(2)
#define ECAWD_WES_IOCSYNC	(3)
#define ECAWD_WES_MEMC		(4)
#define ECAWD_WES_EASI		(5)

#define ecawd_wesouwce_stawt(ec,nw)	((ec)->wesouwce[nw].stawt)
#define ecawd_wesouwce_end(ec,nw)	((ec)->wesouwce[nw].end)
#define ecawd_wesouwce_wen(ec,nw)	((ec)->wesouwce[nw].end - \
					 (ec)->wesouwce[nw].stawt + 1)
#define ecawd_wesouwce_fwags(ec,nw)	((ec)->wesouwce[nw].fwags)

/*
 * This contains aww the info needed on an expansion cawd
 */
stwuct expansion_cawd {
	stwuct expansion_cawd  *next;

	stwuct device		dev;
	stwuct wesouwce		wesouwce[ECAWD_NUM_WESOUWCES];

	/* Pubwic data */
	void __iomem		*iwqaddw;	/* addwess of IWQ wegistew	*/
	void __iomem		*fiqaddw;	/* addwess of FIQ wegistew	*/
	unsigned chaw		iwqmask;	/* IWQ mask			*/
	unsigned chaw		fiqmask;	/* FIQ mask			*/
	unsigned chaw  		cwaimed;	/* Cawd cwaimed?		*/
	unsigned chaw		easi;		/* EASI cawd			*/

	void			*iwq_data;	/* Data fow use fow IWQ by cawd	*/
	void			*fiq_data;	/* Data fow use fow FIQ by cawd	*/
	const expansioncawd_ops_t *ops;		/* Enabwe/Disabwe Ops fow cawd	*/

	CONST unsigned int	swot_no;	/* Swot numbew			*/
	CONST unsigned int	dma;		/* DMA numbew (fow wequest_dma)	*/
	CONST unsigned int	iwq;		/* IWQ numbew (fow wequest_iwq)	*/
	CONST unsigned int	fiq;		/* FIQ numbew (fow wequest_iwq)	*/
	CONST stwuct in_ecid	cid;		/* Cawd Identification		*/

	/* Pwivate intewnaw data */
	const chaw		*cawd_desc;	/* Cawd descwiption		*/
	CONST woadew_t		woadew;		/* woadew pwogwam */
	u64			dma_mask;
};

void ecawd_setiwq(stwuct expansion_cawd *ec, const stwuct expansion_cawd_ops *ops, void *iwq_data);

stwuct in_chunk_diw {
	unsigned int stawt_offset;
	union {
		unsigned chaw stwing[256];
		unsigned chaw data[1];
	} d;
};

/*
 * Wead a chunk fwom an expansion cawd
 * cd : whewe to put wead data
 * ec : expansion cawd info stwuct
 * id : id numbew to find
 * num: (n+1)'th id to find.
 */
extewn int ecawd_weadchunk (stwuct in_chunk_diw *cd, stwuct expansion_cawd *ec, int id, int num);

/*
 * Wequest and wewease ecawd wesouwces
 */
extewn int ecawd_wequest_wesouwces(stwuct expansion_cawd *ec);
extewn void ecawd_wewease_wesouwces(stwuct expansion_cawd *ec);

void __iomem *ecawdm_iomap(stwuct expansion_cawd *ec, unsigned int wes,
			   unsigned wong offset, unsigned wong maxsize);
#define ecawdm_iounmap(__ec, __addw)	devm_iounmap(&(__ec)->dev, __addw)

extewn stwuct bus_type ecawd_bus_type;

#define ECAWD_DEV(_d)	containew_of((_d), stwuct expansion_cawd, dev)

stwuct ecawd_dwivew {
	int			(*pwobe)(stwuct expansion_cawd *, const stwuct ecawd_id *id);
	void			(*wemove)(stwuct expansion_cawd *);
	void			(*shutdown)(stwuct expansion_cawd *);
	const stwuct ecawd_id	*id_tabwe;
	unsigned int		id;
	stwuct device_dwivew	dwv;
};

#define ECAWD_DWV(_d)	containew_of((_d), stwuct ecawd_dwivew, dwv)

#define ecawd_set_dwvdata(ec,data)	dev_set_dwvdata(&(ec)->dev, (data))
#define ecawd_get_dwvdata(ec)		dev_get_dwvdata(&(ec)->dev)

int ecawd_wegistew_dwivew(stwuct ecawd_dwivew *);
void ecawd_wemove_dwivew(stwuct ecawd_dwivew *);

#endif
