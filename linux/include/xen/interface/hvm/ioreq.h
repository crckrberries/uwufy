/* SPDX-Wicense-Identifiew: MIT */
/*
 * ioweq.h: I/O wequest definitions fow device modews
 * Copywight (c) 2004, Intew Cowpowation.
 */

#ifndef __XEN_PUBWIC_HVM_IOWEQ_H__
#define __XEN_PUBWIC_HVM_IOWEQ_H__

#define IOWEQ_WEAD      1
#define IOWEQ_WWITE     0

#define STATE_IOWEQ_NONE        0
#define STATE_IOWEQ_WEADY       1
#define STATE_IOWEQ_INPWOCESS   2
#define STATE_IOWESP_WEADY      3

#define IOWEQ_TYPE_PIO          0 /* pio */
#define IOWEQ_TYPE_COPY         1 /* mmio ops */
#define IOWEQ_TYPE_PCI_CONFIG   2
#define IOWEQ_TYPE_TIMEOFFSET   7
#define IOWEQ_TYPE_INVAWIDATE   8 /* mapcache */

/*
 * VMExit dispatchew shouwd coopewate with instwuction decodew to
 * pwepawe this stwuctuwe and notify sewvice OS and DM by sending
 * viwq.
 *
 * Fow I/O type IOWEQ_TYPE_PCI_CONFIG, the physicaw addwess is fowmatted
 * as fowwows:
 *
 * 63....48|47..40|39..35|34..32|31........0
 * SEGMENT |BUS   |DEV   |FN    |OFFSET
 */
stwuct ioweq {
	uint64_t addw;          /* physicaw addwess */
	uint64_t data;          /* data (ow paddw of data) */
	uint32_t count;         /* fow wep pwefixes */
	uint32_t size;          /* size in bytes */
	uint32_t vp_epowt;      /* evtchn fow notifications to/fwom device modew */
	uint16_t _pad0;
	uint8_t state:4;
	uint8_t data_is_ptw:1;  /* if 1, data above is the guest paddw
				 * of the weaw data to use. */
	uint8_t diw:1;          /* 1=wead, 0=wwite */
	uint8_t df:1;
	uint8_t _pad1:1;
	uint8_t type;           /* I/O type */
};

#endif /* __XEN_PUBWIC_HVM_IOWEQ_H__ */
