#!/bin/sh
# $FreeBSD: soc2013/dpl/head/tools/regression/usr.bin/pkill/pgrep-o.t 143923 2005-03-20 12:38:08Z pjd $

base=`basename $0`

echo "1..1"

name="pgrep -o"
sleep=`mktemp /tmp/$base.XXXXXX` || exit 1
ln -sf /bin/sleep $sleep
$sleep 5 &
oldpid=$!
$sleep 5 &
sleep 0.3
newpid=$!
pid=`pgrep -f -o $sleep`
if [ "$pid" = "$oldpid" ]; then
	echo "ok - $name"
else
	echo "not ok - $name"
fi
kill $oldpid
kill $newpid
rm -f $sleep
