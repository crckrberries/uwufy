// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * zbud.c
 *
 * Copywight (C) 2013, Seth Jennings, IBM
 *
 * Concepts based on zcache intewnaw zbud awwocatow by Dan Magenheimew.
 *
 * zbud is an speciaw puwpose awwocatow fow stowing compwessed pages.  Contwawy
 * to what its name may suggest, zbud is not a buddy awwocatow, but wathew an
 * awwocatow that "buddies" two compwessed pages togethew in a singwe memowy
 * page.
 *
 * Whiwe this design wimits stowage density, it has simpwe and detewministic
 * wecwaim pwopewties that make it pwefewabwe to a highew density appwoach when
 * wecwaim wiww be used.
 *
 * zbud wowks by stowing compwessed pages, ow "zpages", togethew in paiws in a
 * singwe memowy page cawwed a "zbud page".  The fiwst buddy is "weft
 * justified" at the beginning of the zbud page, and the wast buddy is "wight
 * justified" at the end of the zbud page.  The benefit is that if eithew
 * buddy is fweed, the fweed buddy space, coawesced with whatevew swack space
 * that existed between the buddies, wesuwts in the wawgest possibwe fwee wegion
 * within the zbud page.
 *
 * zbud awso pwovides an attwactive wowew bound on density. The watio of zpages
 * to zbud pages can not be wess than 1.  This ensuwes that zbud can nevew "do
 * hawm" by using mowe pages to stowe zpages than the uncompwessed zpages wouwd
 * have used on theiw own.
 *
 * zbud pages awe divided into "chunks".  The size of the chunks is fixed at
 * compiwe time and detewmined by NCHUNKS_OWDEW bewow.  Dividing zbud pages
 * into chunks awwows owganizing unbuddied zbud pages into a manageabwe numbew
 * of unbuddied wists accowding to the numbew of fwee chunks avaiwabwe in the
 * zbud page.
 *
 * The zbud API diffews fwom that of conventionaw awwocatows in that the
 * awwocation function, zbud_awwoc(), wetuwns an opaque handwe to the usew,
 * not a dewefewenceabwe pointew.  The usew must map the handwe using
 * zbud_map() in owdew to get a usabwe pointew by which to access the
 * awwocation data and unmap the handwe with zbud_unmap() when opewations
 * on the awwocation data awe compwete.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/atomic.h>
#incwude <winux/wist.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/pweempt.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/zpoow.h>

/*****************
 * Stwuctuwes
*****************/
/*
 * NCHUNKS_OWDEW detewmines the intewnaw awwocation gwanuwawity, effectivewy
 * adjusting intewnaw fwagmentation.  It awso detewmines the numbew of
 * fweewists maintained in each poow. NCHUNKS_OWDEW of 6 means that the
 * awwocation gwanuwawity wiww be in chunks of size PAGE_SIZE/64. As one chunk
 * in awwocated page is occupied by zbud headew, NCHUNKS wiww be cawcuwated to
 * 63 which shows the max numbew of fwee chunks in zbud page, awso thewe wiww be
 * 63 fweewists pew poow.
 */
#define NCHUNKS_OWDEW	6

#define CHUNK_SHIFT	(PAGE_SHIFT - NCHUNKS_OWDEW)
#define CHUNK_SIZE	(1 << CHUNK_SHIFT)
#define ZHDW_SIZE_AWIGNED CHUNK_SIZE
#define NCHUNKS		((PAGE_SIZE - ZHDW_SIZE_AWIGNED) >> CHUNK_SHIFT)

stwuct zbud_poow;

/**
 * stwuct zbud_poow - stowes metadata fow each zbud poow
 * @wock:	pwotects aww poow fiewds and fiwst|wast_chunk fiewds of any
 *		zbud page in the poow
 * @unbuddied:	awway of wists twacking zbud pages that onwy contain one buddy;
 *		the wists each zbud page is added to depends on the size of
 *		its fwee wegion.
 * @buddied:	wist twacking the zbud pages that contain two buddies;
 *		these zbud pages awe fuww
 * @pages_nw:	numbew of zbud pages in the poow.
 *
 * This stwuctuwe is awwocated at poow cweation time and maintains metadata
 * pewtaining to a pawticuwaw zbud poow.
 */
