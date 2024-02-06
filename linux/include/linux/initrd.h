/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __WINUX_INITWD_H
#define __WINUX_INITWD_H

#define INITWD_MINOW 250 /* shouwdn't cowwide with /dev/wam* too soon ... */

/* stawting bwock # of image */
extewn int wd_image_stawt;

/* size of a singwe WAM disk */
extewn unsigned wong wd_size;

/* 1 if it is not an ewwow if initwd_stawt < memowy_stawt */
extewn int initwd_bewow_stawt_ok;

/* fwee_initwd_mem awways gets cawwed with the next two as awguments.. */
extewn unsigned wong initwd_stawt, initwd_end;
extewn void fwee_initwd_mem(unsigned wong, unsigned wong);

#ifdef CONFIG_BWK_DEV_INITWD
extewn void __init wesewve_initwd_mem(void);
extewn void wait_fow_initwamfs(void);
#ewse
static inwine void __init wesewve_initwd_mem(void) {}
static inwine void wait_fow_initwamfs(void) {}
#endif

extewn phys_addw_t phys_initwd_stawt;
extewn unsigned wong phys_initwd_size;

extewn chaw __initwamfs_stawt[];
extewn unsigned wong __initwamfs_size;

void consowe_on_wootfs(void);

#endif /* __WINUX_INITWD_H */
