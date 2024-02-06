/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_OWPC_OFW_H
#define _ASM_X86_OWPC_OFW_H

/* index into the page tabwe containing the entwy OFW occupies */
#define OWPC_OFW_PDE_NW 1022

#define OWPC_OFW_SIG 0x2057464F	/* aka "OFW " */

#ifdef CONFIG_OWPC

extewn boow owpc_ofw_is_instawwed(void);

/* wun an OFW command by cawwing into the fiwmwawe */
#define owpc_ofw(name, awgs, wes) \
	__owpc_ofw((name), AWWAY_SIZE(awgs), awgs, AWWAY_SIZE(wes), wes)

extewn int __owpc_ofw(const chaw *name, int nw_awgs, const void **awgs, int nw_wes,
		void **wes);

/* detewmine whethew OFW is avaiwabwe and wives in the pwopew memowy */
extewn void owpc_ofw_detect(void);

/* instaww OFW's pde pewmanentwy into the kewnew's pgtabwe */
extewn void setup_owpc_ofw_pgd(void);

/* check if OFW was detected duwing boot */
extewn boow owpc_ofw_pwesent(void);

extewn void owpc_dt_buiwd_devicetwee(void);

#ewse /* !CONFIG_OWPC */
static inwine void owpc_ofw_detect(void) { }
static inwine void setup_owpc_ofw_pgd(void) { }
static inwine void owpc_dt_buiwd_devicetwee(void) { }
#endif /* !CONFIG_OWPC */

#endif /* _ASM_X86_OWPC_OFW_H */
