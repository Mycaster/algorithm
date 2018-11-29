#===========================================================================
#  common
#===========================================================================
CC := gcc

#===========================================================================
# target 定义一个空的最终目标变量
#===========================================================================
PROGRAM = 

#如果是生成的二进制程序，则最终的目标变量是 PROGRAM=$(APP_TARGET)
ifdef APP_TARGET
	# CFLAGS += -rdynamic
	CXXFLAGS += -rdynamic
	PROGRAM=$(APP_TARGET)
	CSRES := $(APP_TARGET)
	REPORTDIR := $(APP_TARGET)
endif

## Stable Section: usually no need to be changed. But you can add more.  
##==========================================================================  
SHELL   = /bin/sh  
EMPTY   =  
SPACE   = $(EMPTY) $(EMPTY)  

# 如果 PROGRAM 为空，则默认的输出结果为 a.out
ifeq ($(PROGRAM),)  
  CUR_PATH_NAMES = $(subst /,$(SPACE),$(subst $(SPACE),_,$(CURDIR)))  
  PROGRAM = $(word $(words $(CUR_PATH_NAMES)),$(CUR_PATH_NAMES))  
  ifeq ($(PROGRAM),)  
    PROGRAM = a.out  
  endif  
endif  

# 如果 SRCDIRS 为空则默认设置为当前目录
ifeq ($(SRCDIRS),)  
  SRCDIRS = . 
endif

#文件的后缀名
SRCEXTS:=.c .cpp
HDREXTS:=.h
#===========================================================================
# 1. $(foreach VAR,LIST,TEXT)
#	 foreach 函数执行时把"LIST"中使用空格分割的单词依次取出赋值给变量"VAR"，然后执行"TEXT"表达式

# 2. $(addprefix fixstring,string1 string2 ...)
#    addprefix 加前缀函数, $(addprefix src/,foo bar)返回值是 "src/foosrc/bar"

# 3. $(wildcard PATTERN...) 
#	 $(wildcard *.c) 可以获取工作目录下所有.c文件列表
# 
#===========================================================================
# 用于调试, 输出结果为 $(SRCDIRS)/*.c . $(SRCDIRS)/*.cpp
# $(warning $(addprefix $(SRCDIRS)/*,$(SRCEXTS)))

# 目标目录下所有的源文件的集合
SOURCES = $(foreach d,$(SRCDIRS),$(wildcard $(addprefix $(d)/*,$(SRCEXTS))))
# 目标目录下所有的头文件的集合
HEADERS = $(foreach d,$(SRCDIRS),$(wildcard $(addprefix $(d)/*,$(HDREXTS))))  
# 目标目录下所有的 .c 源文件的集合
SRC_CXX = $(filter-out %.c,$(SOURCES))  
# 目标目录下所有的 .o 文件的集合 (注意==> 这些只是文件名集合的变量, 实际上这些 .o 文件还没有生成)
OBJS    = $(addsuffix .o, $(basename $(SOURCES)))  
# 编译选项
CFLAGS = --std=gnu99 -g -Wall -Werror -Wshadow -m64 \
		-Wno-unused-const-variable -Wno-address
#定义编译的命令
## Define some useful variables.  
COMPILE.c   = $(CC)  $(CFLAGS)  $(INCFLAGS)  -c  
COMPILE.cxx = $(CXX) $(CXXFLAGS) $(INCFLAGS) -c  
LINK.c      = $(CC)  $(CFLAGS)  $(LDFLAGS)  
LINK.cxx    = $(CXX) $(CXXFLAGS) $(LDFLAGS)  
AR			= ar -cr
  
.PHONY: all objs tags ctags clean distclean help show  
  
# Delete the default suffixes  
.SUFFIXES:  
  
#make all 的时候，由于all 依赖于 precommand $(PROGRAM)  postcommand, 因此再依次去 make precommand make $(PROGRAM) make postcommand
all: precommand $(PROGRAM) postcommand
  
# Rules for generating object files (.o).  
#----------------------------------------  
objs:$(OBJS)  

#将所有的 .c 文件编译生成对应的 .o 文件, 这里生成之后 $(OBJS) 就可以用了, 也就是 objs 构建完成
%.o:%.c
	$(COMPILE.c) $< -o $@  

%.o:%.C
	$(COMPILE.cxx) $< -o $@  

%.o:%.cc
	$(COMPILE.cxx) $< -o $@  

%.o:%.cpp
	$(COMPILE.cxx) $< -o $@  

%.o:%.CPP
	$(COMPILE.cxx) $< -o $@  

%.o:%.c++
	$(COMPILE.cxx) $< -o $@  

%.o:%.cp
	$(COMPILE.cxx) $< -o $@  

%.o:%.cxx
	$(COMPILE.cxx) $< -o $@  

# Rules for generating the tags.  
#-------------------------------------  
tags: $(HEADERS) $(SOURCES)
	$(ETAGS) $(ETAGSFLAGS) $(HEADERS) $(SOURCES)  

ctags: $(HEADERS) $(SOURCES)
	$(CTAGS) $(CTAGSFLAGS) $(HEADERS) $(SOURCES)  

# Rules for generating the executable.  
#-------------------------------------  
#执行 $(PRECOMMAND) 来生成 precommand
precommand:
	$(PRECOMMAND)
postcommand:
	$(POSTCOMMAND)
cleancommand:
	$(CLEANCOMMAND)

#依赖 $(OBJS) 生成 $(PROGRAM), 根据最终是生成库文件还是生成二进制文件，来执行链接
$(PROGRAM):$(OBJS)
ifdef LIB_TARGET
	$(AR) $@ $(OBJS)
else
ifeq ($(wildcard *.cpp *.cc),)	# C program
	$(LINK.c)   $(OBJS) $(LIBFLAGS) -o $@
	@echo Type $@ to execute the program.
else                            # C++ program
	$(LINK.cxx) $(OBJS) $(LIBFLAGS) -o $@
	@echo Type $@ to execute the program.  
endif  
endif

clean: cleancommand
	$(RM) $(OBJS) $(PROGRAM) TAGS  

distclean: clean
  
# Show help.  
help:
	@echo 'Generic Makefile for C/C++ Programs (gcmakefile) version 0.5'
	@echo 'Copyright (C) 2007, 2008 whyglinux <whyglinux@hotmail.com>'
	@echo
	@echo 'Usage: make [TARGET]'
	@echo 'TARGETS:'
	@echo '  all       (=make) compile and link.'
	@echo '  NODEP=yes make without generating dependencies.'
	@echo '  objs      compile only (no linking).'
	@echo '  tags      create tags for Emacs editor.'
	@echo '  ctags     create ctags for VI editor.'
	@echo '  clean     clean objects and the executable file.'
#	@echo '  distclean clean objects, the executable and dependencies.'
	@echo '  show      show variables (for debug use only).'
	@echo '  help      print this message.'
	@echo
	@echo 'Report bugs to <whyglinux AT gmail DOT com>.'
	
# Show variables (for debug use only.)  
show:
	@echo 'PROGRAM     :' $(PROGRAM)
	@echo 'SRCDIRS     :' $(SRCDIRS)
	@echo 'HEADERS     :' $(HEADERS)
	@echo 'SOURCES     :' $(SOURCES)
	@echo 'SRC_CXX     :' $(SRC_CXX)
	@echo 'OBJS        :' $(OBJS)
	@echo 'COMPILE.c   :' $(COMPILE.c)
	@echo 'COMPILE.cxx :' $(COMPILE.cxx)
	@echo 'link.c      :' $(LINK.c)
	@echo 'link.cxx    :' $(LINK.cxx)
	
