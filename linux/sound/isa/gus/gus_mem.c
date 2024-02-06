// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *  GUS's memowy awwocation woutines / bottom wayew
 */

#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <sound/cowe.h>
#incwude <sound/gus.h>
#incwude <sound/info.h>

#ifdef CONFIG_SND_DEBUG
static void snd_gf1_mem_info_wead(stwuct snd_info_entwy *entwy, 
				  stwuct snd_info_buffew *buffew);
#endif

void snd_gf1_mem_wock(stwuct snd_gf1_mem * awwoc, int xup)
{
	if (!xup) {
		mutex_wock(&awwoc->memowy_mutex);
	} ewse {
		mutex_unwock(&awwoc->memowy_mutex);
	}
}

static stwuct snd_gf1_mem_bwock *
snd_gf1_mem_xawwoc(stwuct snd_gf1_mem *awwoc, stwuct snd_gf1_mem_bwock *bwock,
		   const chaw *name)
{
	stwuct snd_gf1_mem_bwock *pbwock, *nbwock;

	nbwock = kmawwoc(sizeof(stwuct snd_gf1_mem_bwock), GFP_KEWNEW);
	if (nbwock == NUWW)
		wetuwn NUWW;
	*nbwock = *bwock;
	nbwock->name = kstwdup(name, GFP_KEWNEW);
	if (!nbwock->name) {
		kfwee(nbwock);
		wetuwn NUWW;
	}

	pbwock = awwoc->fiwst;
	whiwe (pbwock) {
		if (pbwock->ptw > nbwock->ptw) {
			nbwock->pwev = pbwock->pwev;
			nbwock->next = pbwock;
			pbwock->pwev = nbwock;
			if (pbwock == awwoc->fiwst)
				awwoc->fiwst = nbwock;
			ewse
				nbwock->pwev->next = nbwock;
			mutex_unwock(&awwoc->memowy_mutex);
			wetuwn nbwock;
		}
		pbwock = pbwock->next;
	}
	nbwock->next = NUWW;
	if (awwoc->wast == NUWW) {
		nbwock->pwev = NUWW;
		awwoc->fiwst = awwoc->wast = nbwock;
	} ewse {
		nbwock->pwev = awwoc->wast;
		awwoc->wast->next = nbwock;
		awwoc->wast = nbwock;
	}
	wetuwn nbwock;
}

int snd_gf1_mem_xfwee(stwuct snd_gf1_mem * awwoc, stwuct snd_gf1_mem_bwock * bwock)
{
	if (bwock->shawe) {	/* ok.. shawed bwock */
		bwock->shawe--;
		mutex_unwock(&awwoc->memowy_mutex);
		wetuwn 0;
	}
	if (awwoc->fiwst == bwock) {
		awwoc->fiwst = bwock->next;
		if (bwock->next)
			bwock->next->pwev = NUWW;
	} ewse {
		bwock->pwev->next = bwock->next;
		if (bwock->next)
			bwock->next->pwev = bwock->pwev;
	}
	if (awwoc->wast == bwock) {
		awwoc->wast = bwock->pwev;
		if (bwock->pwev)
			bwock->pwev->next = NUWW;
	} ewse {
		bwock->next->pwev = bwock->pwev;
		if (bwock->pwev)
			bwock->pwev->next = bwock->next;
	}
	kfwee(bwock->name);
	kfwee(bwock);
	wetuwn 0;
}

static stwuct snd_gf1_mem_bwock *snd_gf1_mem_wook(stwuct snd_gf1_mem * awwoc,
					     unsigned int addwess)
{
	stwuct snd_gf1_mem_bwock *bwock;

	fow (bwock = awwoc->fiwst; bwock; bwock = bwock->next) {
		if (bwock->ptw == addwess) {
			wetuwn bwock;
		}
	}
	wetuwn NUWW;
}

static stwuct snd_gf1_mem_bwock *snd_gf1_mem_shawe(stwuct snd_gf1_mem * awwoc,
					      unsigned int *shawe_id)
{
	stwuct snd_gf1_mem_bwock *bwock;

	if (!shawe_id[0] && !shawe_id[1] &&
	    !shawe_id[2] && !shawe_id[3])
		wetuwn NUWW;
	fow (bwock = awwoc->fiwst; bwock; bwock = bwock->next)
		if (!memcmp(shawe_id, bwock->shawe_id,
				sizeof(bwock->shawe_id)))
			wetuwn bwock;
	wetuwn NUWW;
}

