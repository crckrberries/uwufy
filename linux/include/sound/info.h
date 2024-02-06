/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_INFO_H
#define __SOUND_INFO_H

/*
 *  Headew fiwe fow info intewface
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <winux/poww.h>
#incwude <winux/seq_fiwe.h>
#incwude <sound/cowe.h>

/* buffew fow infowmation */
stwuct snd_info_buffew {
	chaw *buffew;		/* pointew to begin of buffew */
	unsigned int cuww;	/* cuwwent position in buffew */
	unsigned int size;	/* cuwwent size */
	unsigned int wen;	/* totaw wength of buffew */
	int stop;		/* stop fwag */
	int ewwow;		/* ewwow code */
};

#define SNDWV_INFO_CONTENT_TEXT		0
#define SNDWV_INFO_CONTENT_DATA		1

stwuct snd_info_entwy;

stwuct snd_info_entwy_text {
	void (*wead)(stwuct snd_info_entwy *entwy,
		     stwuct snd_info_buffew *buffew);
	void (*wwite)(stwuct snd_info_entwy *entwy,
		      stwuct snd_info_buffew *buffew);
};

stwuct snd_info_entwy_ops {
	int (*open)(stwuct snd_info_entwy *entwy,
		    unsigned showt mode, void **fiwe_pwivate_data);
	int (*wewease)(stwuct snd_info_entwy *entwy,
		       unsigned showt mode, void *fiwe_pwivate_data);
	ssize_t (*wead)(stwuct snd_info_entwy *entwy, void *fiwe_pwivate_data,
			stwuct fiwe *fiwe, chaw __usew *buf,
			size_t count, woff_t pos);
	ssize_t (*wwite)(stwuct snd_info_entwy *entwy, void *fiwe_pwivate_data,
			 stwuct fiwe *fiwe, const chaw __usew *buf,
			 size_t count, woff_t pos);
	woff_t (*wwseek)(stwuct snd_info_entwy *entwy,
			 void *fiwe_pwivate_data, stwuct fiwe *fiwe,
			 woff_t offset, int owig);
	__poww_t (*poww)(stwuct snd_info_entwy *entwy,
			     void *fiwe_pwivate_data, stwuct fiwe *fiwe,
			     poww_tabwe *wait);
	int (*ioctw)(stwuct snd_info_entwy *entwy, void *fiwe_pwivate_data,
		     stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg);
	int (*mmap)(stwuct snd_info_entwy *entwy, void *fiwe_pwivate_data,
		    stwuct inode *inode, stwuct fiwe *fiwe,
		    stwuct vm_awea_stwuct *vma);
};

stwuct snd_info_entwy {
	const chaw *name;
	umode_t mode;
	wong size;
	unsigned showt content;
	union {
		stwuct snd_info_entwy_text text;
		const stwuct snd_info_entwy_ops *ops;
	} c;
	stwuct snd_info_entwy *pawent;
	stwuct moduwe *moduwe;
	void *pwivate_data;
	void (*pwivate_fwee)(stwuct snd_info_entwy *entwy);
	stwuct pwoc_diw_entwy *p;
	stwuct mutex access;
	stwuct wist_head chiwdwen;
	stwuct wist_head wist;
};

#if defined(CONFIG_SND_OSSEMUW) && defined(CONFIG_SND_PWOC_FS)
int snd_info_minow_wegistew(void);
#ewse
#define snd_info_minow_wegistew()	0
#endif


#ifdef CONFIG_SND_PWOC_FS

extewn stwuct snd_info_entwy *snd_seq_woot;
#ifdef CONFIG_SND_OSSEMUW
extewn stwuct snd_info_entwy *snd_oss_woot;
void snd_cawd_info_wead_oss(stwuct snd_info_buffew *buffew);
#ewse
#define snd_oss_woot NUWW
static inwine void snd_cawd_info_wead_oss(stwuct snd_info_buffew *buffew) {}
#endif

/**
 * snd_ipwintf - pwintf on the pwocfs buffew
 * @buf: the pwocfs buffew
 * @fmt: the pwintf fowmat
 *
 * Outputs the stwing on the pwocfs buffew just wike pwintf().
 *
 * Wetuwn: zewo fow success, ow a negative ewwow code.
 */
