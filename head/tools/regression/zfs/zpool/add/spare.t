#!/bin/sh
# $FreeBSD: soc2013/dpl/head/tools/regression/zfs/zpool/add/spare.t 185072 2008-11-17 20:49:29Z pjd $

dir=`dirname $0`
. ${dir}/../../misc.sh

echo "1..31"

disks_create 6
names_create 1

expect_ok ${ZPOOL} create ${name0} ${disk0}
expect_ok ${ZPOOL} add ${name0} spare ${disk1}
exp=`(
  echo "  pool: ${name0}"
  echo " state: ONLINE"
  echo " scrub: none requested"
  echo "config:"
  echo "	NAME        STATE   READ WRITE CKSUM"
  echo "	${name0}    ONLINE     0     0     0"
  echo "	  ${disk0}  ONLINE     0     0     0"
  echo "	spares"
  echo "	  ${disk1}  AVAIL"
  echo "errors: No known data errors"
)`
expect "${exp}" ${ZPOOL} status ${name0}
expect_ok ${ZPOOL} destroy ${name0}
expect_fl ${ZPOOL} status -x ${name0}

expect_ok ${ZPOOL} create ${name0} mirror ${disk0} ${disk1}
expect_ok ${ZPOOL} add ${name0} spare ${disk2} ${disk3}
exp=`(
  echo "  pool: ${name0}"
  echo " state: ONLINE"
  echo " scrub: none requested"
  echo "config:"
  echo "	NAME          STATE   READ WRITE CKSUM"
  echo "	${name0}      ONLINE     0     0     0"
  echo "	  mirror      ONLINE     0     0     0"
  echo "	    ${disk0}  ONLINE     0     0     0"
  echo "	    ${disk1}  ONLINE     0     0     0"
  echo "	spares"
  echo "	  ${disk2}    AVAIL"
  echo "	  ${disk3}    AVAIL"
  echo "errors: No known data errors"
)`
expect "${exp}" ${ZPOOL} status ${name0}
expect_ok ${ZPOOL} destroy ${name0}
expect_fl ${ZPOOL} status -x ${name0}

expect_ok ${ZPOOL} create ${name0} raidz ${disk0} ${disk1} ${disk2}
expect_ok ${ZPOOL} add ${name0} spare ${disk3} ${disk4}
exp=`(
  echo "  pool: ${name0}"
  echo " state: ONLINE"
  echo " scrub: none requested"
  echo "config:"
  echo "	NAME          STATE   READ WRITE CKSUM"
  echo "	${name0}      ONLINE     0     0     0"
  echo "	  raidz1      ONLINE     0     0     0"
  echo "	    ${disk0}  ONLINE     0     0     0"
  echo "	    ${disk1}  ONLINE     0     0     0"
  echo "	    ${disk2}  ONLINE     0     0     0"
  echo "	spares"
  echo "	  ${disk3}    AVAIL"
  echo "	  ${disk4}    AVAIL"
  echo "errors: No known data errors"
)`
expect "${exp}" ${ZPOOL} status ${name0}
expect_ok ${ZPOOL} destroy ${name0}
expect_fl ${ZPOOL} status -x ${name0}

expect_ok ${ZPOOL} create ${name0} raidz2 ${disk0} ${disk1} ${disk2} ${disk3}
expect_ok ${ZPOOL} add ${name0} spare ${disk4} ${disk5}
exp=`(
  echo "  pool: ${name0}"
  echo " state: ONLINE"
  echo " scrub: none requested"
  echo "config:"
  echo "	NAME          STATE   READ WRITE CKSUM"
  echo "	${name0}      ONLINE     0     0     0"
  echo "	  raidz2      ONLINE     0     0     0"
  echo "	    ${disk0}  ONLINE     0     0     0"
  echo "	    ${disk1}  ONLINE     0     0     0"
  echo "	    ${disk2}  ONLINE     0     0     0"
  echo "	    ${disk3}  ONLINE     0     0     0"
  echo "	spares"
  echo "	  ${disk4}    AVAIL"
  echo "	  ${disk5}    AVAIL"
  echo "errors: No known data errors"
)`
expect "${exp}" ${ZPOOL} status ${name0}
expect_ok ${ZPOOL} destroy ${name0}
expect_fl ${ZPOOL} status -x ${name0}

expect_ok ${ZPOOL} create ${name0} ${disk0} spare ${disk1}
expect_ok ${ZPOOL} add ${name0} spare ${disk2} ${disk3}
exp=`(
  echo "  pool: ${name0}"
  echo " state: ONLINE"
  echo " scrub: none requested"
  echo "config:"
  echo "	NAME        STATE   READ WRITE CKSUM"
  echo "	${name0}    ONLINE     0     0     0"
  echo "	  ${disk0}  ONLINE     0     0     0"
  echo "	spares"
  echo "	  ${disk1}  AVAIL"
  echo "	  ${disk2}  AVAIL"
  echo "	  ${disk3}  AVAIL"
  echo "errors: No known data errors"
)`
expect "${exp}" ${ZPOOL} status ${name0}
expect_ok ${ZPOOL} destroy ${name0}
expect_fl ${ZPOOL} status -x ${name0}

expect_ok ${ZPOOL} create ${name0} ${disk0}
expect_ok ${ZPOOL} add ${name0} spare ${disk1} ${disk2}
expect_ok ${ZPOOL} add ${name0} spare ${disk3}
exp=`(
  echo "  pool: ${name0}"
  echo " state: ONLINE"
  echo " scrub: none requested"
  echo "config:"
  echo "	NAME        STATE   READ WRITE CKSUM"
  echo "	${name0}    ONLINE     0     0     0"
  echo "	  ${disk0}  ONLINE     0     0     0"
  echo "	spares"
  echo "	  ${disk1}  AVAIL"
  echo "	  ${disk2}  AVAIL"
  echo "	  ${disk3}  AVAIL"
  echo "errors: No known data errors"
)`
expect "${exp}" ${ZPOOL} status ${name0}
expect_ok ${ZPOOL} destroy ${name0}
expect_fl ${ZPOOL} status -x ${name0}

disks_destroy
