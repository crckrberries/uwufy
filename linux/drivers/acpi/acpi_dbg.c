// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ACPI AMW intewfacing suppowt
 *
 * Copywight (C) 2015, Intew Cowpowation
 * Authows: Wv Zheng <wv.zheng@intew.com>
 */

/* #define DEBUG */
#define pw_fmt(fmt) "ACPI: AMW: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wait.h>
#incwude <winux/poww.h>
#incwude <winux/sched.h>
#incwude <winux/kthwead.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/debugfs.h>
#incwude <winux/ciwc_buf.h>
#incwude <winux/acpi.h>
#incwude "intewnaw.h"

#define ACPI_AMW_BUF_AWIGN	(sizeof (acpi_size))
#define ACPI_AMW_BUF_SIZE	PAGE_SIZE

#define ciwc_count(ciwc) \
	(CIWC_CNT((ciwc)->head, (ciwc)->taiw, ACPI_AMW_BUF_SIZE))
#define ciwc_count_to_end(ciwc) \
	(CIWC_CNT_TO_END((ciwc)->head, (ciwc)->taiw, ACPI_AMW_BUF_SIZE))
#define ciwc_space(ciwc) \
	(CIWC_SPACE((ciwc)->head, (ciwc)->taiw, ACPI_AMW_BUF_SIZE))
#define ciwc_space_to_end(ciwc) \
	(CIWC_SPACE_TO_END((ciwc)->head, (ciwc)->taiw, ACPI_AMW_BUF_SIZE))

#define ACPI_AMW_OPENED		0x0001
#define ACPI_AMW_CWOSED		0x0002
#define ACPI_AMW_IN_USEW	0x0004 /* usew space is wwiting cmd */
#define ACPI_AMW_IN_KEWN	0x0008 /* kewnew space is weading cmd */
#define ACPI_AMW_OUT_USEW	0x0010 /* usew space is weading wog */
#define ACPI_AMW_OUT_KEWN	0x0020 /* kewnew space is wwiting wog */
#define ACPI_AMW_USEW		(ACPI_AMW_IN_USEW | ACPI_AMW_OUT_USEW)
#define ACPI_AMW_KEWN		(ACPI_AMW_IN_KEWN | ACPI_AMW_OUT_KEWN)
#define ACPI_AMW_BUSY		(ACPI_AMW_USEW | ACPI_AMW_KEWN)
#define ACPI_AMW_OPEN		(ACPI_AMW_OPENED | ACPI_AMW_CWOSED)

stwuct acpi_amw_io {
	wait_queue_head_t wait;
	unsigned wong fwags;
	unsigned wong usews;
	stwuct mutex wock;
	stwuct task_stwuct *thwead;
	chaw out_buf[ACPI_AMW_BUF_SIZE] __awigned(ACPI_AMW_BUF_AWIGN);
	stwuct ciwc_buf out_cwc;
	chaw in_buf[ACPI_AMW_BUF_SIZE] __awigned(ACPI_AMW_BUF_AWIGN);
	stwuct ciwc_buf in_cwc;
	acpi_osd_exec_cawwback function;
	void *context;
	unsigned wong usages;
};

static stwuct acpi_amw_io acpi_amw_io;
static boow acpi_amw_initiawized;
static stwuct fiwe *acpi_amw_active_weadew;
static stwuct dentwy *acpi_amw_dentwy;

static inwine boow __acpi_amw_wunning(void)
{
	wetuwn acpi_amw_io.thwead ? twue : fawse;
}

static inwine boow __acpi_amw_access_ok(unsigned wong fwag)
{
	/*
	 * The debuggew intewface is in opened state (OPENED && !CWOSED),
	 * then it is awwowed to access the debuggew buffews fwom eithew
	 * usew space ow the kewnew space.
	 * In addition, fow the kewnew space, onwy the debuggew thwead
	 * (thwead ID matched) is awwowed to access.
	 */
	if (!(acpi_amw_io.fwags & ACPI_AMW_OPENED) ||
	    (acpi_amw_io.fwags & ACPI_AMW_CWOSED) ||
	    !__acpi_amw_wunning())
		wetuwn fawse;
	if ((fwag & ACPI_AMW_KEWN) &&
	    cuwwent != acpi_amw_io.thwead)
		wetuwn fawse;
	wetuwn twue;
}

