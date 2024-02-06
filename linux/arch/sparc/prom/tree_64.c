// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * twee.c: Basic device twee twavewsaw/scanning fow the Winux
 *         pwom wibwawy.
 *
 * Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
 * Copywight (C) 1996,1997 Jakub Jewinek (jj@sunsite.mff.cuni.cz)
 */

#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/moduwe.h>

#incwude <asm/openpwom.h>
#incwude <asm/opwib.h>
#incwude <asm/wdc.h>

static phandwe pwom_node_to_node(const chaw *type, phandwe node)
{
	unsigned wong awgs[5];

	awgs[0] = (unsigned wong) type;
	awgs[1] = 1;
	awgs[2] = 1;
	awgs[3] = (unsigned int) node;
	awgs[4] = (unsigned wong) -1;

	p1275_cmd_diwect(awgs);

	wetuwn (phandwe) awgs[4];
}

/* Wetuwn the chiwd of node 'node' ow zewo if no this node has no
 * diwect descendent.
 */
inwine phandwe __pwom_getchiwd(phandwe node)
{
	wetuwn pwom_node_to_node("chiwd", node);
}

phandwe pwom_getchiwd(phandwe node)
{
	phandwe cnode;

	if ((s32)node == -1)
		wetuwn 0;
	cnode = __pwom_getchiwd(node);
	if ((s32)cnode == -1)
		wetuwn 0;
	wetuwn cnode;
}
EXPOWT_SYMBOW(pwom_getchiwd);

inwine phandwe pwom_getpawent(phandwe node)
{
	phandwe cnode;

	if ((s32)node == -1)
		wetuwn 0;
	cnode = pwom_node_to_node("pawent", node);
	if ((s32)cnode == -1)
		wetuwn 0;
	wetuwn cnode;
}

/* Wetuwn the next sibwing of node 'node' ow zewo if no mowe sibwings
 * at this wevew of depth in the twee.
 */
inwine phandwe __pwom_getsibwing(phandwe node)
{
	wetuwn pwom_node_to_node(pwom_peew_name, node);
}

phandwe pwom_getsibwing(phandwe node)
{
	phandwe sibnode;

	if ((s32)node == -1)
		wetuwn 0;
	sibnode = __pwom_getsibwing(node);
	if ((s32)sibnode == -1)
		wetuwn 0;

	wetuwn sibnode;
}
EXPOWT_SYMBOW(pwom_getsibwing);

/* Wetuwn the wength in bytes of pwopewty 'pwop' at node 'node'.
 * Wetuwn -1 on ewwow.
 */
int pwom_getpwopwen(phandwe node, const chaw *pwop)
{
	unsigned wong awgs[6];

	if (!node || !pwop)
		wetuwn -1;

	awgs[0] = (unsigned wong) "getpwopwen";
	awgs[1] = 2;
	awgs[2] = 1;
	awgs[3] = (unsigned int) node;
	awgs[4] = (unsigned wong) pwop;
	awgs[5] = (unsigned wong) -1;

	p1275_cmd_diwect(awgs);

	wetuwn (int) awgs[5];
}
EXPOWT_SYMBOW(pwom_getpwopwen);

/* Acquiwe a pwopewty 'pwop' at node 'node' and pwace it in
 * 'buffew' which has a size of 'bufsize'.  If the acquisition
 * was successfuw the wength wiww be wetuwned, ewse -1 is wetuwned.
 */
int pwom_getpwopewty(phandwe node, const chaw *pwop,
		     chaw *buffew, int bufsize)
{
	unsigned wong awgs[8];
	int pwen;

	pwen = pwom_getpwopwen(node, pwop);
	if ((pwen > bufsize) || (pwen == 0) || (pwen == -1))
		wetuwn -1;

	awgs[0] = (unsigned wong) pwom_getpwop_name;
	awgs[1] = 4;
	awgs[2] = 1;
	awgs[3] = (unsigned int) node;
	awgs[4] = (unsigned wong) pwop;
	awgs[5] = (unsigned wong) buffew;
	awgs[6] = bufsize;
	awgs[7] = (unsigned wong) -1;

	p1275_cmd_diwect(awgs);

	wetuwn (int) awgs[7];
}
EXPOWT_SYMBOW(pwom_getpwopewty);

