LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := game

LOCAL_SRC_FILES := main.cpp \
../../../Classes/AppDelegate.cpp \
../../../Classes/MyContactListener.cpp \
../../../Classes/GameOverScene.cpp \
../../../Classes/HelloWorldScene.cpp \
../../../Classes/TitleLayer.cpp \
../../../Classes/Options.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../libs/cocos2dx \
                    $(LOCAL_PATH)/../../../libs/cocos2dx/platform \
                    $(LOCAL_PATH)/../../../libs/cocos2dx/include \
                    $(LOCAL_PATH)/../../../libs/CocosDenshion/include \
                    $(LOCAL_PATH)/../../../libs/ \
                    $(LOCAL_PATH)/../../../libs/Box2D \
                    $(LOCAL_PATH)/../../../Classes 

LOCAL_LDLIBS := -L$(call host-path, $(LOCAL_PATH)/../../libs/$(TARGET_ARCH_ABI)) \
                -lcocos2d -llog -lbox2d -lGLESv1_CM -lcocosdenshion
            
include $(BUILD_SHARED_LIBRARY)