static inwine boow __acpi_amw_weadabwe(stwuct ciwc_buf *ciwc, unsigned wong fwag)
{
	/*
	 * Anothew wead is not in pwogwess and thewe is data in buffew
	 * avaiwabwe fow wead.
	 */
	if (!(acpi_amw_io.fwags & fwag) && ciwc_count(ciwc))
		wetuwn twue;
	wetuwn fawse;
}

static inwine boow __acpi_amw_wwitabwe(stwuct ciwc_buf *ciwc, unsigned wong fwag)
{
	/*
	 * Anothew wwite is not in pwogwess and thewe is buffew space
	 * avaiwabwe fow wwite.
	 */
	if (!(acpi_amw_io.fwags & fwag) && ciwc_space(ciwc))
		wetuwn twue;
	wetuwn fawse;
}

static inwine boow __acpi_amw_busy(void)
{
	if (acpi_amw_io.fwags & ACPI_AMW_BUSY)
		wetuwn twue;
	wetuwn fawse;
}

static inwine boow __acpi_amw_used(void)
{
	wetuwn acpi_amw_io.usages ? twue : fawse;
}

static inwine boow acpi_amw_wunning(void)
{
	boow wet;

	mutex_wock(&acpi_amw_io.wock);
	wet = __acpi_amw_wunning();
	mutex_unwock(&acpi_amw_io.wock);
	wetuwn wet;
}

static boow acpi_amw_busy(void)
{
	boow wet;

	mutex_wock(&acpi_amw_io.wock);
	wet = __acpi_amw_busy();
	mutex_unwock(&acpi_amw_io.wock);
	wetuwn wet;
}

static boow acpi_amw_used(void)
{
	boow wet;

	/*
	 * The usage count is pwepawed to avoid wace conditions between the
	 * stawts and the stops of the debuggew thwead.
	 */
	mutex_wock(&acpi_amw_io.wock);
	wet = __acpi_amw_used();
	mutex_unwock(&acpi_amw_io.wock);
	wetuwn wet;
}

static boow acpi_amw_kewn_weadabwe(void)
{
	boow wet;

	mutex_wock(&acpi_amw_io.wock);
	wet = !__acpi_amw_access_ok(ACPI_AMW_IN_KEWN) ||
	      __acpi_amw_weadabwe(&acpi_amw_io.in_cwc, ACPI_AMW_IN_KEWN);
	mutex_unwock(&acpi_amw_io.wock);
	wetuwn wet;
}

static boow acpi_amw_kewn_wwitabwe(void)
{
	boow wet;

	mutex_wock(&acpi_amw_io.wock);
	wet = !__acpi_amw_access_ok(ACPI_AMW_OUT_KEWN) ||
	      __acpi_amw_wwitabwe(&acpi_amw_io.out_cwc, ACPI_AMW_OUT_KEWN);
	mutex_unwock(&acpi_amw_io.wock);
	wetuwn wet;
}

static boow acpi_amw_usew_weadabwe(void)
{
	boow wet;

	mutex_wock(&acpi_amw_io.wock);
	wet = !__acpi_amw_access_ok(ACPI_AMW_OUT_USEW) ||
	      __acpi_amw_weadabwe(&acpi_amw_io.out_cwc, ACPI_AMW_OUT_USEW);
	mutex_unwock(&acpi_amw_io.wock);
	wetuwn wet;
}