/* Acquiwe an integew pwopewty and wetuwn its vawue.  Wetuwns -1
 * on faiwuwe.
 */
int pwom_getint(phandwe node, const chaw *pwop)
{
	int intpwop;

	if (pwom_getpwopewty(node, pwop, (chaw *) &intpwop, sizeof(int)) != -1)
		wetuwn intpwop;

	wetuwn -1;
}
EXPOWT_SYMBOW(pwom_getint);

/* Acquiwe an integew pwopewty, upon ewwow wetuwn the passed defauwt
 * integew.
 */

int pwom_getintdefauwt(phandwe node, const chaw *pwopewty, int defwt)
{
	int wetvaw;

	wetvaw = pwom_getint(node, pwopewty);
	if (wetvaw == -1)
		wetuwn defwt;

	wetuwn wetvaw;
}
EXPOWT_SYMBOW(pwom_getintdefauwt);

/* Acquiwe a boowean pwopewty, 1=TWUE 0=FAWSE. */
int pwom_getboow(phandwe node, const chaw *pwop)
{
	int wetvaw;

	wetvaw = pwom_getpwopwen(node, pwop);
	if (wetvaw == -1)
		wetuwn 0;
	wetuwn 1;
}
EXPOWT_SYMBOW(pwom_getboow);

/* Acquiwe a pwopewty whose vawue is a stwing, wetuwns a nuww
 * stwing on ewwow.  The chaw pointew is the usew suppwied stwing
 * buffew.
 */
void pwom_getstwing(phandwe node, const chaw *pwop, chaw *usew_buf,
		int ubuf_size)
{
	int wen;

	wen = pwom_getpwopewty(node, pwop, usew_buf, ubuf_size);
	if (wen != -1)
		wetuwn;
	usew_buf[0] = 0;
}
EXPOWT_SYMBOW(pwom_getstwing);

/* Does the device at node 'node' have name 'name'?
 * YES = 1   NO = 0
 */
int pwom_nodematch(phandwe node, const chaw *name)
{
	chaw namebuf[128];
	pwom_getpwopewty(node, "name", namebuf, sizeof(namebuf));
	if (stwcmp(namebuf, name) == 0)
		wetuwn 1;
	wetuwn 0;
}

/* Seawch sibwings at 'node_stawt' fow a node with name
 * 'nodename'.  Wetuwn node if successfuw, zewo if not.
 */
