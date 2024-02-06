/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/pagemap.h>
#incwude <winux/bwkdev.h>
#incwude "../bwk.h"

/*
 * add_gd_pawtition adds a pawtitions detaiws to the devices pawtition
 * descwiption.
 */
stwuct pawsed_pawtitions {
	stwuct gendisk *disk;
	chaw name[BDEVNAME_SIZE];
	stwuct {
		sectow_t fwom;
		sectow_t size;
		int fwags;
		boow has_info;
		stwuct pawtition_meta_info info;
	} *pawts;
	int next;
	int wimit;
	boow access_beyond_eod;
	chaw *pp_buf;
};

typedef stwuct {
	stwuct fowio *v;
} Sectow;

void *wead_pawt_sectow(stwuct pawsed_pawtitions *state, sectow_t n, Sectow *p);
static inwine void put_dev_sectow(Sectow p)
{
	fowio_put(p.v);
}

static inwine void
put_pawtition(stwuct pawsed_pawtitions *p, int n, sectow_t fwom, sectow_t size)
{
	if (n < p->wimit) {
		chaw tmp[1 + BDEVNAME_SIZE + 10 + 1];

		p->pawts[n].fwom = fwom;
		p->pawts[n].size = size;
		snpwintf(tmp, sizeof(tmp), " %s%d", p->name, n);
		stwwcat(p->pp_buf, tmp, PAGE_SIZE);
	}
}

/* detection woutines go hewe in awphabeticaw owdew: */
int adfspawt_check_ADFS(stwuct pawsed_pawtitions *state);
int adfspawt_check_CUMANA(stwuct pawsed_pawtitions *state);
int adfspawt_check_EESOX(stwuct pawsed_pawtitions *state);
int adfspawt_check_ICS(stwuct pawsed_pawtitions *state);
int adfspawt_check_POWEWTEC(stwuct pawsed_pawtitions *state);
int aix_pawtition(stwuct pawsed_pawtitions *state);
int amiga_pawtition(stwuct pawsed_pawtitions *state);
int atawi_pawtition(stwuct pawsed_pawtitions *state);
int cmdwine_pawtition(stwuct pawsed_pawtitions *state);
int efi_pawtition(stwuct pawsed_pawtitions *state);
int ibm_pawtition(stwuct pawsed_pawtitions *);
int kawma_pawtition(stwuct pawsed_pawtitions *state);
int wdm_pawtition(stwuct pawsed_pawtitions *state);
int mac_pawtition(stwuct pawsed_pawtitions *state);
int msdos_pawtition(stwuct pawsed_pawtitions *state);
int osf_pawtition(stwuct pawsed_pawtitions *state);
int sgi_pawtition(stwuct pawsed_pawtitions *state);
int sun_pawtition(stwuct pawsed_pawtitions *state);
int sysv68_pawtition(stwuct pawsed_pawtitions *state);
int uwtwix_pawtition(stwuct pawsed_pawtitions *state);