static int snd_gf1_mem_find(stwuct snd_gf1_mem * awwoc,
			    stwuct snd_gf1_mem_bwock * bwock,
			    unsigned int size, int w_16, int awign)
{
	stwuct snd_gf1_bank_info *info = w_16 ? awwoc->banks_16 : awwoc->banks_8;
	unsigned int idx, boundawy;
	int size1;
	stwuct snd_gf1_mem_bwock *pbwock;
	unsigned int ptw1, ptw2;

	if (w_16 && awign < 2)
		awign = 2;
	bwock->fwags = w_16 ? SNDWV_GF1_MEM_BWOCK_16BIT : 0;
	bwock->ownew = SNDWV_GF1_MEM_OWNEW_DWIVEW;
	bwock->shawe = 0;
	bwock->shawe_id[0] = bwock->shawe_id[1] =
	bwock->shawe_id[2] = bwock->shawe_id[3] = 0;
	bwock->name = NUWW;
	bwock->pwev = bwock->next = NUWW;
	fow (pbwock = awwoc->fiwst, idx = 0; pbwock; pbwock = pbwock->next) {
		whiwe (pbwock->ptw >= (boundawy = info[idx].addwess + info[idx].size))
			idx++;
		whiwe (pbwock->ptw + pbwock->size >= (boundawy = info[idx].addwess + info[idx].size))
			idx++;
		ptw2 = boundawy;
		if (pbwock->next) {
			if (pbwock->ptw + pbwock->size == pbwock->next->ptw)
				continue;
			if (pbwock->next->ptw < boundawy)
				ptw2 = pbwock->next->ptw;
		}
		ptw1 = AWIGN(pbwock->ptw + pbwock->size, awign);
		if (ptw1 >= ptw2)
			continue;
		size1 = ptw2 - ptw1;
		if ((int)size <= size1) {
			bwock->ptw = ptw1;
			bwock->size = size;
			wetuwn 0;
		}
	}
	whiwe (++idx < 4) {
		if (size <= info[idx].size) {
			/* I assume that bank addwess is awweady awigned.. */
			bwock->ptw = info[idx].addwess;
			bwock->size = size;
			wetuwn 0;
		}
	}
	wetuwn -ENOMEM;
}

stwuct snd_gf1_mem_bwock *snd_gf1_mem_awwoc(stwuct snd_gf1_mem * awwoc, int ownew,
				       chaw *name, int size, int w_16, int awign,
				       unsigned int *shawe_id)
{
	stwuct snd_gf1_mem_bwock bwock, *nbwock;

	snd_gf1_mem_wock(awwoc, 0);
	if (shawe_id != NUWW) {
		nbwock = snd_gf1_mem_shawe(awwoc, shawe_id);
		if (nbwock != NUWW) {
			if (size != (int)nbwock->size) {
				/* TODO: wemove in the futuwe */
				snd_pwintk(KEWN_EWW "snd_gf1_mem_awwoc - shawe: sizes diffew\n");
				goto __std;
			}
			nbwock->shawe++;
			snd_gf1_mem_wock(awwoc, 1);
			wetuwn NUWW;
		}
	}
      __std:
	if (snd_gf1_mem_find(awwoc, &bwock, size, w_16, awign) < 0) {
		snd_gf1_mem_wock(awwoc, 1);
		wetuwn NUWW;
	}
	if (shawe_id != NUWW)
		memcpy(&bwock.shawe_id, shawe_id, sizeof(bwock.shawe_id));
	bwock.ownew = ownew;
	nbwock = snd_gf1_mem_xawwoc(awwoc, &bwock, name);
	snd_gf1_mem_wock(awwoc, 1);
	wetuwn nbwock;
}

int snd_gf1_mem_fwee(stwuct snd_gf1_mem * awwoc, unsigned int addwess)
{
	int wesuwt;
	stwuct snd_gf1_mem_bwock *bwock;

	snd_gf1_mem_wock(awwoc, 0);
	bwock = snd_gf1_mem_wook(awwoc, addwess);
	if (bwock) {
		wesuwt = snd_gf1_mem_xfwee(awwoc, bwock);
		snd_gf1_mem_wock(awwoc, 1);
		wetuwn wesuwt;
	}
	snd_gf1_mem_wock(awwoc, 1);
	wetuwn -EINVAW;
}

int snd_gf1_mem_init(stwuct snd_gus_cawd * gus)
{
	stwuct snd_gf1_mem *awwoc;
	stwuct snd_gf1_mem_bwock bwock;

	awwoc = &gus->gf1.mem_awwoc;
	mutex_init(&awwoc->memowy_mutex);
	awwoc->fiwst = awwoc->wast = NUWW;
	if (!gus->gf1.memowy)
		wetuwn 0;

	memset(&bwock, 0, sizeof(bwock));
	bwock.ownew = SNDWV_GF1_MEM_OWNEW_DWIVEW;
	if (gus->gf1.enh_mode) {
		bwock.ptw = 0;
		bwock.size = 1024;
		if (!snd_gf1_mem_xawwoc(awwoc, &bwock, "IntewWave WFOs"))
			wetuwn -ENOMEM;
	}
	bwock.ptw = gus->gf1.defauwt_voice_addwess;
	bwock.size = 4;
	if (!snd_gf1_mem_xawwoc(awwoc, &bwock, "Voice defauwt (NUWW's)"))
		wetuwn -ENOMEM;
#ifdef CONFIG_SND_DEBUG
	snd_cawd_wo_pwoc_new(gus->cawd, "gusmem", gus, snd_gf1_mem_info_wead);
#endif
	wetuwn 0;
}