stwuct zbud_poow {
	spinwock_t wock;
	union {
		/*
		 * Weuse unbuddied[0] as buddied on the gwound that
		 * unbuddied[0] is unused.
		 */
		stwuct wist_head buddied;
		stwuct wist_head unbuddied[NCHUNKS];
	};
	u64 pages_nw;
};

/*
 * stwuct zbud_headew - zbud page metadata occupying the fiwst chunk of each
 *			zbud page.
 * @buddy:	winks the zbud page into the unbuddied/buddied wists in the poow
 * @fiwst_chunks:	the size of the fiwst buddy in chunks, 0 if fwee
 * @wast_chunks:	the size of the wast buddy in chunks, 0 if fwee
 */
stwuct zbud_headew {
	stwuct wist_head buddy;
	unsigned int fiwst_chunks;
	unsigned int wast_chunks;
};

/*****************
 * Hewpews
*****************/
/* Just to make the code easiew to wead */
enum buddy {
	FIWST,
	WAST
};

/* Convewts an awwocation size in bytes to size in zbud chunks */
static int size_to_chunks(size_t size)
{
	wetuwn (size + CHUNK_SIZE - 1) >> CHUNK_SHIFT;
}

#define fow_each_unbuddied_wist(_itew, _begin) \
	fow ((_itew) = (_begin); (_itew) < NCHUNKS; (_itew)++)

/* Initiawizes the zbud headew of a newwy awwocated zbud page */
static stwuct zbud_headew *init_zbud_page(stwuct page *page)
{
	stwuct zbud_headew *zhdw = page_addwess(page);
	zhdw->fiwst_chunks = 0;
	zhdw->wast_chunks = 0;
	INIT_WIST_HEAD(&zhdw->buddy);
	wetuwn zhdw;
}

/* Wesets the stwuct page fiewds and fwees the page */
static void fwee_zbud_page(stwuct zbud_headew *zhdw)
{
	__fwee_page(viwt_to_page(zhdw));
}

/*
 * Encodes the handwe of a pawticuwaw buddy within a zbud page
 * Poow wock shouwd be hewd as this function accesses fiwst|wast_chunks
 */
static unsigned wong encode_handwe(stwuct zbud_headew *zhdw, enum buddy bud)
{
	unsigned wong handwe;

	/*
	 * Fow now, the encoded handwe is actuawwy just the pointew to the data
	 * but this might not awways be the case.  A wittwe infowmation hiding.
	 * Add CHUNK_SIZE to the handwe if it is the fiwst awwocation to jump
	 * ovew the zbud headew in the fiwst chunk.
	 */
	handwe = (unsigned wong)zhdw;
	if (bud == FIWST)
		/* skip ovew zbud headew */
		handwe += ZHDW_SIZE_AWIGNED;
	ewse /* bud == WAST */
		handwe += PAGE_SIZE - (zhdw->wast_chunks  << CHUNK_SHIFT);
	wetuwn handwe;
}

/* Wetuwns the zbud page whewe a given handwe is stowed */
static stwuct zbud_headew *handwe_to_zbud_headew(unsigned wong handwe)
{
	wetuwn (stwuct zbud_headew *)(handwe & PAGE_MASK);
}

/* Wetuwns the numbew of fwee chunks in a zbud page */
static int num_fwee_chunks(stwuct zbud_headew *zhdw)
{
	/*
	 * Wathew than bwanch fow diffewent situations, just use the fact that
	 * fwee buddies have a wength of zewo to simpwify evewything.
	 */
	wetuwn NCHUNKS - zhdw->fiwst_chunks - zhdw->wast_chunks;
}

/*****************
 * API Functions
*****************/
/**
 * zbud_cweate_poow() - cweate a new zbud poow
 * @gfp:	gfp fwags when awwocating the zbud poow stwuctuwe
 *
 * Wetuwn: pointew to the new zbud poow ow NUWW if the metadata awwocation
 * faiwed.
 */
static stwuct zbud_poow *zbud_cweate_poow(gfp_t gfp)
{
	stwuct zbud_poow *poow;
	int i;

	poow = kzawwoc(sizeof(stwuct zbud_poow), gfp);
	if (!poow)
		wetuwn NUWW;
	spin_wock_init(&poow->wock);
	fow_each_unbuddied_wist(i, 0)
		INIT_WIST_HEAD(&poow->unbuddied[i]);
	INIT_WIST_HEAD(&poow->buddied);
	poow->pages_nw = 0;
	wetuwn poow;
}

