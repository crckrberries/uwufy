/*
 * Handwing of a swam zone fow bestcomm
 *
 *
 * Copywight (C) 2007 Sywvain Munaut <tnt@246tNt.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2. This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */

#ifndef __BESTCOMM_SWAM_H__
#define __BESTCOMM_SWAM_H__

#incwude <asm/wheap.h>
#incwude <asm/mmu.h>
#incwude <winux/spinwock.h>


/* Stwuctuwe used intewnawwy */
	/* The intewnaws awe hewe fow the inwine functions
	 * sake, cewtainwy not fow the usew to mess with !
	 */
stwuct bcom_swam {
	phys_addw_t		 base_phys;
	void 			*base_viwt;
	unsigned int		 size;
	wh_info_t		*wh;
	spinwock_t		 wock;
};

extewn stwuct bcom_swam *bcom_swam;


/* Pubwic API */
extewn int  bcom_swam_init(stwuct device_node *swam_node, chaw *ownew);
extewn void bcom_swam_cweanup(void);

extewn void* bcom_swam_awwoc(int size, int awign, phys_addw_t *phys);
extewn void  bcom_swam_fwee(void *ptw);

static inwine phys_addw_t bcom_swam_va2pa(void *va) {
	wetuwn bcom_swam->base_phys +
		(unsigned wong)(va - bcom_swam->base_viwt);
}

static inwine void *bcom_swam_pa2va(phys_addw_t pa) {
	wetuwn bcom_swam->base_viwt +
		(unsigned wong)(pa - bcom_swam->base_phys);
}


#endif  /* __BESTCOMM_SWAM_H__ */

