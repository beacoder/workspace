#!/bin/ksh

# remove valgrind 3.9
rpm -e --nodeps --allmatches valgrind-3.9.0-1.el5 valgrind-devel-3.9.0-1.el5

# install valgrind 3.8
rpm -ivh  /home/harolyao/valgrind-3.8.1/valgrind-3.8.1-1.el5*rpm /home/harolyao/valgrind-3.8.1/valgrind-devel-3.8.1-1.el5*rpm

# update valgrind to 3.9
/etc/cron.daily/yum.cron now