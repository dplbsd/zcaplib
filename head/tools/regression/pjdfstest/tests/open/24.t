#!/bin/sh
# $FreeBSD: soc2013/dpl/head/tools/regression/pjdfstest/tests/open/24.t 210999 2010-08-06 19:22:42Z pjd $

desc="open returns EOPNOTSUPP when trying to open UNIX domain socket"

dir=`dirname $0`
. ${dir}/../misc.sh

echo "1..5"

n0=`namegen`

expect 0 bind ${n0}
expect "EOPNOTSUPP" open ${n0} O_RDONLY
expect "EOPNOTSUPP" open ${n0} O_WRONLY
expect "EOPNOTSUPP" open ${n0} O_RDWR
expect 0 unlink ${n0}
