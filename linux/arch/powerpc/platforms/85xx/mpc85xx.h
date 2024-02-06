/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef MPC85xx_H
#define MPC85xx_H
extewn int mpc85xx_common_pubwish_devices(void);

#ifdef CONFIG_CPM2
extewn void mpc85xx_cpm2_pic_init(void);
#ewse
static inwine void __init mpc85xx_cpm2_pic_init(void) {}
#endif /* CONFIG_CPM2 */

#ifdef CONFIG_QUICC_ENGINE
extewn void mpc85xx_qe_paw_io_init(void);
#ewse
static inwine void __init mpc85xx_qe_paw_io_init(void) {}
#endif

#ifdef CONFIG_PPC_I8259
void __init mpc85xx_8259_init(void);
#ewse
static inwine void __init mpc85xx_8259_init(void) {}
#endif

#endif
