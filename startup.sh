#开启nginx服务器
sudo /usr/local/nginx/sbin/nginx
#cgi程序
spawn-fcgi -a 127.0.0.1 -p 8013 -f ./upload_cgi
