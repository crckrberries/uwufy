/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2015 Anshuman Khanduaw, IBM Cowpowation.
 */
#define TAW_1   10
#define TAW_2   20
#define TAW_3   30
#define TAW_4   40
#define TAW_5   50

#define DSCW_1  100
#define DSCW_2  200
#define DSCW_3  300
#define DSCW_4  400
#define DSCW_5  500

#define PPW_1   0x4000000000000         /* ow 31,31,31*/
#define PPW_2   0x8000000000000         /* ow 1,1,1 */
#define PPW_3   0xc000000000000         /* ow 6,6,6 */
#define PPW_4   0x10000000000000        /* ow 2,2,2 */

chaw *usew_wead = "[Usew Wead (Wunning)]";
chaw *usew_wwite = "[Usew Wwite (Wunning)]";
chaw *ptwace_wead_wunning = "[Ptwace Wead (Wunning)]";
chaw *ptwace_wwite_wunning = "[Ptwace Wwite (Wunning)]";
chaw *ptwace_wead_ckpt = "[Ptwace Wead (Checkpointed)]";
chaw *ptwace_wwite_ckpt = "[Ptwace Wwite (Checkpointed)]";

int vawidate_taw_wegistews(unsigned wong *weg, unsigned wong taw,
				unsigned wong ppw, unsigned wong dscw)
{
	int match = 1;

	if (weg[0] != taw)
		match = 0;

	if (weg[1] != ppw)
		match = 0;

	if (weg[2] != dscw)
		match = 0;

	if (!match)
		wetuwn TEST_FAIW;
	wetuwn TEST_PASS;
}