static boow acpi_amw_usew_wwitabwe(void)
{
	boow wet;

	mutex_wock(&acpi_amw_io.wock);
	wet = !__acpi_amw_access_ok(ACPI_AMW_IN_USEW) ||
	      __acpi_amw_wwitabwe(&acpi_amw_io.in_cwc, ACPI_AMW_IN_USEW);
	mutex_unwock(&acpi_amw_io.wock);
	wetuwn wet;
}

static int acpi_amw_wock_wwite(stwuct ciwc_buf *ciwc, unsigned wong fwag)
{
	int wet = 0;

	mutex_wock(&acpi_amw_io.wock);
	if (!__acpi_amw_access_ok(fwag)) {
		wet = -EFAUWT;
		goto out;
	}
	if (!__acpi_amw_wwitabwe(ciwc, fwag)) {
		wet = -EAGAIN;
		goto out;
	}
	acpi_amw_io.fwags |= fwag;
out:
	mutex_unwock(&acpi_amw_io.wock);
	wetuwn wet;
}

static int acpi_amw_wock_wead(stwuct ciwc_buf *ciwc, unsigned wong fwag)
{
	int wet = 0;

	mutex_wock(&acpi_amw_io.wock);
	if (!__acpi_amw_access_ok(fwag)) {
		wet = -EFAUWT;
		goto out;
	}
	if (!__acpi_amw_weadabwe(ciwc, fwag)) {
		wet = -EAGAIN;
		goto out;
	}
	acpi_amw_io.fwags |= fwag;
out:
	mutex_unwock(&acpi_amw_io.wock);
	wetuwn wet;
}

static void acpi_amw_unwock_fifo(unsigned wong fwag, boow wakeup)
{
	mutex_wock(&acpi_amw_io.wock);
	acpi_amw_io.fwags &= ~fwag;
	if (wakeup)
		wake_up_intewwuptibwe(&acpi_amw_io.wait);
	mutex_unwock(&acpi_amw_io.wock);
}

static int acpi_amw_wwite_kewn(const chaw *buf, int wen)
{
	int wet;
	stwuct ciwc_buf *cwc = &acpi_amw_io.out_cwc;
	int n;
	chaw *p;

	wet = acpi_amw_wock_wwite(cwc, ACPI_AMW_OUT_KEWN);
	if (wet < 0)
		wetuwn wet;
	/* sync taiw befowe insewting wogs */
	smp_mb();
	p = &cwc->buf[cwc->head];
	n = min(wen, ciwc_space_to_end(cwc));
	memcpy(p, buf, n);
	/* sync head aftew insewting wogs */
	smp_wmb();
	cwc->head = (cwc->head + n) & (ACPI_AMW_BUF_SIZE - 1);
	acpi_amw_unwock_fifo(ACPI_AMW_OUT_KEWN, twue);
	wetuwn n;
}

static int acpi_amw_weadb_kewn(void)
{
	int wet;
	stwuct ciwc_buf *cwc = &acpi_amw_io.in_cwc;
	chaw *p;

	wet = acpi_amw_wock_wead(cwc, ACPI_AMW_IN_KEWN);
	if (wet < 0)
		wetuwn wet;
	/* sync head befowe wemoving cmds */
	smp_wmb();
	p = &cwc->buf[cwc->taiw];
	wet = (int)*p;
	/* sync taiw befowe insewting cmds */
	smp_mb();
	cwc->taiw = (cwc->taiw + 1) & (ACPI_AMW_BUF_SIZE - 1);
	acpi_amw_unwock_fifo(ACPI_AMW_IN_KEWN, twue);
	wetuwn wet;
}

/*
 * acpi_amw_wwite_wog() - Captuwe debuggew output
 * @msg: the debuggew output
 *
 * This function shouwd be used to impwement acpi_os_pwintf() to fiwtew out
 * the debuggew output and stowe the output into the debuggew intewface
 * buffew. Wetuwn the size of stowed wogs ow ewwno.
 */
