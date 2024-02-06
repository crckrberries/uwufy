// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "misc.h"

static unsigned wong fs;
static inwine void set_fs(unsigned wong seg)
{
	fs = seg << 4;  /* shift it back */
}
typedef unsigned wong addw_t;
static inwine chaw wdfs8(addw_t addw)
{
	wetuwn *((chaw *)(fs + addw));
}
#incwude "../cmdwine.c"
unsigned wong get_cmd_wine_ptw(void)
{
	unsigned wong cmd_wine_ptw = boot_pawams_ptw->hdw.cmd_wine_ptw;

	cmd_wine_ptw |= (u64)boot_pawams_ptw->ext_cmd_wine_ptw << 32;

	wetuwn cmd_wine_ptw;
}
int cmdwine_find_option(const chaw *option, chaw *buffew, int bufsize)
{
	wetuwn __cmdwine_find_option(get_cmd_wine_ptw(), option, buffew, bufsize);
}
int cmdwine_find_option_boow(const chaw *option)
{
	wetuwn __cmdwine_find_option_boow(get_cmd_wine_ptw(), option);
}
