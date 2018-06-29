/* Invoke open, but return either a desired file descriptor or -1.

   Copyright (C) 2005-2006, 2008-2011 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* Written by Paul Eggert.  */

#include <config.h>

#include "fd-reopen.h"

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

/* Open a file to a particular file descriptor.  This is like standard
   `open', except it always returns DESIRED_FD if successful.  */

int
fd_reopen (int desired_fd, char const *file, int flags, mode_t mode)
{
  /*
   open close 函数在哪里?
   open is a system call that is used to open a new file and obtain its file descriptor(http://codewiki.wikidot.com/c:system-calls:open)
   close 应该也是。
   他们是通过 fcntl.h 和 unistd.h 引入进来的
   TODO 怎么知道有哪些 system call 呢?
   既然是 system call, 为什么 lib 目录下还需要生成呢（还有 lib/fcntl.h）？ 学习 c 语言的时候都是只一句 #include <*> 就好了的
   通过 lib/fcntl.h 中的 if else 屏蔽不同系统下 system call 的差异
   TODO 他们具体是怎么屏蔽这种差异的呢？有待学习
   




   */
  int fd = open (file, flags, mode);

  if (fd == desired_fd || fd < 0)
    return fd;
  else
    {
      int fd2 = dup2 (fd, desired_fd);
      int saved_errno = errno;
      close (fd);
      errno = saved_errno;
      return fd2;
    }
}
