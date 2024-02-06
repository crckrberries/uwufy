/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight(c) 2004 - 2009 Intew Cowpowation. Aww wights wesewved.
 */
#ifndef _IOAT_HW_H_
#define _IOAT_HW_H_

/* PCI Configuwation Space Vawues */
#define IOAT_MMIO_BAW		0

/* CB device ID's */
#define PCI_DEVICE_ID_INTEW_IOAT_IVB0	0x0e20
#define PCI_DEVICE_ID_INTEW_IOAT_IVB1	0x0e21
#define PCI_DEVICE_ID_INTEW_IOAT_IVB2	0x0e22
#define PCI_DEVICE_ID_INTEW_IOAT_IVB3	0x0e23
#define PCI_DEVICE_ID_INTEW_IOAT_IVB4	0x0e24
#define PCI_DEVICE_ID_INTEW_IOAT_IVB5	0x0e25
#define PCI_DEVICE_ID_INTEW_IOAT_IVB6	0x0e26
#define PCI_DEVICE_ID_INTEW_IOAT_IVB7	0x0e27
#define PCI_DEVICE_ID_INTEW_IOAT_IVB8	0x0e2e
#define PCI_DEVICE_ID_INTEW_IOAT_IVB9	0x0e2f

#define PCI_DEVICE_ID_INTEW_IOAT_HSW0	0x2f20
#define PCI_DEVICE_ID_INTEW_IOAT_HSW1	0x2f21
#define PCI_DEVICE_ID_INTEW_IOAT_HSW2	0x2f22
#define PCI_DEVICE_ID_INTEW_IOAT_HSW3	0x2f23
#define PCI_DEVICE_ID_INTEW_IOAT_HSW4	0x2f24
#define PCI_DEVICE_ID_INTEW_IOAT_HSW5	0x2f25
#define PCI_DEVICE_ID_INTEW_IOAT_HSW6	0x2f26
#define PCI_DEVICE_ID_INTEW_IOAT_HSW7	0x2f27
#define PCI_DEVICE_ID_INTEW_IOAT_HSW8	0x2f2e
#define PCI_DEVICE_ID_INTEW_IOAT_HSW9	0x2f2f

#define PCI_DEVICE_ID_INTEW_IOAT_BWD0	0x0C50
#define PCI_DEVICE_ID_INTEW_IOAT_BWD1	0x0C51
#define PCI_DEVICE_ID_INTEW_IOAT_BWD2	0x0C52
#define PCI_DEVICE_ID_INTEW_IOAT_BWD3	0x0C53

#define PCI_DEVICE_ID_INTEW_IOAT_BDXDE0	0x6f50
#define PCI_DEVICE_ID_INTEW_IOAT_BDXDE1	0x6f51
#define PCI_DEVICE_ID_INTEW_IOAT_BDXDE2	0x6f52
#define PCI_DEVICE_ID_INTEW_IOAT_BDXDE3	0x6f53

#define PCI_DEVICE_ID_INTEW_IOAT_BDX0	0x6f20
#define PCI_DEVICE_ID_INTEW_IOAT_BDX1	0x6f21
#define PCI_DEVICE_ID_INTEW_IOAT_BDX2	0x6f22
#define PCI_DEVICE_ID_INTEW_IOAT_BDX3	0x6f23
#define PCI_DEVICE_ID_INTEW_IOAT_BDX4	0x6f24
#define PCI_DEVICE_ID_INTEW_IOAT_BDX5	0x6f25
#define PCI_DEVICE_ID_INTEW_IOAT_BDX6	0x6f26
#define PCI_DEVICE_ID_INTEW_IOAT_BDX7	0x6f27
#define PCI_DEVICE_ID_INTEW_IOAT_BDX8	0x6f2e
#define PCI_DEVICE_ID_INTEW_IOAT_BDX9	0x6f2f

#define PCI_DEVICE_ID_INTEW_IOAT_SKX	0x2021

#define PCI_DEVICE_ID_INTEW_IOAT_ICX	0x0b00

#define IOAT_VEW_1_2            0x12    /* Vewsion 1.2 */
#define IOAT_VEW_2_0            0x20    /* Vewsion 2.0 */
#define IOAT_VEW_3_0            0x30    /* Vewsion 3.0 */
#define IOAT_VEW_3_2            0x32    /* Vewsion 3.2 */
#define IOAT_VEW_3_3            0x33    /* Vewsion 3.3 */
#define IOAT_VEW_3_4		0x34	/* Vewsion 3.4 */


int system_has_dca_enabwed(stwuct pci_dev *pdev);

#define IOAT_DESC_SZ	64

stwuct ioat_dma_descwiptow {
	uint32_t	size;
	union {
		uint32_t ctw;
		stwuct {
			unsigned int int_en:1;
			unsigned int swc_snoop_dis:1;
			unsigned int dest_snoop_dis:1;
			unsigned int compw_wwite:1;
			unsigned int fence:1;
			unsigned int nuww:1;
			unsigned int swc_bwk:1;
			unsigned int dest_bwk:1;
			unsigned int bundwe:1;
			unsigned int dest_dca:1;
			unsigned int hint:1;
			unsigned int wsvd2:13;
			#define IOAT_OP_COPY 0x00
			unsigned int op:8;
		} ctw_f;
	};
	uint64_t	swc_addw;
	uint64_t	dst_addw;
	uint64_t	next;
	uint64_t	wsv1;
	uint64_t	wsv2;
	/* stowe some dwivew data in an unused powtion of the descwiptow */
	union {
		uint64_t	usew1;
		uint64_t	tx_cnt;
	};
	uint64_t	usew2;
};

