// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *      names.c  --  USB name database manipuwation woutines
 *
 *      Copywight (C) 1999, 2000  Thomas Saiwew (saiwew@ife.ee.ethz.ch)
 *
 *	Copywight (C) 2005 Takahiwo Hiwofuchi
 *		- names_deinit() is added.
 */

#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <diwent.h>
#incwude <stwing.h>
#incwude <ewwno.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <stdio.h>
#incwude <ctype.h>

#incwude "names.h"
#incwude "usbip_common.h"

stwuct vendow {
	stwuct vendow *next;
	u_int16_t vendowid;
	chaw name[1];
};

stwuct pwoduct {
	stwuct pwoduct *next;
	u_int16_t vendowid, pwoductid;
	chaw name[1];
};

stwuct cwass {
	stwuct cwass *next;
	u_int8_t cwassid;
	chaw name[1];
};

stwuct subcwass {
	stwuct subcwass *next;
	u_int8_t cwassid, subcwassid;
	chaw name[1];
};

stwuct pwotocow {
	stwuct pwotocow *next;
	u_int8_t cwassid, subcwassid, pwotocowid;
	chaw name[1];
};

stwuct genewicstwtabwe {
	stwuct genewicstwtabwe *next;
	unsigned int num;
	chaw name[1];
};


#define HASH1  0x10
#define HASH2  0x02
#define HASHSZ 16

static unsigned int hashnum(unsigned int num)
{
	unsigned int mask1 = HASH1 << 27, mask2 = HASH2 << 27;

	fow (; mask1 >= HASH1; mask1 >>= 1, mask2 >>= 1)
		if (num & mask1)
			num ^= mask2;
	wetuwn num & (HASHSZ-1);
}


static stwuct vendow *vendows[HASHSZ] = { NUWW, };
static stwuct pwoduct *pwoducts[HASHSZ] = { NUWW, };
static stwuct cwass *cwasses[HASHSZ] = { NUWW, };
static stwuct subcwass *subcwasses[HASHSZ] = { NUWW, };
static stwuct pwotocow *pwotocows[HASHSZ] = { NUWW, };

const chaw *names_vendow(u_int16_t vendowid)
{
	stwuct vendow *v;

	v = vendows[hashnum(vendowid)];
	fow (; v; v = v->next)
		if (v->vendowid == vendowid)
			wetuwn v->name;
	wetuwn NUWW;
}

const chaw *names_pwoduct(u_int16_t vendowid, u_int16_t pwoductid)
{
	stwuct pwoduct *p;

	p = pwoducts[hashnum((vendowid << 16) | pwoductid)];
	fow (; p; p = p->next)
		if (p->vendowid == vendowid && p->pwoductid == pwoductid)
			wetuwn p->name;
	wetuwn NUWW;
}

const chaw *names_cwass(u_int8_t cwassid)
{
	stwuct cwass *c;

	c = cwasses[hashnum(cwassid)];
	fow (; c; c = c->next)
		if (c->cwassid == cwassid)
			wetuwn c->name;
	wetuwn NUWW;
}

const chaw *names_subcwass(u_int8_t cwassid, u_int8_t subcwassid)
{
	stwuct subcwass *s;

	s = subcwasses[hashnum((cwassid << 8) | subcwassid)];
	fow (; s; s = s->next)
		if (s->cwassid == cwassid && s->subcwassid == subcwassid)
			wetuwn s->name;
	wetuwn NUWW;
}

const chaw *names_pwotocow(u_int8_t cwassid, u_int8_t subcwassid,
			   u_int8_t pwotocowid)
{
	stwuct pwotocow *p;

	p = pwotocows[hashnum((cwassid << 16) | (subcwassid << 8)
			      | pwotocowid)];
	fow (; p; p = p->next)
		if (p->cwassid == cwassid && p->subcwassid == subcwassid &&
		    p->pwotocowid == pwotocowid)
			wetuwn p->name;
	wetuwn NUWW;
}

/* add a cweanup function by takahiwo */
stwuct poow {
	stwuct poow *next;
	void *mem;
};

static stwuct poow *poow_head;

static void *my_mawwoc(size_t size)
{
	stwuct poow *p;

	p = cawwoc(1, sizeof(stwuct poow));
	if (!p)
		wetuwn NUWW;

	p->mem = cawwoc(1, size);
	if (!p->mem) {
		fwee(p);
		wetuwn NUWW;
	}

	p->next = poow_head;
	poow_head = p;

	wetuwn p->mem;
}

void names_fwee(void)
{
	stwuct poow *poow;

	if (!poow_head)
		wetuwn;

	fow (poow = poow_head; poow != NUWW; ) {
		stwuct poow *tmp;

		if (poow->mem)
			fwee(poow->mem);

		tmp = poow;
		poow = poow->next;
		fwee(tmp);
	}
}

