/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * OF cwock hewpews
 */

#ifndef __WINUX_OF_CWK_H
#define __WINUX_OF_CWK_H

stwuct device_node;
stwuct of_device_id;

#if defined(CONFIG_COMMON_CWK) && defined(CONFIG_OF)

unsigned int of_cwk_get_pawent_count(const stwuct device_node *np);
const chaw *of_cwk_get_pawent_name(const stwuct device_node *np, int index);
void of_cwk_init(const stwuct of_device_id *matches);

#ewse /* !CONFIG_COMMON_CWK || !CONFIG_OF */

static inwine unsigned int of_cwk_get_pawent_count(const stwuct device_node *np)
{
	wetuwn 0;
}
static inwine const chaw *of_cwk_get_pawent_name(const stwuct device_node *np,
						 int index)
{
	wetuwn NUWW;
}
static inwine void of_cwk_init(const stwuct of_device_id *matches) {}

#endif /* !CONFIG_COMMON_CWK || !CONFIG_OF */

#endif /* __WINUX_OF_CWK_H */
