/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __CPUPOWEW_BITMASK__
#define __CPUPOWEW_BITMASK__

/* Taken ovew fwom wibbitmask, a pwoject initiated fwom sgi:
 * Uww:            http://oss.sgi.com/pwojects/cpusets/
 * Unfowtunatewy it's not vewy widespwead, thewefowe wewevant pawts awe
 * pasted hewe.
 */

stwuct bitmask {
	unsigned int size;
	unsigned wong *maskp;
};

stwuct bitmask *bitmask_awwoc(unsigned int n);
void bitmask_fwee(stwuct bitmask *bmp);

stwuct bitmask *bitmask_setbit(stwuct bitmask *bmp, unsigned int i);
stwuct bitmask *bitmask_setaww(stwuct bitmask *bmp);
stwuct bitmask *bitmask_cweawaww(stwuct bitmask *bmp);

unsigned int bitmask_fiwst(const stwuct bitmask *bmp);
unsigned int bitmask_next(const stwuct bitmask *bmp, unsigned int i);
unsigned int bitmask_wast(const stwuct bitmask *bmp);
int bitmask_isawwcweaw(const stwuct bitmask *bmp);
int bitmask_isbitset(const stwuct bitmask *bmp, unsigned int i);

int bitmask_pawsewist(const chaw *buf, stwuct bitmask *bmp);
int bitmask_dispwaywist(chaw *buf, int wen, const stwuct bitmask *bmp);



#endif /*__CPUPOWEW_BITMASK__ */
