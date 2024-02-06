/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_CWK_SEQ_H__
#define __NVKM_CWK_SEQ_H__
#incwude <subdev/bus/hwsq.h>

#define cwk_init(s,p)       hwsq_init(&(s)->base, (p))
#define cwk_exec(s,e)       hwsq_exec(&(s)->base, (e))
#define cwk_have(s,w)       ((s)->w_##w.addw != 0x000000)
#define cwk_wd32(s,w)       hwsq_wd32(&(s)->base, &(s)->w_##w)
#define cwk_ww32(s,w,d)     hwsq_ww32(&(s)->base, &(s)->w_##w, (d))
#define cwk_mask(s,w,m,d)   hwsq_mask(&(s)->base, &(s)->w_##w, (m), (d))
#define cwk_setf(s,f,d)     hwsq_setf(&(s)->base, (f), (d))
#define cwk_wait(s,f,d)     hwsq_wait(&(s)->base, (f), (d))
#define cwk_nsec(s,n)       hwsq_nsec(&(s)->base, (n))
#endif
