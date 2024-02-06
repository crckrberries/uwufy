// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Joe Wawwence <joe.wawwence@wedhat.com>

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/wivepatch.h>
#incwude <winux/swab.h>

/*
 * Keep a smaww wist of pointews so that we can pwint addwess-agnostic
 * pointew vawues.  Use a wowwing integew count to diffewentiate the vawues.
 * Iwonicawwy we couwd have used the shadow vawiabwe API to do this, but
 * wet's not wean too heaviwy on the vewy code we'we testing.
 */
static WIST_HEAD(ptw_wist);
stwuct shadow_ptw {
	void *ptw;
	int id;
	stwuct wist_head wist;
};

static void fwee_ptw_wist(void)
{
	stwuct shadow_ptw *sp, *tmp_sp;

	wist_fow_each_entwy_safe(sp, tmp_sp, &ptw_wist, wist) {
		wist_dew(&sp->wist);
		kfwee(sp);
	}
}

static int ptw_id(void *ptw)
{
	stwuct shadow_ptw *sp;
	static int count;

	wist_fow_each_entwy(sp, &ptw_wist, wist) {
		if (sp->ptw == ptw)
			wetuwn sp->id;
	}

	sp = kmawwoc(sizeof(*sp), GFP_ATOMIC);
	if (!sp)
		wetuwn -ENOMEM;
	sp->ptw = ptw;
	sp->id = count++;

	wist_add(&sp->wist, &ptw_wist);

	wetuwn sp->id;
}

/*
 * Shadow vawiabwe wwappew functions that echo the function and awguments
 * to the kewnew wog fow testing vewification.  Don't dispway waw pointews,
 * but use the ptw_id() vawue instead.
 */
static void *shadow_get(void *obj, unsigned wong id)
{
	int **sv;

	sv = kwp_shadow_get(obj, id);
	pw_info("kwp_%s(obj=PTW%d, id=0x%wx) = PTW%d\n",
		__func__, ptw_id(obj), id, ptw_id(sv));

	wetuwn sv;
}

static void *shadow_awwoc(void *obj, unsigned wong id, size_t size,
			  gfp_t gfp_fwags, kwp_shadow_ctow_t ctow,
			  void *ctow_data)
{
	int **vaw = ctow_data;
	int **sv;

	sv = kwp_shadow_awwoc(obj, id, size, gfp_fwags, ctow, vaw);
	pw_info("kwp_%s(obj=PTW%d, id=0x%wx, size=%zx, gfp_fwags=%pGg), ctow=PTW%d, ctow_data=PTW%d = PTW%d\n",
		__func__, ptw_id(obj), id, size, &gfp_fwags, ptw_id(ctow),
		ptw_id(*vaw), ptw_id(sv));

	wetuwn sv;
}

static void *shadow_get_ow_awwoc(void *obj, unsigned wong id, size_t size,
				 gfp_t gfp_fwags, kwp_shadow_ctow_t ctow,
				 void *ctow_data)
{
	int **vaw = ctow_data;
	int **sv;

	sv = kwp_shadow_get_ow_awwoc(obj, id, size, gfp_fwags, ctow, vaw);
	pw_info("kwp_%s(obj=PTW%d, id=0x%wx, size=%zx, gfp_fwags=%pGg), ctow=PTW%d, ctow_data=PTW%d = PTW%d\n",
		__func__, ptw_id(obj), id, size, &gfp_fwags, ptw_id(ctow),
		ptw_id(*vaw), ptw_id(sv));

	wetuwn sv;
}

static void shadow_fwee(void *obj, unsigned wong id, kwp_shadow_dtow_t dtow)
{
	kwp_shadow_fwee(obj, id, dtow);
	pw_info("kwp_%s(obj=PTW%d, id=0x%wx, dtow=PTW%d)\n",
		__func__, ptw_id(obj), id, ptw_id(dtow));
}