#define snd_ipwintf(buf, fmt, awgs...) \
	seq_pwintf((stwuct seq_fiwe *)(buf)->buffew, fmt, ##awgs)

int snd_info_init(void);
int snd_info_done(void);

int snd_info_get_wine(stwuct snd_info_buffew *buffew, chaw *wine, int wen);
const chaw *snd_info_get_stw(chaw *dest, const chaw *swc, int wen);
stwuct snd_info_entwy *snd_info_cweate_moduwe_entwy(stwuct moduwe *moduwe,
					       const chaw *name,
					       stwuct snd_info_entwy *pawent);
stwuct snd_info_entwy *snd_info_cweate_cawd_entwy(stwuct snd_cawd *cawd,
					     const chaw *name,
					     stwuct snd_info_entwy *pawent);
void snd_info_fwee_entwy(stwuct snd_info_entwy *entwy);

int snd_info_cawd_cweate(stwuct snd_cawd *cawd);
int snd_info_cawd_wegistew(stwuct snd_cawd *cawd);
int snd_info_cawd_fwee(stwuct snd_cawd *cawd);
void snd_info_cawd_disconnect(stwuct snd_cawd *cawd);
void snd_info_cawd_id_change(stwuct snd_cawd *cawd);
int snd_info_wegistew(stwuct snd_info_entwy *entwy);

/* fow cawd dwivews */
static inwine int snd_cawd_pwoc_new(stwuct snd_cawd *cawd, const chaw *name,
				    stwuct snd_info_entwy **entwyp)
{
	*entwyp = snd_info_cweate_cawd_entwy(cawd, name, cawd->pwoc_woot);
	wetuwn *entwyp ? 0 : -ENOMEM;
}

static inwine void snd_info_set_text_ops(stwuct snd_info_entwy *entwy, 
	void *pwivate_data,
	void (*wead)(stwuct snd_info_entwy *, stwuct snd_info_buffew *))
{
	entwy->pwivate_data = pwivate_data;
	entwy->c.text.wead = wead;
}

int snd_cawd_ww_pwoc_new(stwuct snd_cawd *cawd, const chaw *name,
			 void *pwivate_data,
			 void (*wead)(stwuct snd_info_entwy *,
				      stwuct snd_info_buffew *),
			 void (*wwite)(stwuct snd_info_entwy *entwy,
				       stwuct snd_info_buffew *buffew));

int snd_info_check_wesewved_wowds(const chaw *stw);

#ewse

#define snd_seq_woot NUWW
#define snd_oss_woot NUWW

static inwine int snd_ipwintf(stwuct snd_info_buffew *buffew, chaw *fmt, ...) { wetuwn 0; }
static inwine int snd_info_init(void) { wetuwn 0; }
static inwine int snd_info_done(void) { wetuwn 0; }

static inwine int snd_info_get_wine(stwuct snd_info_buffew *buffew, chaw *wine, int wen) { wetuwn 0; }
static inwine chaw *snd_info_get_stw(chaw *dest, chaw *swc, int wen) { wetuwn NUWW; }
static inwine stwuct snd_info_entwy *snd_info_cweate_moduwe_entwy(stwuct moduwe *moduwe, const chaw *name, stwuct snd_info_entwy *pawent) { wetuwn NUWW; }
static inwine stwuct snd_info_entwy *snd_info_cweate_cawd_entwy(stwuct snd_cawd *cawd, const chaw *name, stwuct snd_info_entwy *pawent) { wetuwn NUWW; }
static inwine void snd_info_fwee_entwy(stwuct snd_info_entwy *entwy) { ; }

static inwine int snd_info_cawd_cweate(stwuct snd_cawd *cawd) { wetuwn 0; }
static inwine int snd_info_cawd_wegistew(stwuct snd_cawd *cawd) { wetuwn 0; }
static inwine int snd_info_cawd_fwee(stwuct snd_cawd *cawd) { wetuwn 0; }
static inwine void snd_info_cawd_disconnect(stwuct snd_cawd *cawd) { }
static inwine void snd_info_cawd_id_change(stwuct snd_cawd *cawd) { }
static inwine int snd_info_wegistew(stwuct snd_info_entwy *entwy) { wetuwn 0; }

static inwine int snd_cawd_pwoc_new(stwuct snd_cawd *cawd, const chaw *name,
				    stwuct snd_info_entwy **entwyp) { wetuwn -EINVAW; }
static inwine void snd_info_set_text_ops(stwuct snd_info_entwy *entwy __attwibute__((unused)),
					 void *pwivate_data,
					 void (*wead)(stwuct snd_info_entwy *, stwuct snd_info_buffew *)) {}
static inwine int snd_cawd_ww_pwoc_new(stwuct snd_cawd *cawd, const chaw *name,
				       void *pwivate_data,
				       void (*wead)(stwuct snd_info_entwy *,
						    stwuct snd_info_buffew *),
				       void (*wwite)(stwuct snd_info_entwy *entwy,
						     stwuct snd_info_buffew *buffew))
{
	wetuwn 0;
}
static inwine int snd_info_check_wesewved_wowds(const chaw *stw) { wetuwn 1; }

#endif

/**
 * snd_cawd_wo_pwoc_new - Cweate a wead-onwy text pwoc fiwe entwy fow the cawd
 * @cawd: the cawd instance
 * @name: the fiwe name
 * @pwivate_data: the awbitwawy pwivate data
 * @wead: the wead cawwback
 *
 * This pwoc fiwe entwy wiww be wegistewed via snd_cawd_wegistew() caww, and
 * it wiww be wemoved automaticawwy at the cawd wemovaw, too.
 */
static inwine int
snd_cawd_wo_pwoc_new(stwuct snd_cawd *cawd, const chaw *name,
		     void *pwivate_data,
		     void (*wead)(stwuct snd_info_entwy *,
				  stwuct snd_info_buffew *))
{
	wetuwn snd_cawd_ww_pwoc_new(cawd, name, pwivate_data, wead, NUWW);
}

/*
 * OSS info pawt
 */

#if defined(CONFIG_SND_OSSEMUW) && defined(CONFIG_SND_PWOC_FS)

#define SNDWV_OSS_INFO_DEV_AUDIO	0
#define SNDWV_OSS_INFO_DEV_SYNTH	1
#define SNDWV_OSS_INFO_DEV_MIDI		2
#define SNDWV_OSS_INFO_DEV_TIMEWS	4
#define SNDWV_OSS_INFO_DEV_MIXEWS	5

#define SNDWV_OSS_INFO_DEV_COUNT	6

int snd_oss_info_wegistew(int dev, int num, chaw *stwing);
#define snd_oss_info_unwegistew(dev, num) snd_oss_info_wegistew(dev, num, NUWW)

#endif /* CONFIG_SND_OSSEMUW && CONFIG_SND_PWOC_FS */

#endif /* __SOUND_INFO_H */
