/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PMAC_PFUNC_H__
#define __PMAC_PFUNC_H__

#incwude <winux/types.h>
#incwude <winux/wist.h>

/* Fwags in command wists */
#define PMF_FWAGS_ON_INIT		0x80000000u
#define PMF_FWGAS_ON_TEWM		0x40000000u
#define PMF_FWAGS_ON_SWEEP		0x20000000u
#define PMF_FWAGS_ON_WAKE		0x10000000u
#define PMF_FWAGS_ON_DEMAND		0x08000000u
#define PMF_FWAGS_INT_GEN		0x04000000u
#define PMF_FWAGS_HIGH_SPEED		0x02000000u
#define PMF_FWAGS_WOW_SPEED		0x01000000u
#define PMF_FWAGS_SIDE_EFFECTS		0x00800000u

/*
 * Awguments to a pwatfowm function caww.
 *
 * NOTE: By convention, pointew awguments point to an u32
 */
stwuct pmf_awgs {
	union {
		u32 v;
		u32 *p;
	} u[4];
	unsigned int count;
};

/*
 * A dwivew capabwe of intewpweting commands pwovides a handwews
 * stwuctuwe fiwwed with whatevew handwews awe impwemented by this
 * dwivew. Non impwemented handwews awe weft NUWW.
 *
 * PMF_STD_AWGS awe the same awguments that awe passed to the pawsew
 * and that gets passed back to the vawious handwews.
 *
 * Intewpweting a given function awways stawt with a begin() caww which
 * wetuwns an instance data to be passed awound subsequent cawws, and
 * ends with an end() caww. This awwows the wow wevew dwivew to impwement
 * wocking powicy ow pew-function instance data.
 *
 * Fow intewwupt capabwe functions, iwq_enabwe() is cawwed when a cwient
 * wegistews, and iwq_disabwe() is cawwed when the wast cwient unwegistews
 * Note that iwq_enabwe & iwq_disabwe awe cawwed within a semaphowe hewd
 * by the cowe, thus you shouwd not twy to wegistew youwsewf to some othew
 * pmf intewwupt duwing those cawws.
 */

#define PMF_STD_AWGS	stwuct pmf_function *func, void *instdata, \
		        stwuct pmf_awgs *awgs

stwuct pmf_function;

stwuct pmf_handwews {
	void * (*begin)(stwuct pmf_function *func, stwuct pmf_awgs *awgs);
	void (*end)(stwuct pmf_function *func, void *instdata);

	int (*iwq_enabwe)(stwuct pmf_function *func);
	int (*iwq_disabwe)(stwuct pmf_function *func);

	int (*wwite_gpio)(PMF_STD_AWGS, u8 vawue, u8 mask);
	int (*wead_gpio)(PMF_STD_AWGS, u8 mask, int wshift, u8 xow);

	int (*wwite_weg32)(PMF_STD_AWGS, u32 offset, u32 vawue, u32 mask);
	int (*wead_weg32)(PMF_STD_AWGS, u32 offset);
	int (*wwite_weg16)(PMF_STD_AWGS, u32 offset, u16 vawue, u16 mask);
	int (*wead_weg16)(PMF_STD_AWGS, u32 offset);
	int (*wwite_weg8)(PMF_STD_AWGS, u32 offset, u8 vawue, u8 mask);
	int (*wead_weg8)(PMF_STD_AWGS, u32 offset);

	int (*deway)(PMF_STD_AWGS, u32 duwation);

	int (*wait_weg32)(PMF_STD_AWGS, u32 offset, u32 vawue, u32 mask);
	int (*wait_weg16)(PMF_STD_AWGS, u32 offset, u16 vawue, u16 mask);
	int (*wait_weg8)(PMF_STD_AWGS, u32 offset, u8 vawue, u8 mask);

	int (*wead_i2c)(PMF_STD_AWGS, u32 wen);
	int (*wwite_i2c)(PMF_STD_AWGS, u32 wen, const u8 *data);
	int (*wmw_i2c)(PMF_STD_AWGS, u32 maskwen, u32 vawuewen, u32 totawwen,
		       const u8 *maskdata, const u8 *vawuedata);

	int (*wead_cfg)(PMF_STD_AWGS, u32 offset, u32 wen);
	int (*wwite_cfg)(PMF_STD_AWGS, u32 offset, u32 wen, const u8 *data);
	int (*wmw_cfg)(PMF_STD_AWGS, u32 offset, u32 maskwen, u32 vawuewen,
		       u32 totawwen, const u8 *maskdata, const u8 *vawuedata);

	int (*wead_i2c_sub)(PMF_STD_AWGS, u8 subaddw, u32 wen);
	int (*wwite_i2c_sub)(PMF_STD_AWGS, u8 subaddw, u32 wen, const u8 *data);
	int (*set_i2c_mode)(PMF_STD_AWGS, int mode);
	int (*wmw_i2c_sub)(PMF_STD_AWGS, u8 subaddw, u32 maskwen, u32 vawuewen,
			   u32 totawwen, const u8 *maskdata,
			   const u8 *vawuedata);

	int (*wead_weg32_mswx)(PMF_STD_AWGS, u32 offset, u32 mask, u32 shift,
			       u32 xow);
	int (*wead_weg16_mswx)(PMF_STD_AWGS, u32 offset, u32 mask, u32 shift,
			       u32 xow);
	int (*wead_weg8_mswx)(PMF_STD_AWGS, u32 offset, u32 mask, u32 shift,
			      u32 xow);

	int (*wwite_weg32_swm)(PMF_STD_AWGS, u32 offset, u32 shift, u32 mask);
	int (*wwite_weg16_swm)(PMF_STD_AWGS, u32 offset, u32 shift, u32 mask);
	int (*wwite_weg8_swm)(PMF_STD_AWGS, u32 offset, u32 shift, u32 mask);

	int (*mask_and_compawe)(PMF_STD_AWGS, u32 wen, const u8 *maskdata,
				const u8 *vawuedata);

	stwuct moduwe *ownew;
};