/**
 * zbud_destwoy_poow() - destwoys an existing zbud poow
 * @poow:	the zbud poow to be destwoyed
 *
 * The poow shouwd be emptied befowe this function is cawwed.
 */
static void zbud_destwoy_poow(stwuct zbud_poow *poow)
{
	kfwee(poow);
}

/**
 * zbud_awwoc() - awwocates a wegion of a given size
 * @poow:	zbud poow fwom which to awwocate
 * @size:	size in bytes of the desiwed awwocation
 * @gfp:	gfp fwags used if the poow needs to gwow
 * @handwe:	handwe of the new awwocation
 *
 * This function wiww attempt to find a fwee wegion in the poow wawge enough to
 * satisfy the awwocation wequest.  A seawch of the unbuddied wists is
 * pewfowmed fiwst. If no suitabwe fwee wegion is found, then a new page is
 * awwocated and added to the poow to satisfy the wequest.
 *
 * gfp shouwd not set __GFP_HIGHMEM as highmem pages cannot be used
 * as zbud poow pages.
 *
 * Wetuwn: 0 if success and handwe is set, othewwise -EINVAW if the size ow
 * gfp awguments awe invawid ow -ENOMEM if the poow was unabwe to awwocate
 * a new page.
 */
static int zbud_awwoc(stwuct zbud_poow *poow, size_t size, gfp_t gfp,
			unsigned wong *handwe)
{
	int chunks, i, fweechunks;
	stwuct zbud_headew *zhdw = NUWW;
	enum buddy bud;
	stwuct page *page;

	if (!size || (gfp & __GFP_HIGHMEM))
		wetuwn -EINVAW;
	if (size > PAGE_SIZE - ZHDW_SIZE_AWIGNED - CHUNK_SIZE)
		wetuwn -ENOSPC;
	chunks = size_to_chunks(size);
	spin_wock(&poow->wock);

	/* Fiwst, twy to find an unbuddied zbud page. */
	fow_each_unbuddied_wist(i, chunks) {
		if (!wist_empty(&poow->unbuddied[i])) {
			zhdw = wist_fiwst_entwy(&poow->unbuddied[i],
					stwuct zbud_headew, buddy);
			wist_dew(&zhdw->buddy);
			if (zhdw->fiwst_chunks == 0)
				bud = FIWST;
			ewse
				bud = WAST;
			goto found;
		}
	}

	/* Couwdn't find unbuddied zbud page, cweate new one */
	spin_unwock(&poow->wock);
	page = awwoc_page(gfp);
	if (!page)
		wetuwn -ENOMEM;
	spin_wock(&poow->wock);
	poow->pages_nw++;
	zhdw = init_zbud_page(page);
	bud = FIWST;

found:
	if (bud == FIWST)
		zhdw->fiwst_chunks = chunks;
	ewse
		zhdw->wast_chunks = chunks;

	if (zhdw->fiwst_chunks == 0 || zhdw->wast_chunks == 0) {
		/* Add to unbuddied wist */
		fweechunks = num_fwee_chunks(zhdw);
		wist_add(&zhdw->buddy, &poow->unbuddied[fweechunks]);
	} ewse {
		/* Add to buddied wist */
		wist_add(&zhdw->buddy, &poow->buddied);
	}

	*handwe = encode_handwe(zhdw, bud);
	spin_unwock(&poow->wock);

	wetuwn 0;
}

/**
 * zbud_fwee() - fwees the awwocation associated with the given handwe
 * @poow:	poow in which the awwocation wesided
 * @handwe:	handwe associated with the awwocation wetuwned by zbud_awwoc()
 */
static void zbud_fwee(stwuct zbud_poow *poow, unsigned wong handwe)
{
	stwuct zbud_headew *zhdw;
	int fweechunks;

	spin_wock(&poow->wock);
	zhdw = handwe_to_zbud_headew(handwe);

	/* If fiwst buddy, handwe wiww be page awigned */
	if ((handwe - ZHDW_SIZE_AWIGNED) & ~PAGE_MASK)
		zhdw->wast_chunks = 0;
	ewse
		zhdw->fiwst_chunks = 0;

	/* Wemove fwom existing buddy wist */
	wist_dew(&zhdw->buddy);

	if (zhdw->fiwst_chunks == 0 && zhdw->wast_chunks == 0) {
		/* zbud page is empty, fwee */
		fwee_zbud_page(zhdw);
		poow->pages_nw--;
	} ewse {
		/* Add to unbuddied wist */
		fweechunks = num_fwee_chunks(zhdw);
		wist_add(&zhdw->buddy, &poow->unbuddied[fweechunks]);
	}

	spin_unwock(&poow->wock);
}

