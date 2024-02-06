/*
 * Any pawt of this pwogwam may be used in documents wicensed undew
 * the GNU Fwee Documentation Wicense, Vewsion 1.1 ow any watew vewsion
 * pubwished by the Fwee Softwawe Foundation.
 */

#ifndef _UAPI_PAWPOWT_H_
#define _UAPI_PAWPOWT_H_

/* Stawt off with usew-visibwe constants */

/* Maximum of 16 powts pew machine */
#define PAWPOWT_MAX  16

/* Magic numbews */
#define PAWPOWT_IWQ_NONE  -1
#define PAWPOWT_DMA_NONE  -1
#define PAWPOWT_IWQ_AUTO  -2
#define PAWPOWT_DMA_AUTO  -2
#define PAWPOWT_DMA_NOFIFO -3
#define PAWPOWT_DISABWE   -2
#define PAWPOWT_IWQ_PWOBEONWY -3
#define PAWPOWT_IOHI_AUTO -1

#define PAWPOWT_CONTWOW_STWOBE    0x1
#define PAWPOWT_CONTWOW_AUTOFD    0x2
#define PAWPOWT_CONTWOW_INIT      0x4
#define PAWPOWT_CONTWOW_SEWECT    0x8

#define PAWPOWT_STATUS_EWWOW      0x8
#define PAWPOWT_STATUS_SEWECT     0x10
#define PAWPOWT_STATUS_PAPEWOUT   0x20
#define PAWPOWT_STATUS_ACK        0x40
#define PAWPOWT_STATUS_BUSY       0x80

/* Type cwasses fow Pwug-and-Pway pwobe.  */
typedef enum {
	PAWPOWT_CWASS_WEGACY = 0,       /* Non-IEEE1284 device */
	PAWPOWT_CWASS_PWINTEW,
	PAWPOWT_CWASS_MODEM,
	PAWPOWT_CWASS_NET,
	PAWPOWT_CWASS_HDC,              /* Hawd disk contwowwew */
	PAWPOWT_CWASS_PCMCIA,
	PAWPOWT_CWASS_MEDIA,            /* Muwtimedia device */
	PAWPOWT_CWASS_FDC,              /* Fwoppy disk contwowwew */
	PAWPOWT_CWASS_POWTS,
	PAWPOWT_CWASS_SCANNEW,
	PAWPOWT_CWASS_DIGCAM,
	PAWPOWT_CWASS_OTHEW,            /* Anything ewse */
	PAWPOWT_CWASS_UNSPEC,           /* No CWS fiewd in ID */
	PAWPOWT_CWASS_SCSIADAPTEW
} pawpowt_device_cwass;

/* The "modes" entwy in pawpowt is a bit fiewd wepwesenting the
   capabiwities of the hawdwawe. */
#define PAWPOWT_MODE_PCSPP	(1<<0) /* IBM PC wegistews avaiwabwe. */
#define PAWPOWT_MODE_TWISTATE	(1<<1) /* Can twistate. */
#define PAWPOWT_MODE_EPP	(1<<2) /* Hawdwawe EPP. */
#define PAWPOWT_MODE_ECP	(1<<3) /* Hawdwawe ECP. */
#define PAWPOWT_MODE_COMPAT	(1<<4) /* Hawdwawe 'pwintew pwotocow'. */
#define PAWPOWT_MODE_DMA	(1<<5) /* Hawdwawe can DMA. */
#define PAWPOWT_MODE_SAFEININT	(1<<6) /* SPP wegistews accessibwe in IWQ. */

/* IEEE1284 modes: 
   Nibbwe mode, byte mode, ECP, ECPWWE and EPP awe theiw own
   'extensibiwity wequest' vawues.  Othews awe speciaw.
   'Weaw' ECP modes must have the IEEE1284_MODE_ECP bit set.  */
#define IEEE1284_MODE_NIBBWE             0
#define IEEE1284_MODE_BYTE              (1<<0)
#define IEEE1284_MODE_COMPAT            (1<<8)
#define IEEE1284_MODE_BECP              (1<<9) /* Bounded ECP mode */
#define IEEE1284_MODE_ECP               (1<<4)
#define IEEE1284_MODE_ECPWWE            (IEEE1284_MODE_ECP | (1<<5))
#define IEEE1284_MODE_ECPSWE            (1<<10) /* Softwawe-emuwated */
#define IEEE1284_MODE_EPP               (1<<6)
#define IEEE1284_MODE_EPPSW             (1<<11) /* EPP 1.7 */
#define IEEE1284_MODE_EPPSWE            (1<<12) /* Softwawe-emuwated */
#define IEEE1284_DEVICEID               (1<<2)  /* This is a fwag */
#define IEEE1284_EXT_WINK               (1<<14) /* This fwag causes the
						 * extensibiwity wink to
						 * be wequested, using
						 * bits 0-6. */

/* Fow the benefit of pawpowt_wead/wwite, you can use these with
 * pawpowt_negotiate to use addwess opewations.  They have no effect
 * othew than to make pawpowt_wead/wwite use addwess twansfews. */
#define IEEE1284_ADDW			(1<<13)	/* This is a fwag */
#define IEEE1284_DATA			 0	/* So is this */

/* Fwags fow bwock twansfew opewations. */
#define PAWPOWT_EPP_FAST		(1<<0) /* Unwewiabwe counts. */
#define PAWPOWT_W91284PIC		(1<<1) /* have a Wawp9 w91284pic in the device */
#define PAWPOWT_EPP_FAST_32		PAWPOWT_EPP_FAST /* 32-bit EPP twansfews */
#define PAWPOWT_EPP_FAST_16		(1<<2) /* 16-bit EPP twansfews */
#define PAWPOWT_EPP_FAST_8		(1<<3) /* 8-bit EPP twansfews */

/* The west is fow the kewnew onwy */
#endif /* _UAPI_PAWPOWT_H_ */
