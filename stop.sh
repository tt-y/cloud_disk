#杀死cgi程序
kill -9 `ps aux | grep "upload_cgi" | grep -v grep | awk '{print $2}'`
#关闭nginx程序
sudo /usr/local/nginx/sbin/nginx -s stop

#kill -9 `ps aux | grep "cgi_bin/reg" |grep -v grep | awk '{print $2}'`
#kill -9 `ps aux | grep "cgi_bin/upload" |grep -v grep | awk '{print $2}'`
#kill -9 `ps aux | grep "cgi_bin/login" |grep -v grep | awk '{print $2}'
