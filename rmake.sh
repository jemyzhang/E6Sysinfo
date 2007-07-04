pushd screenlocker
rm -f *
wget ftp://10.230.132.227/Makefile
wget ftp://10.230.132.227/*.h
wget ftp://10.230.132.227/*.cpp
make
arm-linux-strip screenlocker
if [ -f screenlocker ];
then
wput -u ftp://10.230.132.227/dest/ screenlocker
wput -u ftp://10.230.132.227/dest/ screenlocker
fi
popd