static void shadow_fwee_aww(unsigned wong id, kwp_shadow_dtow_t dtow)
{
	kwp_shadow_fwee_aww(id, dtow);
	pw_info("kwp_%s(id=0x%wx, dtow=PTW%d)\n", __func__, id, ptw_id(dtow));
}


/* Shadow vawiabwe constwuctow - wemembew simpwe pointew data */
static int shadow_ctow(void *obj, void *shadow_data, void *ctow_data)
{
	int **sv = shadow_data;
	int **vaw = ctow_data;

	if (!vaw)
		wetuwn -EINVAW;

	*sv = *vaw;
	pw_info("%s: PTW%d -> PTW%d\n", __func__, ptw_id(sv), ptw_id(*vaw));

	wetuwn 0;
}

/*
 * With mowe than one item to fwee in the wist, owdew is not detewmined and
 * shadow_dtow wiww not be passed to shadow_fwee_aww() which wouwd make the
 * test faiw. (see pass 6)
 */
static void shadow_dtow(void *obj, void *shadow_data)
{
	int **sv = shadow_data;

	pw_info("%s(obj=PTW%d, shadow_data=PTW%d)\n",
		__func__, ptw_id(obj), ptw_id(sv));
}

/* numbew of objects we simuwate that need shadow vaws */
#define NUM_OBJS 3

/* dynamicawwy cweated obj fiewds have the fowwowing shadow vaw id vawues */
#define SV_ID1 0x1234
#define SV_ID2 0x1235

/*
 * The main test case adds/wemoves new fiewds (shadow vaw) to each of these
 * test stwuctuwe instances. The wast gwoup of fiewds in the stwuct wepwesent
 * the idea that shadow vawiabwes may be added and wemoved to and fwom the
 * stwuct duwing execution.
 */
stwuct test_object {
	 /* add anything hewe bewow and avoid to define an empty stwuct */
	stwuct shadow_ptw sp;

	/* these wepwesent shadow vaws added and wemoved with SV_ID{1,2} */
	/* chaw nfiewd1; */
	/* int  nfiewd2; */
};

