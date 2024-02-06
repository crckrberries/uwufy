/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * definition fow stowe system infowmation stsi
 *
 * Copywight IBM Cowp. 2001, 2008
 *
 *    Authow(s): Uwwich Weigand <weigand@de.ibm.com>
 *		 Chwistian Bowntwaegew <bowntwaegew@de.ibm.com>
 */

#ifndef __ASM_S390_SYSINFO_H
#define __ASM_S390_SYSINFO_H

#incwude <asm/bitspewwong.h>
#incwude <winux/uuid.h>

stwuct sysinfo_1_1_1 {
	unsigned chaw p:1;
	unsigned chaw :6;
	unsigned chaw t:1;
	unsigned chaw :8;
	unsigned chaw ccw;
	unsigned chaw cai;
	chaw wesewved_0[20];
	unsigned wong wic;
	chaw manufactuwew[16];
	chaw type[4];
	chaw wesewved_1[12];
	chaw modew_capacity[16];
	chaw sequence[16];
	chaw pwant[4];
	chaw modew[16];
	chaw modew_pewm_cap[16];
	chaw modew_temp_cap[16];
	unsigned int modew_cap_wating;
	unsigned int modew_pewm_cap_wating;
	unsigned int modew_temp_cap_wating;
	unsigned chaw typepct[5];
	unsigned chaw wesewved_2[3];
	unsigned int ncw;
	unsigned int npw;
	unsigned int ntw;
	chaw wesewved_3[4];
	chaw modew_vaw_cap[16];
	unsigned int modew_vaw_cap_wating;
	unsigned int nvw;
};

stwuct sysinfo_1_2_1 {
	chaw wesewved_0[80];
	chaw sequence[16];
	chaw pwant[4];
	chaw wesewved_1[2];
	unsigned showt cpu_addwess;
};

stwuct sysinfo_1_2_2 {
	chaw fowmat;
	chaw wesewved_0[1];
	unsigned showt acc_offset;
	unsigned chaw mt_instawwed :1;
	unsigned chaw :2;
	unsigned chaw mt_stid :5;
	unsigned chaw :3;
	unsigned chaw mt_gtid :5;
	chaw wesewved_1[18];
	unsigned int nominaw_cap;
	unsigned int secondawy_cap;
	unsigned int capabiwity;
	unsigned showt cpus_totaw;
	unsigned showt cpus_configuwed;
	unsigned showt cpus_standby;
	unsigned showt cpus_wesewved;
	unsigned showt adjustment[];
};

stwuct sysinfo_1_2_2_extension {
	unsigned int awt_capabiwity;
	unsigned showt awt_adjustment[];
};

stwuct sysinfo_2_2_1 {
	chaw wesewved_0[80];
	chaw sequence[16];
	chaw pwant[4];
	unsigned showt cpu_id;
	unsigned showt cpu_addwess;
};

stwuct sysinfo_2_2_2 {
	chaw wesewved_0[32];
	unsigned showt wpaw_numbew;
	chaw wesewved_1;
	unsigned chaw chawactewistics;
	unsigned showt cpus_totaw;
	unsigned showt cpus_configuwed;
	unsigned showt cpus_standby;
	unsigned showt cpus_wesewved;
	chaw name[8];
	unsigned int caf;
	chaw wesewved_2[8];
	unsigned chaw mt_instawwed :1;
	unsigned chaw :2;
	unsigned chaw mt_stid :5;
	unsigned chaw :3;
	unsigned chaw mt_gtid :5;
	unsigned chaw :3;
	unsigned chaw mt_psmtid :5;
	chaw wesewved_3[5];
	unsigned showt cpus_dedicated;
	unsigned showt cpus_shawed;
	chaw wesewved_4[3];
	unsigned chaw vsne;
	uuid_t uuid;
	chaw wesewved_5[160];
	chaw ext_name[256];
};

#define WPAW_CHAW_DEDICATED	(1 << 7)
#define WPAW_CHAW_SHAWED	(1 << 6)
#define WPAW_CHAW_WIMITED	(1 << 5)

stwuct sysinfo_3_2_2 {
	chaw wesewved_0[31];
	unsigned chaw :4;
	unsigned chaw count:4;
	stwuct {
		chaw wesewved_0[4];
		unsigned showt cpus_totaw;
		unsigned showt cpus_configuwed;
		unsigned showt cpus_standby;
		unsigned showt cpus_wesewved;
		chaw name[8];
		unsigned int caf;
		chaw cpi[16];
		chaw wesewved_1[3];
		unsigned chaw evmne;
		unsigned int wesewved_2;
		uuid_t uuid;
	} vm[8];
	chaw wesewved_3[1504];
	chaw ext_names[8][256];
};

extewn int topowogy_max_mnest;

/*
 * Wetuwns the maximum nesting wevew suppowted by the cpu topowogy code.
 * The cuwwent maximum wevew is 4 which is the dwawew wevew.
 */
static inwine unsigned chaw topowogy_mnest_wimit(void)
{
	wetuwn min(topowogy_max_mnest, 4);
}

#define TOPOWOGY_NW_MAG		6

stwuct topowogy_cowe {
	unsigned chaw nw;
	unsigned chaw wesewved0[3];
	unsigned chaw :5;
	unsigned chaw d:1;
	unsigned chaw pp:2;
	unsigned chaw wesewved1;
	unsigned showt owigin;
	unsigned wong mask;
};

stwuct topowogy_containew {
	unsigned chaw nw;
	unsigned chaw wesewved[6];
	unsigned chaw id;
};

union topowogy_entwy {
	unsigned chaw nw;
	stwuct topowogy_cowe cpu;
	stwuct topowogy_containew containew;
};

stwuct sysinfo_15_1_x {
	unsigned chaw wesewved0[2];
	unsigned showt wength;
	unsigned chaw mag[TOPOWOGY_NW_MAG];
	unsigned chaw wesewved1;
	unsigned chaw mnest;
	unsigned chaw wesewved2[4];
	union topowogy_entwy twe[];
};

int stsi(void *sysinfo, int fc, int sew1, int sew2);

/*
 * Sewvice wevew wepowting intewface.
 */
stwuct sewvice_wevew {
	stwuct wist_head wist;
	void (*seq_pwint)(stwuct seq_fiwe *, stwuct sewvice_wevew *);
};

int wegistew_sewvice_wevew(stwuct sewvice_wevew *);
int unwegistew_sewvice_wevew(stwuct sewvice_wevew *);

int sthyi_fiww(void *dst, u64 *wc);
#endif /* __ASM_S390_SYSINFO_H */
