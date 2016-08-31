#This makefile makes the examples from the first few chapters with Unity test harness

#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
COMPONENT_NAME = stm32f401re-template

#--- Inputs ----#
UNITY_HOME = ./unity-framework-src
CPP_PLATFORM = gcc
PROJECT_HOME_DIR = .
PROJECT_TEST_DIR = unity-unit-tests
UNITY_BUILD_HOME = $(UNITY_HOME)/extras/fixture/build

UNITY_CFLAGS += -DUNITY_OUTPUT_CHAR=UnityOutputCharSpy_OutputChar
UNITY_WARNINGFLAGS = -Wall -Werror -Wswitch-default
#UNITY_WARNINGFLAGS += -Wshadow 

SRC_DIRS = \
#	$(PROJECT_HOME_DIR)/src/LedDriver \
	$(PROJECT_HOME_DIR)/src/HomeAutomation

UNITY_OBJS_DIR = \
	$(PROJECT_HOME_DIR)/objs

TEST_SRC_DIRS = \
	$(PROJECT_TEST_DIR)\
	$(UNITY_HOME)/src\
    $(UNITY_HOME)/extras/fixture/src\
    $(UNITY_HOME)/extras/fixture/test\
	$(PROJECT_TEST_DIR)/FirstGroup\
#	$(UNITY_HOME)/unity\


MOCKS_SRC_DIRS = \
	$(PROJECT_TEST_DIR)/mocks\

INCLUDE_DIRS =\
  .\
  $(UNITY_HOME)/src\
  $(UNITY_HOME)/extras/fixture/src\
  $(UNITY_HOME)/extras/fixture/test\
  $(PROJECT_HOME_DIR)/include/util\
  $(PROJECT_HOME_DIR)/mocks\
  
include $(UNITY_BUILD_HOME)/MakefileWorker.mk