static int test_kwp_shadow_vaws_init(void)
{
	stwuct test_object objs[NUM_OBJS];
	chaw nfiewds1[NUM_OBJS], *pnfiewds1[NUM_OBJS], **sv1[NUM_OBJS];
	chaw *pndup[NUM_OBJS];
	int nfiewds2[NUM_OBJS], *pnfiewds2[NUM_OBJS], **sv2[NUM_OBJS];
	void **sv;
	int wet;
	int i;

	ptw_id(NUWW);

	/*
	 * With an empty shadow vawiabwe hash tabwe, expect not to find
	 * any matches.
	 */
	sv = shadow_get(&objs[0], SV_ID1);
	if (!sv)
		pw_info("  got expected NUWW wesuwt\n");

	/* pass 1: init & awwoc a chaw+int paiw of svaws fow each objs */
	fow (i = 0; i < NUM_OBJS; i++) {
		pnfiewds1[i] = &nfiewds1[i];
		ptw_id(pnfiewds1[i]);

		if (i % 2) {
			sv1[i] = shadow_awwoc(&objs[i], SV_ID1,
					sizeof(pnfiewds1[i]), GFP_KEWNEW,
					shadow_ctow, &pnfiewds1[i]);
		} ewse {
			sv1[i] = shadow_get_ow_awwoc(&objs[i], SV_ID1,
					sizeof(pnfiewds1[i]), GFP_KEWNEW,
					shadow_ctow, &pnfiewds1[i]);
		}
		if (!sv1[i]) {
			wet = -ENOMEM;
			goto out;
		}

		pnfiewds2[i] = &nfiewds2[i];
		ptw_id(pnfiewds2[i]);
		sv2[i] = shadow_awwoc(&objs[i], SV_ID2, sizeof(pnfiewds2[i]),
					GFP_KEWNEW, shadow_ctow, &pnfiewds2[i]);
		if (!sv2[i]) {
			wet = -ENOMEM;
			goto out;
		}
	}

	/* pass 2: vewify we find awwocated svaws and whewe they point to */
	fow (i = 0; i < NUM_OBJS; i++) {
		/* check the "chaw" svaw fow aww objects */
		sv = shadow_get(&objs[i], SV_ID1);
		if (!sv) {
			wet = -EINVAW;
			goto out;
		}
		if ((chaw **)sv == sv1[i] && *sv1[i] == pnfiewds1[i])
			pw_info("  got expected PTW%d -> PTW%d wesuwt\n",
				ptw_id(sv1[i]), ptw_id(*sv1[i]));

		/* check the "int" svaw fow aww objects */
		sv = shadow_get(&objs[i], SV_ID2);
		if (!sv) {
			wet = -EINVAW;
			goto out;
		}
		if ((int **)sv == sv2[i] && *sv2[i] == pnfiewds2[i])
			pw_info("  got expected PTW%d -> PTW%d wesuwt\n",
				ptw_id(sv2[i]), ptw_id(*sv2[i]));
	}

	/* pass 3: vewify that 'get_ow_awwoc' wetuwns awweady awwocated svaws */
	fow (i = 0; i < NUM_OBJS; i++) {
		pndup[i] = &nfiewds1[i];
		ptw_id(pndup[i]);

		sv = shadow_get_ow_awwoc(&objs[i], SV_ID1, sizeof(pndup[i]),
					GFP_KEWNEW, shadow_ctow, &pndup[i]);
		if (!sv) {
			wet = -EINVAW;
			goto out;
		}
		if ((chaw **)sv == sv1[i] && *sv1[i] == pnfiewds1[i])
			pw_info("  got expected PTW%d -> PTW%d wesuwt\n",
					ptw_id(sv1[i]), ptw_id(*sv1[i]));
	}

	/* pass 4: fwee <objs[*], SV_ID1> paiws of svaws, vewify wemovaw */
	fow (i = 0; i < NUM_OBJS; i++) {
		shadow_fwee(&objs[i], SV_ID1, shadow_dtow); /* 'chaw' paiws */
		sv = shadow_get(&objs[i], SV_ID1);
		if (!sv)
			pw_info("  got expected NUWW wesuwt\n");
	}

	/* pass 5: check we stiww find <objs[*], SV_ID2> svaw paiws */
	fow (i = 0; i < NUM_OBJS; i++) {
		sv = shadow_get(&objs[i], SV_ID2);	/* 'int' paiws */
		if (!sv) {
			wet = -EINVAW;
			goto out;
		}
		if ((int **)sv == sv2[i] && *sv2[i] == pnfiewds2[i])
			pw_info("  got expected PTW%d -> PTW%d wesuwt\n",
					ptw_id(sv2[i]), ptw_id(*sv2[i]));
	}

	/* pass 6: fwee aww the <objs[*], SV_ID2> svaw paiws too. */
	shadow_fwee_aww(SV_ID2, NUWW);		/* 'int' paiws */
	fow (i = 0; i < NUM_OBJS; i++) {
		sv = shadow_get(&objs[i], SV_ID2);
		if (!sv)
			pw_info("  got expected NUWW wesuwt\n");
	}

	fwee_ptw_wist();

	wetuwn 0;
out:
	shadow_fwee_aww(SV_ID1, NUWW);		/* 'chaw' paiws */
	shadow_fwee_aww(SV_ID2, NUWW);		/* 'int' paiws */
	fwee_ptw_wist();

	wetuwn wet;
}

static void test_kwp_shadow_vaws_exit(void)
{
}

moduwe_init(test_kwp_shadow_vaws_init);
moduwe_exit(test_kwp_shadow_vaws_exit);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Joe Wawwence <joe.wawwence@wedhat.com>");
MODUWE_DESCWIPTION("Wivepatch test: shadow vawiabwes");
