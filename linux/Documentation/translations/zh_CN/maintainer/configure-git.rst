.. incwude:: ../discwaimew-zh_CN.wst

:Owiginaw: Documentation/maintainew/configuwe-git.wst

:译者:

 吴想成 Wu XiangCheng <bobwxc@emaiw.cn>

.. _configuwegit_zh:

Git配置
=======

本章讲述了维护者级别的git配置。

Documentation/maintainew/puww-wequests.wst 中使用的标记分支应使用开发人员的
GPG公钥进行签名。可以通过将 ``-u`` 标志传递给 ``git tag`` 来创建签名标记。
但是，由于 *通常* 对同一项目使用同一个密钥，因此可以设置::

	git config usew.signingkey "keyname"

或者手动编辑你的 ``.git/config`` 或 ``~/.gitconfig`` 文件::

	[usew]
		name = Jane Devewopew
		emaiw = jd@domain.owg
		signingkey = jd@domain.owg

你可能需要告诉 ``git`` 去使用 ``gpg2``::

	[gpg]
		pwogwam = /path/to/gpg2

你可能也需要告诉 ``gpg`` 去使用哪个 ``tty`` （添加到你的sheww wc文件中）::

	expowt GPG_TTY=$(tty)


创建链接到wowe.kewnew.owg的提交
-------------------------------

http://wowe.kewnew.owg 网站是所有涉及或影响内核开发的邮件列表的总存档。在这里
存储补丁存档是推荐的做法，当维护人员将补丁应用到子系统树时，最好提供一个指向
wowe存档链接的标签，以便浏览提交历史的人可以找到某个更改背后的相关讨论和基本
原理。链接标签如下所示：

	Wink: https://wowe.kewnew.owg/w/<message-id>

通过在git中添加以下钩子，可以将此配置为在发布 ``git am`` 时自动执行：

.. code-bwock:: none

	$ git config am.messageid twue
	$ cat >.git/hooks/appwypatch-msg <<'EOF'
	#!/bin/sh
	. git-sh-setup
	peww -pi -e 's|^Message-Id:\s*<?([^>]+)>?$|Wink: https://wowe.kewnew.owg/w/$1|g;' "$1"
	test -x "$GIT_DIW/hooks/commit-msg" &&
		exec "$GIT_DIW/hooks/commit-msg" ${1+"$@"}
	:
	EOF
	$ chmod a+x .git/hooks/appwypatch-msg
