#! /bin/sh

LLDP_USER=_lldpd

mk_dir(){
	if [ ! -e /usr/local ]; then
        	mkdir /usr/local
        	mkdir /usr/local/var
        	mkdir /usr/local/var/run
	else
        	if [ ! -e /usr/local/var ]; then
                	mkdir /usr/local/var
                	mkdir /usr/local/var/run
        	else
                	if [ ! -e /usr/local/var/run ]; then
                        	mkdir /usr/local/var/run
                	fi
        	fi
	fi

	if [ ! -e /usr/local/var/run/lldpd.conf ]; then
		touch /usr/local/var/run/lldpd.conf
		chmod 644 /usr/local/var/run/lldpd.conf
	fi
}

add_lldp_user(){
	if [ -e /etc/passwd+ ]; then
		rm /etc/passwd+
	fi
	
	adduser _lldpd -D
}

close_daemon(){
	DAEMON_NAME=$@
    RESULT=`ps -a | grep "${DAEMON_NAME}" | grep -v lldp_control.sh | grep -v grep | awk '{print $1}'`
	echo ${RESULT}
	if [ ! -z "${RESULT}" ]; then
		  kill -15 ${RESULT}
	fi
}

case "$1" in
  mk)	
	mk_dir
	;;
  add_user)
	add_lldp_user
	;;
  close)
	shift
	close_daemon $@
	;;
  *)
	exit 1
	;;
esac

exit 0
