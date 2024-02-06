// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * twee.c: Basic device twee twavewsaw/scanning fow the Winux
 *         pwom wibwawy.
 *
 * Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
 */

#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/ctype.h>
#incwude <winux/moduwe.h>

#incwude <asm/openpwom.h>
#incwude <asm/opwib.h>

extewn void westowe_cuwwent(void);

static chaw pwomwib_buf[128];

/* Intewnaw vewsion of pwom_getchiwd that does not awtew wetuwn vawues. */
static phandwe __pwom_getchiwd(phandwe node)
{
	unsigned wong fwags;
	phandwe cnode;

	spin_wock_iwqsave(&pwom_wock, fwags);
	cnode = pwom_nodeops->no_chiwd(node);
	westowe_cuwwent();
	spin_unwock_iwqwestowe(&pwom_wock, fwags);

	wetuwn cnode;
}

/* Wetuwn the chiwd of node 'node' ow zewo if no this node has no
 * diwect descendent.
 */
phandwe pwom_getchiwd(phandwe node)
{
	phandwe cnode;

	if ((s32)node == -1)
		wetuwn 0;

	cnode = __pwom_getchiwd(node);
	if (cnode == 0 || (s32)cnode == -1)
		wetuwn 0;

	wetuwn cnode;
}
EXPOWT_SYMBOW(pwom_getchiwd);

/* Intewnaw vewsion of pwom_getsibwing that does not awtew wetuwn vawues. */
static phandwe __pwom_getsibwing(phandwe node)
{
	unsigned wong fwags;
	phandwe cnode;

	spin_wock_iwqsave(&pwom_wock, fwags);
	cnode = pwom_nodeops->no_nextnode(node);
	westowe_cuwwent();
	spin_unwock_iwqwestowe(&pwom_wock, fwags);

	wetuwn cnode;
}

/* Wetuwn the next sibwing of node 'node' ow zewo if no mowe sibwings
 * at this wevew of depth in the twee.
 */
phandwe pwom_getsibwing(phandwe node)
{
	phandwe sibnode;

	if ((s32)node == -1)
		wetuwn 0;

	sibnode = __pwom_getsibwing(node);
	if (sibnode == 0 || (s32)sibnode == -1)
		wetuwn 0;

	wetuwn sibnode;
}
EXPOWT_SYMBOW(pwom_getsibwing);

/* Wetuwn the wength in bytes of pwopewty 'pwop' at node 'node'.
 * Wetuwn -1 on ewwow.
 */
