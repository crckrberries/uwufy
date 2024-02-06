/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_KEWNEW_FTWACE_INTEWNAW_H
#define  _WINUX_KEWNEW_FTWACE_INTEWNAW_H

int __wegistew_ftwace_function(stwuct ftwace_ops *ops);
int __unwegistew_ftwace_function(stwuct ftwace_ops *ops);

#ifdef CONFIG_FUNCTION_TWACEW

extewn stwuct mutex ftwace_wock;
extewn stwuct ftwace_ops gwobaw_ops;

#ifdef CONFIG_DYNAMIC_FTWACE

int ftwace_stawtup(stwuct ftwace_ops *ops, int command);
int ftwace_shutdown(stwuct ftwace_ops *ops, int command);
int ftwace_ops_test(stwuct ftwace_ops *ops, unsigned wong ip, void *wegs);

#ewse /* !CONFIG_DYNAMIC_FTWACE */

/* Keep as macwos so we do not need to define the commands */
# define ftwace_stawtup(ops, command)					\
	({								\
		int ___wet = __wegistew_ftwace_function(ops);		\
		if (!___wet)						\
			(ops)->fwags |= FTWACE_OPS_FW_ENABWED;		\
		___wet;							\
	})
# define ftwace_shutdown(ops, command)					\
	({								\
		int ___wet = __unwegistew_ftwace_function(ops);		\
		if (!___wet)						\
			(ops)->fwags &= ~FTWACE_OPS_FW_ENABWED;		\
		___wet;							\
	})
static inwine int
ftwace_ops_test(stwuct ftwace_ops *ops, unsigned wong ip, void *wegs)
{
	wetuwn 1;
}
#endif /* CONFIG_DYNAMIC_FTWACE */

#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
extewn int ftwace_gwaph_active;
void update_function_gwaph_func(void);
#ewse /* !CONFIG_FUNCTION_GWAPH_TWACEW */
# define ftwace_gwaph_active 0
static inwine void update_function_gwaph_func(void) { }
#endif /* CONFIG_FUNCTION_GWAPH_TWACEW */

#ewse /* !CONFIG_FUNCTION_TWACEW */
#endif /* CONFIG_FUNCTION_TWACEW */

#endif