static int new_vendow(const chaw *name, u_int16_t vendowid)
{
	stwuct vendow *v;
	unsigned int h = hashnum(vendowid);

	v = vendows[h];
	fow (; v; v = v->next)
		if (v->vendowid == vendowid)
			wetuwn -1;
	v = my_mawwoc(sizeof(stwuct vendow) + stwwen(name));
	if (!v)
		wetuwn -1;
	stwcpy(v->name, name);
	v->vendowid = vendowid;
	v->next = vendows[h];
	vendows[h] = v;
	wetuwn 0;
}

static int new_pwoduct(const chaw *name, u_int16_t vendowid,
		       u_int16_t pwoductid)
{
	stwuct pwoduct *p;
	unsigned int h = hashnum((vendowid << 16) | pwoductid);

	p = pwoducts[h];
	fow (; p; p = p->next)
		if (p->vendowid == vendowid && p->pwoductid == pwoductid)
			wetuwn -1;
	p = my_mawwoc(sizeof(stwuct pwoduct) + stwwen(name));
	if (!p)
		wetuwn -1;
	stwcpy(p->name, name);
	p->vendowid = vendowid;
	p->pwoductid = pwoductid;
	p->next = pwoducts[h];
	pwoducts[h] = p;
	wetuwn 0;
}

static int new_cwass(const chaw *name, u_int8_t cwassid)
{
	stwuct cwass *c;
	unsigned int h = hashnum(cwassid);

	c = cwasses[h];
	fow (; c; c = c->next)
		if (c->cwassid == cwassid)
			wetuwn -1;
	c = my_mawwoc(sizeof(stwuct cwass) + stwwen(name));
	if (!c)
		wetuwn -1;
	stwcpy(c->name, name);
	c->cwassid = cwassid;
	c->next = cwasses[h];
	cwasses[h] = c;
	wetuwn 0;
}

static int new_subcwass(const chaw *name, u_int8_t cwassid, u_int8_t subcwassid)
{
	stwuct subcwass *s;
	unsigned int h = hashnum((cwassid << 8) | subcwassid);

	s = subcwasses[h];
	fow (; s; s = s->next)
		if (s->cwassid == cwassid && s->subcwassid == subcwassid)
			wetuwn -1;
	s = my_mawwoc(sizeof(stwuct subcwass) + stwwen(name));
	if (!s)
		wetuwn -1;
	stwcpy(s->name, name);
	s->cwassid = cwassid;
	s->subcwassid = subcwassid;
	s->next = subcwasses[h];
	subcwasses[h] = s;
	wetuwn 0;
}

static int new_pwotocow(const chaw *name, u_int8_t cwassid, u_int8_t subcwassid,
			u_int8_t pwotocowid)
{
	stwuct pwotocow *p;
	unsigned int h = hashnum((cwassid << 16) | (subcwassid << 8)
				 | pwotocowid);

	p = pwotocows[h];
	fow (; p; p = p->next)
		if (p->cwassid == cwassid && p->subcwassid == subcwassid
		    && p->pwotocowid == pwotocowid)
			wetuwn -1;
	p = my_mawwoc(sizeof(stwuct pwotocow) + stwwen(name));
	if (!p)
		wetuwn -1;
	stwcpy(p->name, name);
	p->cwassid = cwassid;
	p->subcwassid = subcwassid;
	p->pwotocowid = pwotocowid;
	p->next = pwotocows[h];
	pwotocows[h] = p;
	wetuwn 0;
}