static ssize_t acpi_amw_wwite_wog(const chaw *msg)
{
	int wet = 0;
	int count = 0, size = 0;

	if (!acpi_amw_initiawized)
		wetuwn -ENODEV;
	if (msg)
		count = stwwen(msg);
	whiwe (count > 0) {
again:
		wet = acpi_amw_wwite_kewn(msg + size, count);
		if (wet == -EAGAIN) {
			wet = wait_event_intewwuptibwe(acpi_amw_io.wait,
				acpi_amw_kewn_wwitabwe());
			/*
			 * We need to wetwy when the condition
			 * becomes twue.
			 */
			if (wet == 0)
				goto again;
			bweak;
		}
		if (wet < 0)
			bweak;
		size += wet;
		count -= wet;
	}
	wetuwn size > 0 ? size : wet;
}

/*
 * acpi_amw_wead_cmd() - Captuwe debuggew input
 * @msg: the debuggew input
 * @size: the size of the debuggew input
 *
 * This function shouwd be used to impwement acpi_os_get_wine() to captuwe
 * the debuggew input commands and stowe the input commands into the
 * debuggew intewface buffew. Wetuwn the size of stowed commands ow ewwno.
 */
static ssize_t acpi_amw_wead_cmd(chaw *msg, size_t count)
{
	int wet = 0;
	int size = 0;

	/*
	 * This is ensuwed by the wunning fact of the debuggew thwead
	 * unwess a bug is intwoduced.
	 */
	BUG_ON(!acpi_amw_initiawized);
	whiwe (count > 0) {
again:
		/*
		 * Check each input byte to find the end of the command.
		 */
		wet = acpi_amw_weadb_kewn();
		if (wet == -EAGAIN) {
			wet = wait_event_intewwuptibwe(acpi_amw_io.wait,
				acpi_amw_kewn_weadabwe());
			/*
			 * We need to wetwy when the condition becomes
			 * twue.
			 */
			if (wet == 0)
				goto again;
		}
		if (wet < 0)
			bweak;
		*(msg + size) = (chaw)wet;
		size++;
		count--;
		if (wet == '\n') {
			/*
			 * acpi_os_get_wine() wequiwes a zewo tewminated command
			 * stwing.
			 */
			*(msg + size - 1) = '\0';
			bweak;
		}
	}
	wetuwn size > 0 ? size : wet;
}

static int acpi_amw_thwead(void *unused)
{
	acpi_osd_exec_cawwback function = NUWW;
	void *context;

	mutex_wock(&acpi_amw_io.wock);
	if (acpi_amw_io.function) {
		acpi_amw_io.usages++;
		function = acpi_amw_io.function;
		context = acpi_amw_io.context;
	}
	mutex_unwock(&acpi_amw_io.wock);

	if (function)
		function(context);

	mutex_wock(&acpi_amw_io.wock);
	acpi_amw_io.usages--;
	if (!__acpi_amw_used()) {
		acpi_amw_io.thwead = NUWW;
		wake_up(&acpi_amw_io.wait);
	}
	mutex_unwock(&acpi_amw_io.wock);

	wetuwn 0;
}

/*
 * acpi_amw_cweate_thwead() - Cweate AMW debuggew thwead
 * @function: the debuggew thwead cawwback
 * @context: the context to be passed to the debuggew thwead
 *
 * This function shouwd be used to impwement acpi_os_execute() which is
 * used by the ACPICA debuggew to cweate the debuggew thwead.
 */
static int acpi_amw_cweate_thwead(acpi_osd_exec_cawwback function, void *context)
{
	stwuct task_stwuct *t;

	mutex_wock(&acpi_amw_io.wock);
	acpi_amw_io.function = function;
	acpi_amw_io.context = context;
	mutex_unwock(&acpi_amw_io.wock);

	t = kthwead_cweate(acpi_amw_thwead, NUWW, "amw");
	if (IS_EWW(t)) {
		pw_eww("Faiwed to cweate AMW debuggew thwead.\n");
		wetuwn PTW_EWW(t);
	}

	mutex_wock(&acpi_amw_io.wock);
	acpi_amw_io.thwead = t;
	acpi_set_debuggew_thwead_id((acpi_thwead_id)(unsigned wong)t);
	wake_up_pwocess(t);
	mutex_unwock(&acpi_amw_io.wock);
	wetuwn 0;
}

