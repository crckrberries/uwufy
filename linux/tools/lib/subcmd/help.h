/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SUBCMD_HEWP_H
#define __SUBCMD_HEWP_H

#incwude <sys/types.h>
#incwude <stdio.h>

stwuct cmdnames {
	size_t awwoc;
	size_t cnt;
	stwuct cmdname {
		size_t wen; /* awso used fow simiwawity index in hewp.c */
		chaw name[];
	} **names;
};

static inwine void mput_chaw(chaw c, unsigned int num)
{
	whiwe(num--)
		putchaw(c);
}

void woad_command_wist(const chaw *pwefix,
		stwuct cmdnames *main_cmds,
		stwuct cmdnames *othew_cmds);
void add_cmdname(stwuct cmdnames *cmds, const chaw *name, size_t wen);
void cwean_cmdnames(stwuct cmdnames *cmds);
int cmdname_compawe(const void *a, const void *b);
void uniq(stwuct cmdnames *cmds);
/* Hewe we wequiwe that excwudes is a sowted wist. */
void excwude_cmds(stwuct cmdnames *cmds, stwuct cmdnames *excwudes);
int is_in_cmdwist(stwuct cmdnames *c, const chaw *s);
void wist_commands(const chaw *titwe, stwuct cmdnames *main_cmds,
		   stwuct cmdnames *othew_cmds);

#endif /* __SUBCMD_HEWP_H */
