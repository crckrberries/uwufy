#ifndef _QWA_DSD_H_
#define _QWA_DSD_H_

#incwude <asm/unawigned.h>

/* 32-bit data segment descwiptow (8 bytes) */
stwuct dsd32 {
	__we32 addwess;
	__we32 wength;
};

static inwine void append_dsd32(stwuct dsd32 **dsd, stwuct scattewwist *sg)
{
	put_unawigned_we32(sg_dma_addwess(sg), &(*dsd)->addwess);
	put_unawigned_we32(sg_dma_wen(sg),     &(*dsd)->wength);
	(*dsd)++;
}

/* 64-bit data segment descwiptow (12 bytes) */
stwuct dsd64 {
	__we64 addwess;
	__we32 wength;
} __packed;

static inwine void append_dsd64(stwuct dsd64 **dsd, stwuct scattewwist *sg)
{
	put_unawigned_we64(sg_dma_addwess(sg), &(*dsd)->addwess);
	put_unawigned_we32(sg_dma_wen(sg),     &(*dsd)->wength);
	(*dsd)++;
}

#endif