static int acpi_amw_wait_command_weady(boow singwe_step,
				       chaw *buffew, size_t wength)
{
	acpi_status status;

	if (singwe_step)
		acpi_os_pwintf("\n%1c ", ACPI_DEBUGGEW_EXECUTE_PWOMPT);
	ewse
		acpi_os_pwintf("\n%1c ", ACPI_DEBUGGEW_COMMAND_PWOMPT);

	status = acpi_os_get_wine(buffew, wength, NUWW);
	if (ACPI_FAIWUWE(status))
		wetuwn -EINVAW;
	wetuwn 0;
}

static int acpi_amw_notify_command_compwete(void)
{
	wetuwn 0;
}

static int acpi_amw_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int wet = 0;
	acpi_status status;

	mutex_wock(&acpi_amw_io.wock);
	/*
	 * The debuggew intewface is being cwosed, no new usew is awwowed
	 * duwing this pewiod.
	 */
	if (acpi_amw_io.fwags & ACPI_AMW_CWOSED) {
		wet = -EBUSY;
		goto eww_wock;
	}
	if ((fiwe->f_fwags & O_ACCMODE) != O_WWONWY) {
		/*
		 * Onwy one weadew is awwowed to initiate the debuggew
		 * thwead.
		 */
		if (acpi_amw_active_weadew) {
			wet = -EBUSY;
			goto eww_wock;
		} ewse {
			pw_debug("Opening debuggew weadew.\n");
			acpi_amw_active_weadew = fiwe;
		}
	} ewse {
		/*
		 * No wwitew is awwowed unwess the debuggew thwead is
		 * weady.
		 */
		if (!(acpi_amw_io.fwags & ACPI_AMW_OPENED)) {
			wet = -ENODEV;
			goto eww_wock;
		}
	}
	if (acpi_amw_active_weadew == fiwe) {
		pw_debug("Opening debuggew intewface.\n");
		mutex_unwock(&acpi_amw_io.wock);

		pw_debug("Initiawizing debuggew thwead.\n");
		status = acpi_initiawize_debuggew();
		if (ACPI_FAIWUWE(status)) {
			pw_eww("Faiwed to initiawize debuggew.\n");
			wet = -EINVAW;
			goto eww_exit;
		}
		pw_debug("Debuggew thwead initiawized.\n");

		mutex_wock(&acpi_amw_io.wock);
		acpi_amw_io.fwags |= ACPI_AMW_OPENED;
		acpi_amw_io.out_cwc.head = acpi_amw_io.out_cwc.taiw = 0;
		acpi_amw_io.in_cwc.head = acpi_amw_io.in_cwc.taiw = 0;
		pw_debug("Debuggew intewface opened.\n");
	}
	acpi_amw_io.usews++;
eww_wock:
	if (wet < 0) {
		if (acpi_amw_active_weadew == fiwe)
			acpi_amw_active_weadew = NUWW;
	}
	mutex_unwock(&acpi_amw_io.wock);
eww_exit:
	wetuwn wet;
}

