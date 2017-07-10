#pragma once

//此文件用于保存单例模式复用宏

#define  SINGLE_INSTANCE(T)\
static T* Instance(bool bRelease = false)\
{\
  static T* pApp = NULL;\
  if (!bRelease)\
  {\
    if (pApp == NULL)\
    {\
      pApp = new T();\
    }\
  }\
  else\
  {\
    if (pApp != NULL)\
    {\
      delete pApp;\
      pApp = NULL;\
    }\
  }\
    return pApp;\
}\

#define CREATE_SINGLE(T) T::Instance();
#define RELEASE_SINGLE(T) T::Instance(true);
#define GET_SINGLE(T) T::Instance();

