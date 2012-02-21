LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

subdirs := $(addprefix $(LOCAL_PATH)/../../libs/,$(addsuffix /Android.mk, \
           cocos2dx \
           Box2D \
           CocosDenshion/android \
	))
subdirs += $(LOCAL_PATH)/../../Classes/Android.mk $(LOCAL_PATH)/helloworld/Android.mk

include $(subdirs)