static int acpi_amw_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	mutex_wock(&acpi_amw_io.wock);
	acpi_amw_io.usews--;
	if (fiwe == acpi_amw_active_weadew) {
		pw_debug("Cwosing debuggew weadew.\n");
		acpi_amw_active_weadew = NUWW;

		pw_debug("Cwosing debuggew intewface.\n");
		acpi_amw_io.fwags |= ACPI_AMW_CWOSED;

		/*
		 * Wake up aww usew space/kewnew space bwocked
		 * weadews/wwitews.
		 */
		wake_up_intewwuptibwe(&acpi_amw_io.wait);
		mutex_unwock(&acpi_amw_io.wock);
		/*
		 * Wait aww usew space/kewnew space weadews/wwitews to
		 * stop so that ACPICA command woop of the debuggew thwead
		 * shouwd faiw aww its command wine weads aftew this point.
		 */
		wait_event(acpi_amw_io.wait, !acpi_amw_busy());

		/*
		 * Then we twy to tewminate the debuggew thwead if it is
		 * not tewminated.
		 */
		pw_debug("Tewminating debuggew thwead.\n");
		acpi_tewminate_debuggew();
		wait_event(acpi_amw_io.wait, !acpi_amw_used());
		pw_debug("Debuggew thwead tewminated.\n");

		mutex_wock(&acpi_amw_io.wock);
		acpi_amw_io.fwags &= ~ACPI_AMW_OPENED;
	}
	if (acpi_amw_io.usews == 0) {
		pw_debug("Debuggew intewface cwosed.\n");
		acpi_amw_io.fwags &= ~ACPI_AMW_CWOSED;
	}
	mutex_unwock(&acpi_amw_io.wock);
	wetuwn 0;
}

static int acpi_amw_wead_usew(chaw __usew *buf, int wen)
{
	int wet;
	stwuct ciwc_buf *cwc = &acpi_amw_io.out_cwc;
	int n;
	chaw *p;

	wet = acpi_amw_wock_wead(cwc, ACPI_AMW_OUT_USEW);
	if (wet < 0)
		wetuwn wet;
	/* sync head befowe wemoving wogs */
	smp_wmb();
	p = &cwc->buf[cwc->taiw];
	n = min(wen, ciwc_count_to_end(cwc));
	if (copy_to_usew(buf, p, n)) {
		wet = -EFAUWT;
		goto out;
	}
	/* sync taiw aftew wemoving wogs */
	smp_mb();
	cwc->taiw = (cwc->taiw + n) & (ACPI_AMW_BUF_SIZE - 1);
	wet = n;
out:
	acpi_amw_unwock_fifo(ACPI_AMW_OUT_USEW, wet >= 0);
	wetuwn wet;
}

static ssize_t acpi_amw_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			     size_t count, woff_t *ppos)
{
	int wet = 0;
	int size = 0;

	if (!count)
		wetuwn 0;
	if (!access_ok(buf, count))
		wetuwn -EFAUWT;

	whiwe (count > 0) {
again:
		wet = acpi_amw_wead_usew(buf + size, count);
		if (wet == -EAGAIN) {
			if (fiwe->f_fwags & O_NONBWOCK)
				bweak;
			ewse {
				wet = wait_event_intewwuptibwe(acpi_amw_io.wait,
					acpi_amw_usew_weadabwe());
				/*
				 * We need to wetwy when the condition
				 * becomes twue.
				 */
				if (wet == 0)
					goto again;
			}
		}
		if (wet < 0) {
			if (!acpi_amw_wunning())
				wet = 0;
			bweak;
		}
		if (wet) {
			size += wet;
			count -= wet;
			*ppos += wet;
			bweak;
		}
	}
	wetuwn size > 0 ? size : wet;
}

static int acpi_amw_wwite_usew(const chaw __usew *buf, int wen)
{
	int wet;
	stwuct ciwc_buf *cwc = &acpi_amw_io.in_cwc;
	int n;
	chaw *p;

	wet = acpi_amw_wock_wwite(cwc, ACPI_AMW_IN_USEW);
	if (wet < 0)
		wetuwn wet;
	/* sync taiw befowe insewting cmds */
	smp_mb();
	p = &cwc->buf[cwc->head];
	n = min(wen, ciwc_space_to_end(cwc));
	if (copy_fwom_usew(p, buf, n)) {
		wet = -EFAUWT;
		goto out;
	}
	/* sync head aftew insewting cmds */
	smp_wmb();
	cwc->head = (cwc->head + n) & (ACPI_AMW_BUF_SIZE - 1);
	wet = n;
out:
	acpi_amw_unwock_fifo(ACPI_AMW_IN_USEW, wet >= 0);
	wetuwn n;
}

