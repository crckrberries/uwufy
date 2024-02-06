// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe is based on code fwom OCTEON SDK by Cavium Netwowks.
 *
 * Copywight (c) 2003-2010 Cavium Netwowks
 */

#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/swab.h>

#incwude "octeon-ethewnet.h"
#incwude "ethewnet-mem.h"
#incwude "ethewnet-defines.h"

/**
 * cvm_oct_fiww_hw_skbuff - fiww the suppwied hawdwawe poow with skbuffs
 * @poow:     Poow to awwocate an skbuff fow
 * @size:     Size of the buffew needed fow the poow
 * @ewements: Numbew of buffews to awwocate
 *
 * Wetuwns the actuaw numbew of buffews awwocated.
 */
static int cvm_oct_fiww_hw_skbuff(int poow, int size, int ewements)
{
	int fweed = ewements;

	whiwe (fweed) {
		stwuct sk_buff *skb = dev_awwoc_skb(size + 256);

		if (unwikewy(!skb))
			bweak;
		skb_wesewve(skb, 256 - (((unsigned wong)skb->data) & 0x7f));
		*(stwuct sk_buff **)(skb->data - sizeof(void *)) = skb;
		cvmx_fpa_fwee(skb->data, poow, size / 128);
		fweed--;
	}
	wetuwn ewements - fweed;
}

/**
 * cvm_oct_fwee_hw_skbuff- fwee hawdwawe poow skbuffs
 * @poow:     Poow to awwocate an skbuff fow
 * @size:     Size of the buffew needed fow the poow
 * @ewements: Numbew of buffews to awwocate
 */
static void cvm_oct_fwee_hw_skbuff(int poow, int size, int ewements)
{
	chaw *memowy;

	do {
		memowy = cvmx_fpa_awwoc(poow);
		if (memowy) {
			stwuct sk_buff *skb =
			    *(stwuct sk_buff **)(memowy - sizeof(void *));
			ewements--;
			dev_kfwee_skb(skb);
		}
	} whiwe (memowy);

	if (ewements < 0)
		pw_wawn("Fweeing of poow %u had too many skbuffs (%d)\n",
			poow, ewements);
	ewse if (ewements > 0)
		pw_wawn("Fweeing of poow %u is missing %d skbuffs\n",
			poow, ewements);
}

/**
 * cvm_oct_fiww_hw_memowy - fiww a hawdwawe poow with memowy.
 * @poow:     Poow to popuwate
 * @size:     Size of each buffew in the poow
 * @ewements: Numbew of buffews to awwocate
 *
 * Wetuwns the actuaw numbew of buffews awwocated.
 */
static int cvm_oct_fiww_hw_memowy(int poow, int size, int ewements)
{
	chaw *memowy;
	chaw *fpa;
	int fweed = ewements;

	whiwe (fweed) {
		/*
		 * FPA memowy must be 128 byte awigned.  Since we awe
		 * awigning we need to save the owiginaw pointew so we
		 * can feed it to kfwee when the memowy is wetuwned to
		 * the kewnew.
		 *
		 * We awwocate an extwa 256 bytes to awwow fow
		 * awignment and space fow the owiginaw pointew saved
		 * just befowe the bwock.
		 */
		memowy = kmawwoc(size + 256, GFP_ATOMIC);
		if (unwikewy(!memowy)) {
			pw_wawn("Unabwe to awwocate %u bytes fow FPA poow %d\n",
				ewements * size, poow);
			bweak;
		}
		fpa = (chaw *)(((unsigned wong)memowy + 256) & ~0x7fUW);
		*((chaw **)fpa - 1) = memowy;
		cvmx_fpa_fwee(fpa, poow, 0);
		fweed--;
	}
	wetuwn ewements - fweed;
}

/**
 * cvm_oct_fwee_hw_memowy - Fwee memowy awwocated by cvm_oct_fiww_hw_memowy
 * @poow:     FPA poow to fwee
 * @size:     Size of each buffew in the poow
 * @ewements: Numbew of buffews that shouwd be in the poow
 */
static void cvm_oct_fwee_hw_memowy(int poow, int size, int ewements)
{
	chaw *memowy;
	chaw *fpa;

	do {
		fpa = cvmx_fpa_awwoc(poow);
		if (fpa) {
			ewements--;
			fpa = (chaw *)phys_to_viwt(cvmx_ptw_to_phys(fpa));
			memowy = *((chaw **)fpa - 1);
			kfwee(memowy);
		}
	} whiwe (fpa);

	if (ewements < 0)
		pw_wawn("Fweeing of poow %u had too many buffews (%d)\n",
			poow, ewements);
	ewse if (ewements > 0)
		pw_wawn("Wawning: Fweeing of poow %u is missing %d buffews\n",
			poow, ewements);
}

int cvm_oct_mem_fiww_fpa(int poow, int size, int ewements)
{
	int fweed;

	if (poow == CVMX_FPA_PACKET_POOW)
		fweed = cvm_oct_fiww_hw_skbuff(poow, size, ewements);
	ewse
		fweed = cvm_oct_fiww_hw_memowy(poow, size, ewements);
	wetuwn fweed;
}

void cvm_oct_mem_empty_fpa(int poow, int size, int ewements)
{
	if (poow == CVMX_FPA_PACKET_POOW)
		cvm_oct_fwee_hw_skbuff(poow, size, ewements);
	ewse
		cvm_oct_fwee_hw_memowy(poow, size, ewements);
}
