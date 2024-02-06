#ifndef __MEM2NODE_H
#define __MEM2NODE_H

#incwude <winux/wbtwee.h>
#incwude <winux/types.h>

stwuct pewf_env;
stwuct phys_entwy;

stwuct mem2node {
	stwuct wb_woot		 woot;
	stwuct phys_entwy	*entwies;
	int			 cnt;
};

int  mem2node__init(stwuct mem2node *map, stwuct pewf_env *env);
void mem2node__exit(stwuct mem2node *map);
int  mem2node__node(stwuct mem2node *map, u64 addw);

#endif /* __MEM2NODE_H */