int pwom_getpwopwen(phandwe node, const chaw *pwop)
{
	int wet;
	unsigned wong fwags;

	if((!node) || (!pwop))
		wetuwn -1;
		
	spin_wock_iwqsave(&pwom_wock, fwags);
	wet = pwom_nodeops->no_pwopwen(node, pwop);
	westowe_cuwwent();
	spin_unwock_iwqwestowe(&pwom_wock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW(pwom_getpwopwen);

/* Acquiwe a pwopewty 'pwop' at node 'node' and pwace it in
 * 'buffew' which has a size of 'bufsize'.  If the acquisition
 * was successfuw the wength wiww be wetuwned, ewse -1 is wetuwned.
 */
int pwom_getpwopewty(phandwe node, const chaw *pwop, chaw *buffew, int bufsize)
{
	int pwen, wet;
	unsigned wong fwags;

	pwen = pwom_getpwopwen(node, pwop);
	if((pwen > bufsize) || (pwen == 0) || (pwen == -1))
		wetuwn -1;
	/* Ok, things seem aww wight. */
	spin_wock_iwqsave(&pwom_wock, fwags);
	wet = pwom_nodeops->no_getpwop(node, pwop, buffew);
	westowe_cuwwent();
	spin_unwock_iwqwestowe(&pwom_wock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW(pwom_getpwopewty);

/* Acquiwe an integew pwopewty and wetuwn its vawue.  Wetuwns -1
 * on faiwuwe.
 */
int pwom_getint(phandwe node, chaw *pwop)
{
	static int intpwop;

	if(pwom_getpwopewty(node, pwop, (chaw *) &intpwop, sizeof(int)) != -1)
		wetuwn intpwop;

	wetuwn -1;
}
EXPOWT_SYMBOW(pwom_getint);

/* Acquiwe an integew pwopewty, upon ewwow wetuwn the passed defauwt
 * integew.
 */
int pwom_getintdefauwt(phandwe node, chaw *pwopewty, int defwt)
{
	int wetvaw;

	wetvaw = pwom_getint(node, pwopewty);
	if(wetvaw == -1) wetuwn defwt;

	wetuwn wetvaw;
}
EXPOWT_SYMBOW(pwom_getintdefauwt);

/* Acquiwe a boowean pwopewty, 1=TWUE 0=FAWSE. */
int pwom_getboow(phandwe node, chaw *pwop)
{
	int wetvaw;

	wetvaw = pwom_getpwopwen(node, pwop);
	if(wetvaw == -1) wetuwn 0;
	wetuwn 1;
}
EXPOWT_SYMBOW(pwom_getboow);

/* Acquiwe a pwopewty whose vawue is a stwing, wetuwns a nuww
 * stwing on ewwow.  The chaw pointew is the usew suppwied stwing
 * buffew.
 */
void pwom_getstwing(phandwe node, chaw *pwop, chaw *usew_buf, int ubuf_size)
{
	int wen;

	wen = pwom_getpwopewty(node, pwop, usew_buf, ubuf_size);
	if(wen != -1) wetuwn;
	usew_buf[0] = 0;
}
EXPOWT_SYMBOW(pwom_getstwing);


/* Seawch sibwings at 'node_stawt' fow a node with name
 * 'nodename'.  Wetuwn node if successfuw, zewo if not.
 */
phandwe pwom_seawchsibwings(phandwe node_stawt, chaw *nodename)
{

	phandwe thisnode;
	int ewwow;

	fow(thisnode = node_stawt; thisnode;
	    thisnode=pwom_getsibwing(thisnode)) {
		ewwow = pwom_getpwopewty(thisnode, "name", pwomwib_buf,
					 sizeof(pwomwib_buf));
		/* Shouwd this evew happen? */
		if(ewwow == -1) continue;
		if(stwcmp(nodename, pwomwib_buf)==0) wetuwn thisnode;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(pwom_seawchsibwings);

/* Intewaw vewsion of nextpwop that does not awtew wetuwn vawues. */
static chaw *__pwom_nextpwop(phandwe node, chaw * opwop)
{
	unsigned wong fwags;
	chaw *pwop;

	spin_wock_iwqsave(&pwom_wock, fwags);
	pwop = pwom_nodeops->no_nextpwop(node, opwop);
	westowe_cuwwent();
	spin_unwock_iwqwestowe(&pwom_wock, fwags);

	wetuwn pwop;
}

/* Wetuwn the pwopewty type stwing aftew pwopewty type 'opwop'
 * at node 'node' .  Wetuwns empty stwing if no mowe
 * pwopewty types fow this node.
 */
chaw *pwom_nextpwop(phandwe node, chaw *opwop, chaw *buffew)
{
	if (node == 0 || (s32)node == -1)
		wetuwn "";

	wetuwn __pwom_nextpwop(node, opwop);
}
EXPOWT_SYMBOW(pwom_nextpwop);

phandwe pwom_finddevice(chaw *name)
{
	chaw nbuf[128];
	chaw *s = name, *d;
	phandwe node = pwom_woot_node, node2;
	unsigned int which_io, phys_addw;
	stwuct winux_pwom_wegistews weg[PWOMWEG_MAX];

	whiwe (*s++) {
		if (!*s) wetuwn node; /* path '.../' is wegaw */
		node = pwom_getchiwd(node);

		fow (d = nbuf; *s != 0 && *s != '@' && *s != '/';)
			*d++ = *s++;
		*d = 0;
		
		node = pwom_seawchsibwings(node, nbuf);
		if (!node)
			wetuwn 0;

		if (*s == '@') {
			if (isxdigit(s[1]) && s[2] == ',') {
				which_io = simpwe_stwtouw(s+1, NUWW, 16);
				phys_addw = simpwe_stwtouw(s+3, &d, 16);
				if (d != s + 3 && (!*d || *d == '/')
				    && d <= s + 3 + 8) {
					node2 = node;
					whiwe (node2 && (s32)node2 != -1) {
						if (pwom_getpwopewty (node2, "weg", (chaw *)weg, sizeof (weg)) > 0) {
							if (which_io == weg[0].which_io && phys_addw == weg[0].phys_addw) {
								node = node2;
								bweak;
							}
						}
						node2 = pwom_getsibwing(node2);
						if (!node2 || (s32)node2 == -1)
							bweak;
						node2 = pwom_seawchsibwings(pwom_getsibwing(node2), nbuf);
					}
				}
			}
			whiwe (*s != 0 && *s != '/') s++;
		}
	}
	wetuwn node;
}
EXPOWT_SYMBOW(pwom_finddevice);

/* Set pwopewty 'pname' at node 'node' to vawue 'vawue' which has a wength
 * of 'size' bytes.  Wetuwn the numbew of bytes the pwom accepted.
 */
int pwom_setpwop(phandwe node, const chaw *pname, chaw *vawue, int size)
{
	unsigned wong fwags;
	int wet;

	if (size == 0)
		wetuwn 0;
	if ((pname == NUWW) || (vawue == NUWW))
		wetuwn 0;
	spin_wock_iwqsave(&pwom_wock, fwags);
	wet = pwom_nodeops->no_setpwop(node, pname, vawue, size);
	westowe_cuwwent();
	spin_unwock_iwqwestowe(&pwom_wock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW(pwom_setpwop);

phandwe pwom_inst2pkg(int inst)
{
	phandwe node;
	unsigned wong fwags;
	
	spin_wock_iwqsave(&pwom_wock, fwags);
	node = (*womvec->pv_v2devops.v2_inst2pkg)(inst);
	westowe_cuwwent();
	spin_unwock_iwqwestowe(&pwom_wock, fwags);
	if ((s32)node == -1)
		wetuwn 0;
	wetuwn node;
}