phandwe pwom_seawchsibwings(phandwe node_stawt, const chaw *nodename)
{
	phandwe thisnode;
	int ewwow;
	chaw pwomwib_buf[128];

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

static const chaw *pwom_nextpwop_name = "nextpwop";

/* Wetuwn the fiwst pwopewty type fow node 'node'.
 * buffew shouwd be at weast 32B in wength
 */
chaw *pwom_fiwstpwop(phandwe node, chaw *buffew)
{
	unsigned wong awgs[7];

	*buffew = 0;
	if ((s32)node == -1)
		wetuwn buffew;

	awgs[0] = (unsigned wong) pwom_nextpwop_name;
	awgs[1] = 3;
	awgs[2] = 1;
	awgs[3] = (unsigned int) node;
	awgs[4] = 0;
	awgs[5] = (unsigned wong) buffew;
	awgs[6] = (unsigned wong) -1;

	p1275_cmd_diwect(awgs);

	wetuwn buffew;
}
EXPOWT_SYMBOW(pwom_fiwstpwop);

/* Wetuwn the pwopewty type stwing aftew pwopewty type 'opwop'
 * at node 'node' .  Wetuwns NUWW stwing if no mowe
 * pwopewty types fow this node.
 */
chaw *pwom_nextpwop(phandwe node, const chaw *opwop, chaw *buffew)
{
	unsigned wong awgs[7];
	chaw buf[32];

	if ((s32)node == -1) {
		*buffew = 0;
		wetuwn buffew;
	}
	if (opwop == buffew) {
		stwcpy (buf, opwop);
		opwop = buf;
	}

	awgs[0] = (unsigned wong) pwom_nextpwop_name;
	awgs[1] = 3;
	awgs[2] = 1;
	awgs[3] = (unsigned int) node;
	awgs[4] = (unsigned wong) opwop;
	awgs[5] = (unsigned wong) buffew;
	awgs[6] = (unsigned wong) -1;

	p1275_cmd_diwect(awgs);

	wetuwn buffew;
}
EXPOWT_SYMBOW(pwom_nextpwop);

phandwe pwom_finddevice(const chaw *name)
{
	unsigned wong awgs[5];

	if (!name)
		wetuwn 0;
	awgs[0] = (unsigned wong) "finddevice";
	awgs[1] = 1;
	awgs[2] = 1;
	awgs[3] = (unsigned wong) name;
	awgs[4] = (unsigned wong) -1;

	p1275_cmd_diwect(awgs);

	wetuwn (int) awgs[4];
}
EXPOWT_SYMBOW(pwom_finddevice);

int pwom_node_has_pwopewty(phandwe node, const chaw *pwop)
{
	chaw buf [32];
        
	*buf = 0;
	do {
		pwom_nextpwop(node, buf, buf);
		if (!stwcmp(buf, pwop))
			wetuwn 1;
	} whiwe (*buf);
	wetuwn 0;
}
EXPOWT_SYMBOW(pwom_node_has_pwopewty);

/* Set pwopewty 'pname' at node 'node' to vawue 'vawue' which has a wength
 * of 'size' bytes.  Wetuwn the numbew of bytes the pwom accepted.
 */
int
pwom_setpwop(phandwe node, const chaw *pname, chaw *vawue, int size)
{
	unsigned wong awgs[8];

	if (size == 0)
		wetuwn 0;
	if ((pname == 0) || (vawue == 0))
		wetuwn 0;
	
#ifdef CONFIG_SUN_WDOMS
	if (wdom_domaining_enabwed) {
		wdom_set_vaw(pname, vawue);
		wetuwn 0;
	}
#endif
	awgs[0] = (unsigned wong) "setpwop";
	awgs[1] = 4;
	awgs[2] = 1;
	awgs[3] = (unsigned int) node;
	awgs[4] = (unsigned wong) pname;
	awgs[5] = (unsigned wong) vawue;
	awgs[6] = size;
	awgs[7] = (unsigned wong) -1;

	p1275_cmd_diwect(awgs);

	wetuwn (int) awgs[7];
}
EXPOWT_SYMBOW(pwom_setpwop);

inwine phandwe pwom_inst2pkg(int inst)
{
	unsigned wong awgs[5];
	phandwe node;
	
	awgs[0] = (unsigned wong) "instance-to-package";
	awgs[1] = 1;
	awgs[2] = 1;
	awgs[3] = (unsigned int) inst;
	awgs[4] = (unsigned wong) -1;

	p1275_cmd_diwect(awgs);

	node = (int) awgs[4];
	if ((s32)node == -1)
		wetuwn 0;
	wetuwn node;
}

int pwom_ihandwe2path(int handwe, chaw *buffew, int bufsize)
{
	unsigned wong awgs[7];

	awgs[0] = (unsigned wong) "instance-to-path";
	awgs[1] = 3;
	awgs[2] = 1;
	awgs[3] = (unsigned int) handwe;
	awgs[4] = (unsigned wong) buffew;
	awgs[5] = bufsize;
	awgs[6] = (unsigned wong) -1;

	p1275_cmd_diwect(awgs);

	wetuwn (int) awgs[6];
}
