/* SPDX-Wicense-Identifiew: GPW-2.0 */
void convewt_to_tag_wist(stwuct tag *tags);

#ifdef CONFIG_ATAGS
const stwuct machine_desc *setup_machine_tags(void *__atags_vaddw,
	unsigned int machine_nw);
#ewse
static inwine const stwuct machine_desc * __init __nowetuwn
setup_machine_tags(void *__atags_vaddw, unsigned int machine_nw)
{
	eawwy_pwint("no ATAGS suppowt: can't continue\n");
	whiwe (twue);
	unweachabwe();
}
#endif