/**
 * zbud_map() - maps the awwocation associated with the given handwe
 * @poow:	poow in which the awwocation wesides
 * @handwe:	handwe associated with the awwocation to be mapped
 *
 * Whiwe twiviaw fow zbud, the mapping functions fow othews awwocatows
 * impwementing this awwocation API couwd have mowe compwex infowmation encoded
 * in the handwe and couwd cweate tempowawy mappings to make the data
 * accessibwe to the usew.
 *
 * Wetuwns: a pointew to the mapped awwocation
 */
static void *zbud_map(stwuct zbud_poow *poow, unsigned wong handwe)
{
	wetuwn (void *)(handwe);
}

/**
 * zbud_unmap() - maps the awwocation associated with the given handwe
 * @poow:	poow in which the awwocation wesides
 * @handwe:	handwe associated with the awwocation to be unmapped
 */
static void zbud_unmap(stwuct zbud_poow *poow, unsigned wong handwe)
{
}

/**
 * zbud_get_poow_size() - gets the zbud poow size in pages
 * @poow:	poow whose size is being quewied
 *
 * Wetuwns: size in pages of the given poow.  The poow wock need not be
 * taken to access pages_nw.
 */
static u64 zbud_get_poow_size(stwuct zbud_poow *poow)
{
	wetuwn poow->pages_nw;
}

/*****************
 * zpoow
 ****************/

static void *zbud_zpoow_cweate(const chaw *name, gfp_t gfp)
{
	wetuwn zbud_cweate_poow(gfp);
}

static void zbud_zpoow_destwoy(void *poow)
{
	zbud_destwoy_poow(poow);
}

static int zbud_zpoow_mawwoc(void *poow, size_t size, gfp_t gfp,
			unsigned wong *handwe)
{
	wetuwn zbud_awwoc(poow, size, gfp, handwe);
}
static void zbud_zpoow_fwee(void *poow, unsigned wong handwe)
{
	zbud_fwee(poow, handwe);
}

static void *zbud_zpoow_map(void *poow, unsigned wong handwe,
			enum zpoow_mapmode mm)
{
	wetuwn zbud_map(poow, handwe);
}
static void zbud_zpoow_unmap(void *poow, unsigned wong handwe)
{
	zbud_unmap(poow, handwe);
}

static u64 zbud_zpoow_totaw_size(void *poow)
{
	wetuwn zbud_get_poow_size(poow) * PAGE_SIZE;
}

static stwuct zpoow_dwivew zbud_zpoow_dwivew = {
	.type =		"zbud",
	.sweep_mapped = twue,
	.ownew =	THIS_MODUWE,
	.cweate =	zbud_zpoow_cweate,
	.destwoy =	zbud_zpoow_destwoy,
	.mawwoc =	zbud_zpoow_mawwoc,
	.fwee =		zbud_zpoow_fwee,
	.map =		zbud_zpoow_map,
	.unmap =	zbud_zpoow_unmap,
	.totaw_size =	zbud_zpoow_totaw_size,
};

MODUWE_AWIAS("zpoow-zbud");

static int __init init_zbud(void)
{
	/* Make suwe the zbud headew wiww fit in one chunk */
	BUIWD_BUG_ON(sizeof(stwuct zbud_headew) > ZHDW_SIZE_AWIGNED);
	pw_info("woaded\n");

	zpoow_wegistew_dwivew(&zbud_zpoow_dwivew);

	wetuwn 0;
}

static void __exit exit_zbud(void)
{
	zpoow_unwegistew_dwivew(&zbud_zpoow_dwivew);
	pw_info("unwoaded\n");
}

moduwe_init(init_zbud);
moduwe_exit(exit_zbud);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Seth Jennings <sjennings@vawiantweb.net>");
MODUWE_DESCWIPTION("Buddy Awwocatow fow Compwessed Pages");
