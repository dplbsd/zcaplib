#!/bin/sh
# $FreeBSD: soc2013/dpl/head/tools/regression/usr.bin/pkill/pgrep-x.t 143923 2005-03-20 12:38:08Z pjd $

base=`basename $0`

echo "1..4"

name="pgrep -x"
sleep=`mktemp /tmp/$base.XXXXXX` || exit 1
ln -sf /bin/sleep $sleep
$sleep 5 &
sleep 0.3
pid=$!
if [ ! -z "`pgrep -x sleep | egrep '^'"$pid"'$'`" ]; then
	echo "ok 1 - $name"
else
	echo "not ok 1 - $name"
fi
if [ -z "`pgrep -x slee | egrep '^'"$pid"'$'`" ]; then
	echo "ok 2 - $name"
else
	echo "not ok 2 - $name"
fi
name="pgrep -x -f"
if [ ! -z "`pgrep -x -f ''"$sleep"' 5' | egrep '^'"$pid"'$'`" ]; then
	echo "ok 3 - $name"
else
	echo "not ok 3 - $name"
fi
if [ -z "`pgrep -x -f ''"$sleep"' ' | egrep '^'"$pid"'$'`" ]; then
	echo "ok 4 - $name"
else
	echo "not ok 4 - $name"
fi
kill $pid
rm -f $sleep
