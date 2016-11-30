#This makefile makes all the main book code with CppUTest test harness

#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
COMPONENT_NAME = BookCode_CppUTest

CPPUTEST_HOME = ~/InstalledApplications/cpputest-master

#--- Inputs ----#
#CPPUTEST_HOME = CppUTest
CPP_PLATFORM = Gcc
PROJECT_HOME_DIR = .

SRC_DIRS = \
	src/HomeAutomation \
	src/util\
	src/LedDriver \
	src/dvr\
	src/io \
	src/MyOS \
	src/MyOS/posix \
	src/zune \
	src/systemSetup

TEST_SRC_DIRS = \
	.\
	mocks\
	mocks/io\
	tests/LedDriver\
	tests/stdio\
	cpputest-unit-tests

	
INCLUDE_DIRS =\
  .\
  $(CPPUTEST_HOME)/include\
  include/io\
  mocks\
  include/systemSetup\
  include/stm32f401re\
  include/LedDriver\
  include/MyOS\
  include/dvr\
  include/zune\

MOCKS_SRC_DIRS = \
	mocks\
	
CPPUTEST_WARNINGFLAGS = -Wall -Wswitch-default -Werror -DSTM32F401xE
#CPPUTEST_CFLAGS = -std=c89 
CPPUTEST_CFLAGS += -Wall -Wstrict-prototypes -pedantic
LD_LIBRARIES = -lpthread
	
  
include $(CPPUTEST_HOME)/build/MakefileWorker.mk