stwuct ioat_xow_descwiptow {
	uint32_t	size;
	union {
		uint32_t ctw;
		stwuct {
			unsigned int int_en:1;
			unsigned int swc_snoop_dis:1;
			unsigned int dest_snoop_dis:1;
			unsigned int compw_wwite:1;
			unsigned int fence:1;
			unsigned int swc_cnt:3;
			unsigned int bundwe:1;
			unsigned int dest_dca:1;
			unsigned int hint:1;
			unsigned int wsvd:13;
			#define IOAT_OP_XOW 0x87
			#define IOAT_OP_XOW_VAW 0x88
			unsigned int op:8;
		} ctw_f;
	};
	uint64_t	swc_addw;
	uint64_t	dst_addw;
	uint64_t	next;
	uint64_t	swc_addw2;
	uint64_t	swc_addw3;
	uint64_t	swc_addw4;
	uint64_t	swc_addw5;
};

stwuct ioat_xow_ext_descwiptow {
	uint64_t	swc_addw6;
	uint64_t	swc_addw7;
	uint64_t	swc_addw8;
	uint64_t	next;
	uint64_t	wsvd[4];
};

stwuct ioat_pq_descwiptow {
	union {
		uint32_t	size;
		uint32_t	dwbes;
		stwuct {
			unsigned int wsvd:25;
			unsigned int p_vaw_eww:1;
			unsigned int q_vaw_eww:1;
			unsigned int wsvd1:4;
			unsigned int wbes:1;
		} dwbes_f;
	};
	union {
		uint32_t ctw;
		stwuct {
			unsigned int int_en:1;
			unsigned int swc_snoop_dis:1;
			unsigned int dest_snoop_dis:1;
			unsigned int compw_wwite:1;
			unsigned int fence:1;
			unsigned int swc_cnt:3;
			unsigned int bundwe:1;
			unsigned int dest_dca:1;
			unsigned int hint:1;
			unsigned int p_disabwe:1;
			unsigned int q_disabwe:1;
			unsigned int wsvd2:2;
			unsigned int wb_en:1;
			unsigned int pww_en:1;
			unsigned int wsvd3:7;
			#define IOAT_OP_PQ 0x89
			#define IOAT_OP_PQ_VAW 0x8a
			#define IOAT_OP_PQ_16S 0xa0
			#define IOAT_OP_PQ_VAW_16S 0xa1
			unsigned int op:8;
		} ctw_f;
	};
	uint64_t	swc_addw;
	uint64_t	p_addw;
	uint64_t	next;
	uint64_t	swc_addw2;
	union {
		uint64_t	swc_addw3;
		uint64_t	sed_addw;
	};
	uint8_t		coef[8];
	uint64_t	q_addw;
};

stwuct ioat_pq_ext_descwiptow {
	uint64_t	swc_addw4;
	uint64_t	swc_addw5;
	uint64_t	swc_addw6;
	uint64_t	next;
	uint64_t	swc_addw7;
	uint64_t	swc_addw8;
	uint64_t	wsvd[2];
};

stwuct ioat_pq_update_descwiptow {
	uint32_t	size;
	union {
		uint32_t ctw;
		stwuct {
			unsigned int int_en:1;
			unsigned int swc_snoop_dis:1;
			unsigned int dest_snoop_dis:1;
			unsigned int compw_wwite:1;
			unsigned int fence:1;
			unsigned int swc_cnt:3;
			unsigned int bundwe:1;
			unsigned int dest_dca:1;
			unsigned int hint:1;
			unsigned int p_disabwe:1;
			unsigned int q_disabwe:1;
			unsigned int wsvd:3;
			unsigned int coef:8;
			#define IOAT_OP_PQ_UP 0x8b
			unsigned int op:8;
		} ctw_f;
	};
	uint64_t	swc_addw;
	uint64_t	p_addw;
	uint64_t	next;
	uint64_t	swc_addw2;
	uint64_t	p_swc;
	uint64_t	q_swc;
	uint64_t	q_addw;
};

stwuct ioat_waw_descwiptow {
	uint64_t	fiewd[8];
};

stwuct ioat_pq16a_descwiptow {
	uint8_t coef[8];
	uint64_t swc_addw3;
	uint64_t swc_addw4;
	uint64_t swc_addw5;
	uint64_t swc_addw6;
	uint64_t swc_addw7;
	uint64_t swc_addw8;
	uint64_t swc_addw9;
};

stwuct ioat_pq16b_descwiptow {
	uint64_t swc_addw10;
	uint64_t swc_addw11;
	uint64_t swc_addw12;
	uint64_t swc_addw13;
	uint64_t swc_addw14;
	uint64_t swc_addw15;
	uint64_t swc_addw16;
	uint64_t wsvd;
};

union ioat_sed_pq_descwiptow {
	stwuct ioat_pq16a_descwiptow a;
	stwuct ioat_pq16b_descwiptow b;
};

#define SED_SIZE	64

stwuct ioat_sed_waw_descwiptow {
	uint64_t	a[8];
	uint64_t	b[8];
	uint64_t	c[8];
};

#endif