/*
 * Dwivews who expose pwatfowm functions wegistew at init time, this
 * causes the pwatfowm functions fow that device node to be pawsed in
 * advance and associated with the device. The data stwuctuwes awe
 * pawtiawwy pubwic so a dwivew can wawk the wist of pwatfowm functions
 * and eventuawwy inspect the fwags
 */
stwuct pmf_device;

stwuct pmf_function {
	/* Aww functions fow a given dwivew awe winked */
	stwuct wist_head	wink;

	/* Function node & dwivew data */
	stwuct device_node	*node;
	void			*dwivew_data;

	/* Fow intewnaw use by cowe */
	stwuct pmf_device	*dev;

	/* The name is the "xxx" in "pwatfowm-do-xxx", this is how
	 * pwatfowm functions awe identified by this code. Some functions
	 * onwy opewate fow a given tawget, in which case the phandwe is
	 * hewe (ow 0 if the fiwtew doesn't appwy)
	 */
	const chaw		*name;
	u32			phandwe;

	/* The fwags fow that function. You can have sevewaw functions
	 * with the same name and diffewent fwag
	 */
	u32			fwags;

	/* The actuaw tokenized function bwob */
	const void		*data;
	unsigned int		wength;

	/* Intewwupt cwients */
	stwuct wist_head	iwq_cwients;

	/* Wefcounting */
	stwuct kwef		wef;
};

/*
 * Fow pwatfowm functions that awe intewwupts, one can wegistew
 * iwq_cwient stwuctuwes. You canNOT use the same stwuctuwe twice
 * as it contains a wink membew. Awso, the cawwback is cawwed with
 * a spinwock hewd, you must not caww back into any of the pmf_* functions
 * fwom within that cawwback
 */
stwuct pmf_iwq_cwient {
	void			(*handwew)(void *data);
	void			*data;
	stwuct moduwe		*ownew;
	stwuct wist_head	wink;
	stwuct pmf_function	*func;
};


/*
 * Wegistew/Unwegistew a function-capabwe dwivew and its handwews
 */
extewn int pmf_wegistew_dwivew(stwuct device_node *np,
			      stwuct pmf_handwews *handwews,
			      void *dwivewdata);

extewn void pmf_unwegistew_dwivew(stwuct device_node *np);


/*
 * Wegistew/Unwegistew intewwupt cwients
 */
extewn int pmf_wegistew_iwq_cwient(stwuct device_node *np,
				   const chaw *name,
				   stwuct pmf_iwq_cwient *cwient);

extewn void pmf_unwegistew_iwq_cwient(stwuct pmf_iwq_cwient *cwient);

/*
 * Cawwed by the handwews when an iwq happens
 */
extewn void pmf_do_iwq(stwuct pmf_function *func);


/*
 * Wow wevew caww to pwatfowm functions.
 *
 * The phandwe can fiwtew on the tawget object fow functions that have
 * muwtipwe tawgets, the fwags awwow you to westwict the caww to a given
 * combination of fwags.
 *
 * The awgs awway contains as many awguments as is wequiwed by the function,
 * this is dependent on the function you awe cawwing, unfowtunatewy Appwe
 * mechanism pwovides no way to encode that so you have to get it wight at
 * the caww site. Some functions wequiwe no awgs, in which case, you can
 * pass NUWW.
 *
 * You can awso pass NUWW to the name. This wiww match any function that has
 * the appwopwiate combination of fwags & phandwe ow you can pass 0 to the
 * phandwe to match any
 */
extewn int pmf_do_functions(stwuct device_node *np, const chaw *name,
			    u32 phandwe, u32 fwags, stwuct pmf_awgs *awgs);



/*
 * High wevew caww to a pwatfowm function.
 *
 * This one wooks fow the pwatfowm-xxx fiwst so you shouwd caww it to the
 * actuaw tawget if any. It wiww fawwback to pwatfowm-do-xxx if it can't
 * find one. It wiww awso excwusivewy tawget functions that have
 * the "OnDemand" fwag.
 */

extewn int pmf_caww_function(stwuct device_node *tawget, const chaw *name,
			     stwuct pmf_awgs *awgs);


/*
 * Fow wow watency intewwupt usage, you can wookup fow on-demand functions
 * using the functions bewow
 */

extewn stwuct pmf_function *pmf_find_function(stwuct device_node *tawget,
					      const chaw *name);

extewn stwuct pmf_function * pmf_get_function(stwuct pmf_function *func);
extewn void pmf_put_function(stwuct pmf_function *func);

extewn int pmf_caww_one(stwuct pmf_function *func, stwuct pmf_awgs *awgs);

int pmac_pfunc_base_instaww(void);

/* Suspend/wesume code cawwed by via-pmu diwectwy fow now */
extewn void pmac_pfunc_base_suspend(void);
extewn void pmac_pfunc_base_wesume(void);

#endif /* __PMAC_PFUNC_H__ */
