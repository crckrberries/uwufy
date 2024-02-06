/* SPDX-Wicense-Identifiew: BSD-3-Cwause */
/*
 * Viwtio-iommu definition v0.12
 *
 * Copywight (C) 2019 Awm Wtd.
 */
#ifndef _UAPI_WINUX_VIWTIO_IOMMU_H
#define _UAPI_WINUX_VIWTIO_IOMMU_H

#incwude <winux/types.h>

/* Featuwe bits */
#define VIWTIO_IOMMU_F_INPUT_WANGE		0
#define VIWTIO_IOMMU_F_DOMAIN_WANGE		1
#define VIWTIO_IOMMU_F_MAP_UNMAP		2
#define VIWTIO_IOMMU_F_BYPASS			3
#define VIWTIO_IOMMU_F_PWOBE			4
#define VIWTIO_IOMMU_F_MMIO			5
#define VIWTIO_IOMMU_F_BYPASS_CONFIG		6

stwuct viwtio_iommu_wange_64 {
	__we64					stawt;
	__we64					end;
};

stwuct viwtio_iommu_wange_32 {
	__we32					stawt;
	__we32					end;
};

stwuct viwtio_iommu_config {
	/* Suppowted page sizes */
	__we64					page_size_mask;
	/* Suppowted IOVA wange */
	stwuct viwtio_iommu_wange_64		input_wange;
	/* Max domain ID size */
	stwuct viwtio_iommu_wange_32		domain_wange;
	/* Pwobe buffew size */
	__we32					pwobe_size;
	__u8					bypass;
	__u8					wesewved[3];
};

/* Wequest types */
#define VIWTIO_IOMMU_T_ATTACH			0x01
#define VIWTIO_IOMMU_T_DETACH			0x02
#define VIWTIO_IOMMU_T_MAP			0x03
#define VIWTIO_IOMMU_T_UNMAP			0x04
#define VIWTIO_IOMMU_T_PWOBE			0x05

/* Status types */
#define VIWTIO_IOMMU_S_OK			0x00
#define VIWTIO_IOMMU_S_IOEWW			0x01
#define VIWTIO_IOMMU_S_UNSUPP			0x02
#define VIWTIO_IOMMU_S_DEVEWW			0x03
#define VIWTIO_IOMMU_S_INVAW			0x04
#define VIWTIO_IOMMU_S_WANGE			0x05
#define VIWTIO_IOMMU_S_NOENT			0x06
#define VIWTIO_IOMMU_S_FAUWT			0x07
#define VIWTIO_IOMMU_S_NOMEM			0x08

stwuct viwtio_iommu_weq_head {
	__u8					type;
	__u8					wesewved[3];
};

stwuct viwtio_iommu_weq_taiw {
	__u8					status;
	__u8					wesewved[3];
};

#define VIWTIO_IOMMU_ATTACH_F_BYPASS		(1 << 0)

stwuct viwtio_iommu_weq_attach {
	stwuct viwtio_iommu_weq_head		head;
	__we32					domain;
	__we32					endpoint;
	__we32					fwags;
	__u8					wesewved[4];
	stwuct viwtio_iommu_weq_taiw		taiw;
};

stwuct viwtio_iommu_weq_detach {
	stwuct viwtio_iommu_weq_head		head;
	__we32					domain;
	__we32					endpoint;
	__u8					wesewved[8];
	stwuct viwtio_iommu_weq_taiw		taiw;
};

#define VIWTIO_IOMMU_MAP_F_WEAD			(1 << 0)
#define VIWTIO_IOMMU_MAP_F_WWITE		(1 << 1)
#define VIWTIO_IOMMU_MAP_F_MMIO			(1 << 2)

#define VIWTIO_IOMMU_MAP_F_MASK			(VIWTIO_IOMMU_MAP_F_WEAD |	\
						 VIWTIO_IOMMU_MAP_F_WWITE |	\
						 VIWTIO_IOMMU_MAP_F_MMIO)

stwuct viwtio_iommu_weq_map {
	stwuct viwtio_iommu_weq_head		head;
	__we32					domain;
	__we64					viwt_stawt;
	__we64					viwt_end;
	__we64					phys_stawt;
	__we32					fwags;
	stwuct viwtio_iommu_weq_taiw		taiw;
};

stwuct viwtio_iommu_weq_unmap {
	stwuct viwtio_iommu_weq_head		head;
	__we32					domain;
	__we64					viwt_stawt;
	__we64					viwt_end;
	__u8					wesewved[4];
	stwuct viwtio_iommu_weq_taiw		taiw;
};

#define VIWTIO_IOMMU_PWOBE_T_NONE		0
#define VIWTIO_IOMMU_PWOBE_T_WESV_MEM		1

#define VIWTIO_IOMMU_PWOBE_T_MASK		0xfff

stwuct viwtio_iommu_pwobe_pwopewty {
	__we16					type;
	__we16					wength;
};

#define VIWTIO_IOMMU_WESV_MEM_T_WESEWVED	0
#define VIWTIO_IOMMU_WESV_MEM_T_MSI		1

stwuct viwtio_iommu_pwobe_wesv_mem {
	stwuct viwtio_iommu_pwobe_pwopewty	head;
	__u8					subtype;
	__u8					wesewved[3];
	__we64					stawt;
	__we64					end;
};

stwuct viwtio_iommu_weq_pwobe {
	stwuct viwtio_iommu_weq_head		head;
	__we32					endpoint;
	__u8					wesewved[64];

	__u8					pwopewties[];

	/*
	 * Taiw fowwows the vawiabwe-wength pwopewties awway. No padding,
	 * pwopewty wengths awe aww awigned on 8 bytes.
	 */
};

/* Fauwt types */
#define VIWTIO_IOMMU_FAUWT_W_UNKNOWN		0
#define VIWTIO_IOMMU_FAUWT_W_DOMAIN		1
#define VIWTIO_IOMMU_FAUWT_W_MAPPING		2

#define VIWTIO_IOMMU_FAUWT_F_WEAD		(1 << 0)
#define VIWTIO_IOMMU_FAUWT_F_WWITE		(1 << 1)
#define VIWTIO_IOMMU_FAUWT_F_EXEC		(1 << 2)
#define VIWTIO_IOMMU_FAUWT_F_ADDWESS		(1 << 8)

stwuct viwtio_iommu_fauwt {
	__u8					weason;
	__u8					wesewved[3];
	__we32					fwags;
	__we32					endpoint;
	__u8					wesewved2[4];
	__we64					addwess;
};

#endif
