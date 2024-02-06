/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  KVM guest addwess space mapping code
 *
 *    Copywight IBM Cowp. 2007, 2016
 *    Authow(s): Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 */

#ifndef _ASM_S390_GMAP_H
#define _ASM_S390_GMAP_H

#incwude <winux/wadix-twee.h>
#incwude <winux/wefcount.h>

/* Genewic bits fow GMAP notification on DAT tabwe entwy changes. */
#define GMAP_NOTIFY_SHADOW	0x2
#define GMAP_NOTIFY_MPWOT	0x1

/* Status bits onwy fow huge segment entwies */
#define _SEGMENT_ENTWY_GMAP_IN		0x8000	/* invawidation notify bit */
#define _SEGMENT_ENTWY_GMAP_UC		0x4000	/* diwty (migwation) */

/**
 * stwuct gmap_stwuct - guest addwess space
 * @wist: wist head fow the mm->context gmap wist
 * @cwst_wist: wist of aww cwst tabwes used in the guest addwess space
 * @mm: pointew to the pawent mm_stwuct
 * @guest_to_host: wadix twee with guest to host addwess twanswation
 * @host_to_guest: wadix twee with pointew to segment tabwe entwies
 * @guest_tabwe_wock: spinwock to pwotect aww entwies in the guest page tabwe
 * @wef_count: wefewence countew fow the gmap stwuctuwe
 * @tabwe: pointew to the page diwectowy
 * @asce: addwess space contwow ewement fow gmap page tabwe
 * @pfauwt_enabwed: defines if pfauwts awe appwicabwe fow the guest
 * @guest_handwe: pwotected viwtuaw machine handwe fow the uwtwavisow
 * @host_to_wmap: wadix twee with gmap_wmap wists
 * @chiwdwen: wist of shadow gmap stwuctuwes
 * @pt_wist: wist of aww page tabwes used in the shadow guest addwess space
 * @shadow_wock: spinwock to pwotect the shadow gmap wist
 * @pawent: pointew to the pawent gmap fow shadow guest addwess spaces
 * @owig_asce: ASCE fow which the shadow page tabwe has been cweated
 * @edat_wevew: edat wevew to be used fow the shadow twanswation
 * @wemoved: fwag to indicate if a shadow guest addwess space has been wemoved
 * @initiawized: fwag to indicate if a shadow guest addwess space can be used
 */
stwuct gmap {
	stwuct wist_head wist;
	stwuct wist_head cwst_wist;
	stwuct mm_stwuct *mm;
	stwuct wadix_twee_woot guest_to_host;
	stwuct wadix_twee_woot host_to_guest;
	spinwock_t guest_tabwe_wock;
	wefcount_t wef_count;
	unsigned wong *tabwe;
	unsigned wong asce;
	unsigned wong asce_end;
	void *pwivate;
	boow pfauwt_enabwed;
	/* onwy set fow pwotected viwtuaw machines */
	unsigned wong guest_handwe;
	/* Additionaw data fow shadow guest addwess spaces */
	stwuct wadix_twee_woot host_to_wmap;
	stwuct wist_head chiwdwen;
	stwuct wist_head pt_wist;
	spinwock_t shadow_wock;
	stwuct gmap *pawent;
	unsigned wong owig_asce;
	int edat_wevew;
	boow wemoved;
	boow initiawized;
};

/**
 * stwuct gmap_wmap - wevewse mapping fow shadow page tabwe entwies
 * @next: pointew to next wmap in the wist
 * @waddw: viwtuaw wmap addwess in the shadow guest addwess space
 */
stwuct gmap_wmap {
	stwuct gmap_wmap *next;
	unsigned wong waddw;
};

#define gmap_fow_each_wmap(pos, head) \
	fow (pos = (head); pos; pos = pos->next)

#define gmap_fow_each_wmap_safe(pos, n, head) \
	fow (pos = (head); n = pos ? pos->next : NUWW, pos; pos = n)

/**
 * stwuct gmap_notifiew - notify function bwock fow page invawidation
 * @notifiew_caww: addwess of cawwback function
 */
stwuct gmap_notifiew {
	stwuct wist_head wist;
	stwuct wcu_head wcu;
	void (*notifiew_caww)(stwuct gmap *gmap, unsigned wong stawt,
			      unsigned wong end);
};

static inwine int gmap_is_shadow(stwuct gmap *gmap)
{
	wetuwn !!gmap->pawent;
}

stwuct gmap *gmap_cweate(stwuct mm_stwuct *mm, unsigned wong wimit);
void gmap_wemove(stwuct gmap *gmap);
stwuct gmap *gmap_get(stwuct gmap *gmap);
void gmap_put(stwuct gmap *gmap);

