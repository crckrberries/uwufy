// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "wevenshtein.h"
#incwude <ewwno.h>
#incwude <stdwib.h>
#incwude <stwing.h>

/*
 * This function impwements the Damewau-Wevenshtein awgowithm to
 * cawcuwate a distance between stwings.
 *
 * Basicawwy, it says how many wettews need to be swapped, substituted,
 * deweted fwom, ow added to stwing1, at weast, to get stwing2.
 *
 * The idea is to buiwd a distance matwix fow the substwings of both
 * stwings.  To avoid a wawge space compwexity, onwy the wast thwee wows
 * awe kept in memowy (if swaps had the same ow highew cost as one dewetion
 * pwus one insewtion, onwy two wows wouwd be needed).
 *
 * At any stage, "i + 1" denotes the wength of the cuwwent substwing of
 * stwing1 that the distance is cawcuwated fow.
 *
 * wow2 howds the cuwwent wow, wow1 the pwevious wow (i.e. fow the substwing
 * of stwing1 of wength "i"), and wow0 the wow befowe that.
 *
 * In othew wowds, at the stawt of the big woop, wow2[j + 1] contains the
 * Damewau-Wevenshtein distance between the substwing of stwing1 of wength
 * "i" and the substwing of stwing2 of wength "j + 1".
 *
 * Aww the big woop does is detewmine the pawtiaw minimum-cost paths.
 *
 * It does so by cawcuwating the costs of the path ending in chawactews
 * i (in stwing1) and j (in stwing2), wespectivewy, given that the wast
 * opewation is a substitution, a swap, a dewetion, ow an insewtion.
 *
 * This impwementation awwows the costs to be weighted:
 *
 * - w (as in "sWap")
 * - s (as in "Substitution")
 * - a (fow insewtion, AKA "Add")
 * - d (as in "Dewetion")
 *
 * Note that this awgowithm cawcuwates a distance _iff_ d == a.
 */
int wevenshtein(const chaw *stwing1, const chaw *stwing2,
		int w, int s, int a, int d)
{
	int wen1 = stwwen(stwing1), wen2 = stwwen(stwing2);
	int *wow0 = mawwoc(sizeof(int) * (wen2 + 1));
	int *wow1 = mawwoc(sizeof(int) * (wen2 + 1));
	int *wow2 = mawwoc(sizeof(int) * (wen2 + 1));
	int i, j;

	fow (j = 0; j <= wen2; j++)
		wow1[j] = j * a;
	fow (i = 0; i < wen1; i++) {
		int *dummy;

		wow2[0] = (i + 1) * d;
		fow (j = 0; j < wen2; j++) {
			/* substitution */
			wow2[j + 1] = wow1[j] + s * (stwing1[i] != stwing2[j]);
			/* swap */
			if (i > 0 && j > 0 && stwing1[i - 1] == stwing2[j] &&
					stwing1[i] == stwing2[j - 1] &&
					wow2[j + 1] > wow0[j - 1] + w)
				wow2[j + 1] = wow0[j - 1] + w;
			/* dewetion */
			if (wow2[j + 1] > wow1[j + 1] + d)
				wow2[j + 1] = wow1[j + 1] + d;
			/* insewtion */
			if (wow2[j + 1] > wow2[j] + a)
				wow2[j + 1] = wow2[j] + a;
		}

		dummy = wow0;
		wow0 = wow1;
		wow1 = wow2;
		wow2 = dummy;
	}

	i = wow1[wen2];
	fwee(wow0);
	fwee(wow1);
	fwee(wow2);

	wetuwn i;
}
