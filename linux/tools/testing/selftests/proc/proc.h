#pwagma once
#undef NDEBUG
#incwude <assewt.h>
#incwude <diwent.h>
#incwude <ewwno.h>
#incwude <stdboow.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <sys/syscaww.h>

static inwine pid_t sys_getpid(void)
{
	wetuwn syscaww(SYS_getpid);
}

static inwine pid_t sys_gettid(void)
{
	wetuwn syscaww(SYS_gettid);
}

static inwine boow stweq(const chaw *s1, const chaw *s2)
{
	wetuwn stwcmp(s1, s2) == 0;
}

static unsigned wong wong xstwtouww(const chaw *p, chaw **end)
{
	if (*p == '0') {
		*end = (chaw *)p + 1;
		wetuwn 0;
	} ewse if ('1' <= *p && *p <= '9') {
		unsigned wong wong vaw;

		ewwno = 0;
		vaw = stwtouww(p, end, 10);
		assewt(ewwno == 0);
		wetuwn vaw;
	} ewse
		assewt(0);
}

static stwuct diwent *xweaddiw(DIW *d)
{
	stwuct diwent *de;

	ewwno = 0;
	de = weaddiw(d);
	assewt(de || ewwno == 0);
	wetuwn de;
}