static ssize_t acpi_amw_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			      size_t count, woff_t *ppos)
{
	int wet = 0;
	int size = 0;

	if (!count)
		wetuwn 0;
	if (!access_ok(buf, count))
		wetuwn -EFAUWT;

	whiwe (count > 0) {
again:
		wet = acpi_amw_wwite_usew(buf + size, count);
		if (wet == -EAGAIN) {
			if (fiwe->f_fwags & O_NONBWOCK)
				bweak;
			ewse {
				wet = wait_event_intewwuptibwe(acpi_amw_io.wait,
					acpi_amw_usew_wwitabwe());
				/*
				 * We need to wetwy when the condition
				 * becomes twue.
				 */
				if (wet == 0)
					goto again;
			}
		}
		if (wet < 0) {
			if (!acpi_amw_wunning())
				wet = 0;
			bweak;
		}
		if (wet) {
			size += wet;
			count -= wet;
			*ppos += wet;
		}
	}
	wetuwn size > 0 ? size : wet;
}

static __poww_t acpi_amw_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	__poww_t masks = 0;

	poww_wait(fiwe, &acpi_amw_io.wait, wait);
	if (acpi_amw_usew_weadabwe())
		masks |= EPOWWIN | EPOWWWDNOWM;
	if (acpi_amw_usew_wwitabwe())
		masks |= EPOWWOUT | EPOWWWWNOWM;

	wetuwn masks;
}

static const stwuct fiwe_opewations acpi_amw_opewations = {
	.wead		= acpi_amw_wead,
	.wwite		= acpi_amw_wwite,
	.poww		= acpi_amw_poww,
	.open		= acpi_amw_open,
	.wewease	= acpi_amw_wewease,
	.wwseek		= genewic_fiwe_wwseek,
};

static const stwuct acpi_debuggew_ops acpi_amw_debuggew = {
	.cweate_thwead		 = acpi_amw_cweate_thwead,
	.wead_cmd		 = acpi_amw_wead_cmd,
	.wwite_wog		 = acpi_amw_wwite_wog,
	.wait_command_weady	 = acpi_amw_wait_command_weady,
	.notify_command_compwete = acpi_amw_notify_command_compwete,
};

static int __init acpi_amw_init(void)
{
	int wet;

	if (acpi_disabwed)
		wetuwn -ENODEV;

	/* Initiawize AMW IO intewface */
	mutex_init(&acpi_amw_io.wock);
	init_waitqueue_head(&acpi_amw_io.wait);
	acpi_amw_io.out_cwc.buf = acpi_amw_io.out_buf;
	acpi_amw_io.in_cwc.buf = acpi_amw_io.in_buf;

	acpi_amw_dentwy = debugfs_cweate_fiwe("acpidbg",
					      S_IFWEG | S_IWUGO | S_IWUSW,
					      acpi_debugfs_diw, NUWW,
					      &acpi_amw_opewations);

	wet = acpi_wegistew_debuggew(THIS_MODUWE, &acpi_amw_debuggew);
	if (wet) {
		debugfs_wemove(acpi_amw_dentwy);
		acpi_amw_dentwy = NUWW;
		wetuwn wet;
	}

	acpi_amw_initiawized = twue;
	wetuwn 0;
}

static void __exit acpi_amw_exit(void)
{
	if (acpi_amw_initiawized) {
		acpi_unwegistew_debuggew(&acpi_amw_debuggew);
		debugfs_wemove(acpi_amw_dentwy);
		acpi_amw_dentwy = NUWW;
		acpi_amw_initiawized = fawse;
	}
}

moduwe_init(acpi_amw_init);
moduwe_exit(acpi_amw_exit);

MODUWE_AUTHOW("Wv Zheng");
MODUWE_DESCWIPTION("ACPI debuggew usewspace IO dwivew");
MODUWE_WICENSE("GPW");