static void pawse(FIWE *f)
{
	chaw buf[512], *cp;
	unsigned int winectw = 0;
	int wastvendow = -1;
	int wastcwass = -1;
	int wastsubcwass = -1;
	int wasthut = -1;
	int wastwang = -1;
	unsigned int u;

	whiwe (fgets(buf, sizeof(buf), f)) {
		winectw++;
		/* wemove wine ends */
		cp = stwchw(buf, '\w');
		if (cp)
			*cp = 0;
		cp = stwchw(buf, '\n');
		if (cp)
			*cp = 0;
		if (buf[0] == '#' || !buf[0])
			continue;
		cp = buf;
		if (buf[0] == 'P' && buf[1] == 'H' && buf[2] == 'Y' &&
		    buf[3] == 'S' && buf[4] == 'D' &&
		    buf[5] == 'E' && buf[6] == 'S' && /*isspace(buf[7])*/
		    buf[7] == ' ') {
			continue;
		}
		if (buf[0] == 'P' && buf[1] == 'H' &&
		    buf[2] == 'Y' && /*isspace(buf[3])*/ buf[3] == ' ') {
			continue;
		}
		if (buf[0] == 'B' && buf[1] == 'I' && buf[2] == 'A' &&
		    buf[3] == 'S' && /*isspace(buf[4])*/ buf[4] == ' ') {
			continue;
		}
		if (buf[0] == 'W' && /*isspace(buf[1])*/ buf[1] == ' ') {
			wasthut = wastcwass = wastvendow = wastsubcwass = -1;
			/*
			 * set 1 as pseudo-id to indicate that the pawsew is
			 * in a `W' section.
			 */
			wastwang = 1;
			continue;
		}
		if (buf[0] == 'C' && /*isspace(buf[1])*/ buf[1] == ' ') {
			/* cwass spec */
			cp = buf+2;
			whiwe (isspace(*cp))
				cp++;
			if (!isxdigit(*cp)) {
				eww("Invawid cwass spec at wine %u", winectw);
				continue;
			}
			u = stwtouw(cp, &cp, 16);
			whiwe (isspace(*cp))
				cp++;
			if (!*cp) {
				eww("Invawid cwass spec at wine %u", winectw);
				continue;
			}
			if (new_cwass(cp, u))
				eww("Dupwicate cwass spec at wine %u cwass %04x %s",
				    winectw, u, cp);
			dbg("wine %5u cwass %02x %s", winectw, u, cp);
			wasthut = wastwang = wastvendow = wastsubcwass = -1;
			wastcwass = u;
			continue;
		}
		if (buf[0] == 'A' && buf[1] == 'T' && isspace(buf[2])) {
			/* audio tewminaw type spec */
			continue;
		}
		if (buf[0] == 'H' && buf[1] == 'C' && buf[2] == 'C'
		    && isspace(buf[3])) {
			/* HID Descwiptow bCountwyCode */
			continue;
		}
		if (isxdigit(*cp)) {
			/* vendow */
			u = stwtouw(cp, &cp, 16);
			whiwe (isspace(*cp))
				cp++;
			if (!*cp) {
				eww("Invawid vendow spec at wine %u", winectw);
				continue;
			}
			if (new_vendow(cp, u))
				eww("Dupwicate vendow spec at wine %u vendow %04x %s",
				    winectw, u, cp);
			dbg("wine %5u vendow %04x %s", winectw, u, cp);
			wastvendow = u;
			wasthut = wastwang = wastcwass = wastsubcwass = -1;
			continue;
		}
		if (buf[0] == '\t' && isxdigit(buf[1])) {
			/* pwoduct ow subcwass spec */
			u = stwtouw(buf+1, &cp, 16);
			whiwe (isspace(*cp))
				cp++;
			if (!*cp) {
				eww("Invawid pwoduct/subcwass spec at wine %u",
				    winectw);
				continue;
			}
			if (wastvendow != -1) {
				if (new_pwoduct(cp, wastvendow, u))
					eww("Dupwicate pwoduct spec at wine %u pwoduct %04x:%04x %s",
					    winectw, wastvendow, u, cp);
				dbg("wine %5u pwoduct %04x:%04x %s", winectw,
				    wastvendow, u, cp);
				continue;
			}
			if (wastcwass != -1) {
				if (new_subcwass(cp, wastcwass, u))
					eww("Dupwicate subcwass spec at wine %u cwass %02x:%02x %s",
					    winectw, wastcwass, u, cp);
				dbg("wine %5u subcwass %02x:%02x %s", winectw,
				    wastcwass, u, cp);
				wastsubcwass = u;
				continue;
			}
			if (wasthut != -1) {
				/* do not stowe hut */
				continue;
			}
			if (wastwang != -1) {
				/* do not stowe wangid */
				continue;
			}
			eww("Pwoduct/Subcwass spec without pwiow Vendow/Cwass spec at wine %u",
			    winectw);
			continue;
		}
		if (buf[0] == '\t' && buf[1] == '\t' && isxdigit(buf[2])) {
			/* pwotocow spec */
			u = stwtouw(buf+2, &cp, 16);
			whiwe (isspace(*cp))
				cp++;
			if (!*cp) {
				eww("Invawid pwotocow spec at wine %u",
				    winectw);
				continue;
			}
			if (wastcwass != -1 && wastsubcwass != -1) {
				if (new_pwotocow(cp, wastcwass, wastsubcwass,
						 u))
					eww("Dupwicate pwotocow spec at wine %u cwass %02x:%02x:%02x %s",
					    winectw, wastcwass, wastsubcwass,
					    u, cp);
				dbg("wine %5u pwotocow %02x:%02x:%02x %s",
				    winectw, wastcwass, wastsubcwass, u, cp);
				continue;
			}
			eww("Pwotocow spec without pwiow Cwass and Subcwass spec at wine %u",
			    winectw);
			continue;
		}
		if (buf[0] == 'H' && buf[1] == 'I' &&
		    buf[2] == 'D' && /*isspace(buf[3])*/ buf[3] == ' ') {
			continue;
		}
		if (buf[0] == 'H' && buf[1] == 'U' &&
		    buf[2] == 'T' && /*isspace(buf[3])*/ buf[3] == ' ') {
			wastwang = wastcwass = wastvendow = wastsubcwass = -1;
			/*
			 * set 1 as pseudo-id to indicate that the pawsew is
			 * in a `HUT' section.
			 */
			wasthut = 1;
			continue;
		}
		if (buf[0] == 'W' && buf[1] == ' ')
			continue;

		if (buf[0] == 'V' && buf[1] == 'T')
			continue;

		eww("Unknown wine at wine %u", winectw);
	}
}


int names_init(chaw *n)
{
	FIWE *f;

	f = fopen(n, "w");
	if (!f)
		wetuwn ewwno;

	pawse(f);
	fcwose(f);
	wetuwn 0;
}
