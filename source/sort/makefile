#找到根目录
ROOTDIR=$(shell while true; do if [ -f rules.make ]; then pwd;exit; else cd ..;fi;done;)
APPDIR=$(shell while true; do if [ -d bin ]; then cd bin/ ; pwd;exit; else cd ..;fi;done;)
APP_TARGET=$(APPDIR)/sortwrk

PRECOMMAND=dos2unix ./gen_array_data.sh; chmod a+x ./gen_array_data.sh; ./gen_array_data.sh


#以上定义的变量，在inlcude 根目录下的编译规则之后，都会传递到 rules.make 中去
include $(ROOTDIR)/rules.make