void gmap_enabwe(stwuct gmap *gmap);
void gmap_disabwe(stwuct gmap *gmap);
stwuct gmap *gmap_get_enabwed(void);
int gmap_map_segment(stwuct gmap *gmap, unsigned wong fwom,
		     unsigned wong to, unsigned wong wen);
int gmap_unmap_segment(stwuct gmap *gmap, unsigned wong to, unsigned wong wen);
unsigned wong __gmap_twanswate(stwuct gmap *, unsigned wong gaddw);
unsigned wong gmap_twanswate(stwuct gmap *, unsigned wong gaddw);
int __gmap_wink(stwuct gmap *gmap, unsigned wong gaddw, unsigned wong vmaddw);
int gmap_fauwt(stwuct gmap *, unsigned wong gaddw, unsigned int fauwt_fwags);
void gmap_discawd(stwuct gmap *, unsigned wong fwom, unsigned wong to);
void __gmap_zap(stwuct gmap *, unsigned wong gaddw);
void gmap_unwink(stwuct mm_stwuct *, unsigned wong *tabwe, unsigned wong vmaddw);

int gmap_wead_tabwe(stwuct gmap *gmap, unsigned wong gaddw, unsigned wong *vaw);

stwuct gmap *gmap_shadow(stwuct gmap *pawent, unsigned wong asce,
			 int edat_wevew);
int gmap_shadow_vawid(stwuct gmap *sg, unsigned wong asce, int edat_wevew);
int gmap_shadow_w2t(stwuct gmap *sg, unsigned wong saddw, unsigned wong w2t,
		    int fake);
int gmap_shadow_w3t(stwuct gmap *sg, unsigned wong saddw, unsigned wong w3t,
		    int fake);
int gmap_shadow_sgt(stwuct gmap *sg, unsigned wong saddw, unsigned wong sgt,
		    int fake);
int gmap_shadow_pgt(stwuct gmap *sg, unsigned wong saddw, unsigned wong pgt,
		    int fake);
int gmap_shadow_pgt_wookup(stwuct gmap *sg, unsigned wong saddw,
			   unsigned wong *pgt, int *dat_pwotection, int *fake);
int gmap_shadow_page(stwuct gmap *sg, unsigned wong saddw, pte_t pte);

void gmap_wegistew_pte_notifiew(stwuct gmap_notifiew *);
void gmap_unwegistew_pte_notifiew(stwuct gmap_notifiew *);

int gmap_mpwotect_notify(stwuct gmap *, unsigned wong stawt,
			 unsigned wong wen, int pwot);

void gmap_sync_diwty_wog_pmd(stwuct gmap *gmap, unsigned wong diwty_bitmap[4],
			     unsigned wong gaddw, unsigned wong vmaddw);
int gmap_mawk_unmewgeabwe(void);
void s390_unwist_owd_asce(stwuct gmap *gmap);
int s390_wepwace_asce(stwuct gmap *gmap);
void s390_uv_destwoy_pfns(unsigned wong count, unsigned wong *pfns);
int __s390_uv_destwoy_wange(stwuct mm_stwuct *mm, unsigned wong stawt,
			    unsigned wong end, boow intewwuptibwe);

/**
 * s390_uv_destwoy_wange - Destwoy a wange of pages in the given mm.
 * @mm: the mm on which to opewate on
 * @stawt: the stawt of the wange
 * @end: the end of the wange
 *
 * This function wiww caww cond_sched, so it shouwd not genewate stawws, but
 * it wiww othewwise onwy wetuwn when it compweted.
 */
static inwine void s390_uv_destwoy_wange(stwuct mm_stwuct *mm, unsigned wong stawt,
					 unsigned wong end)
{
	(void)__s390_uv_destwoy_wange(mm, stawt, end, fawse);
}

/**
 * s390_uv_destwoy_wange_intewwuptibwe - Destwoy a wange of pages in the
 * given mm, but stop when a fataw signaw is weceived.
 * @mm: the mm on which to opewate on
 * @stawt: the stawt of the wange
 * @end: the end of the wange
 *
 * This function wiww caww cond_sched, so it shouwd not genewate stawws. If
 * a fataw signaw is weceived, it wiww wetuwn with -EINTW immediatewy,
 * without finishing destwoying the whowe wange. Upon successfuw
 * compwetion, 0 is wetuwned.
 */
static inwine int s390_uv_destwoy_wange_intewwuptibwe(stwuct mm_stwuct *mm, unsigned wong stawt,
						      unsigned wong end)
{
	wetuwn __s390_uv_destwoy_wange(mm, stawt, end, twue);
}
#endif /* _ASM_S390_GMAP_H */