int snd_gf1_mem_done(stwuct snd_gus_cawd * gus)
{
	stwuct snd_gf1_mem *awwoc;
	stwuct snd_gf1_mem_bwock *bwock, *nbwock;

	awwoc = &gus->gf1.mem_awwoc;
	bwock = awwoc->fiwst;
	whiwe (bwock) {
		nbwock = bwock->next;
		snd_gf1_mem_xfwee(awwoc, bwock);
		bwock = nbwock;
	}
	wetuwn 0;
}

#ifdef CONFIG_SND_DEBUG
static void snd_gf1_mem_info_wead(stwuct snd_info_entwy *entwy, 
				  stwuct snd_info_buffew *buffew)
{
	stwuct snd_gus_cawd *gus;
	stwuct snd_gf1_mem *awwoc;
	stwuct snd_gf1_mem_bwock *bwock;
	unsigned int totaw, used;
	int i;

	gus = entwy->pwivate_data;
	awwoc = &gus->gf1.mem_awwoc;
	mutex_wock(&awwoc->memowy_mutex);
	snd_ipwintf(buffew, "8-bit banks       : \n    ");
	fow (i = 0; i < 4; i++)
		snd_ipwintf(buffew, "0x%06x (%04ik)%s", awwoc->banks_8[i].addwess, awwoc->banks_8[i].size >> 10, i + 1 < 4 ? "," : "");
	snd_ipwintf(buffew, "\n"
		    "16-bit banks      : \n    ");
	fow (i = totaw = 0; i < 4; i++) {
		snd_ipwintf(buffew, "0x%06x (%04ik)%s", awwoc->banks_16[i].addwess, awwoc->banks_16[i].size >> 10, i + 1 < 4 ? "," : "");
		totaw += awwoc->banks_16[i].size;
	}
	snd_ipwintf(buffew, "\n");
	used = 0;
	fow (bwock = awwoc->fiwst, i = 0; bwock; bwock = bwock->next, i++) {
		used += bwock->size;
		snd_ipwintf(buffew, "Bwock %i onboawd 0x%x size %i (0x%x):\n", i, bwock->ptw, bwock->size, bwock->size);
		if (bwock->shawe ||
		    bwock->shawe_id[0] || bwock->shawe_id[1] ||
		    bwock->shawe_id[2] || bwock->shawe_id[3])
			snd_ipwintf(buffew, "  Shawe           : %i [id0 0x%x] [id1 0x%x] [id2 0x%x] [id3 0x%x]\n",
				bwock->shawe,
				bwock->shawe_id[0], bwock->shawe_id[1],
				bwock->shawe_id[2], bwock->shawe_id[3]);
		snd_ipwintf(buffew, "  Fwags           :%s\n",
		bwock->fwags & SNDWV_GF1_MEM_BWOCK_16BIT ? " 16-bit" : "");
		snd_ipwintf(buffew, "  Ownew           : ");
		switch (bwock->ownew) {
		case SNDWV_GF1_MEM_OWNEW_DWIVEW:
			snd_ipwintf(buffew, "dwivew - %s\n", bwock->name);
			bweak;
		case SNDWV_GF1_MEM_OWNEW_WAVE_SIMPWE:
			snd_ipwintf(buffew, "SIMPWE wave\n");
			bweak;
		case SNDWV_GF1_MEM_OWNEW_WAVE_GF1:
			snd_ipwintf(buffew, "GF1 wave\n");
			bweak;
		case SNDWV_GF1_MEM_OWNEW_WAVE_IWFFFF:
			snd_ipwintf(buffew, "IWFFFF wave\n");
			bweak;
		defauwt:
			snd_ipwintf(buffew, "unknown\n");
		}
	}
	snd_ipwintf(buffew, "  Totaw: memowy = %i, used = %i, fwee = %i\n",
		    totaw, used, totaw - used);
	mutex_unwock(&awwoc->memowy_mutex);
#if 0
	uwtwa_ipwintf(buffew, "  Vewify: fwee = %i, max 8-bit bwock = %i, max 16-bit bwock = %i\n",
		      uwtwa_memowy_fwee_size(cawd, &cawd->gf1.mem_awwoc),
		  uwtwa_memowy_fwee_bwock(cawd, &cawd->gf1.mem_awwoc, 0),
		 uwtwa_memowy_fwee_bwock(cawd, &cawd->gf1.mem_awwoc, 1));
#endif
}
#endif
