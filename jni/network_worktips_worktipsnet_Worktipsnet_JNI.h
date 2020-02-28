/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class network_worktips_worktipsnet_Worktipsnet_JNI */

#ifndef _Included_network_worktips_worktipsnet_Worktipsnet_JNI
#define _Included_network_worktips_worktipsnet_Worktipsnet_JNI
#ifdef __cplusplus
extern "C"
{
#endif
  /*
   * Class:     network_worktips_worktipsnet_Worktipsnet_JNI
   * Method:    getABICompiledWith
   * Signature: ()Ljava/lang/String;
   */
  JNIEXPORT jstring JNICALL
  Java_network_worktips_worktipsnet_Worktipsnet_1JNI_getABICompiledWith(JNIEnv *, jclass);

  /*
   * Class:     network_worktips_worktipsnet_Worktipsnet_JNI
   * Method:    startWorktipsnet
   * Signature: (Ljava/lang/String;)Ljava/lang/String;
   */
  JNIEXPORT jstring JNICALL
  Java_network_worktips_worktipsnet_Worktipsnet_1JNI_startWorktipsnet(JNIEnv *, jclass,
                                                      jstring);

  JNIEXPORT jstring JNICALL
  Java_network_worktips_worktipsnet_Worktipsnet_1JNI_getIfAddr(JNIEnv *, jclass);

  JNIEXPORT jint JNICALL
  Java_network_worktips_worktipsnet_Worktipsnet_1JNI_getIfRange(JNIEnv *, jclass);

  /*
   * Class:     network_worktips_worktipsnet_Worktipsnet_JNI
   * Method:    stopWorktipsnet
   * Signature: ()V
   */
  JNIEXPORT void JNICALL
  Java_network_worktips_worktipsnet_Worktipsnet_1JNI_stopWorktipsnet(JNIEnv *, jclass);

  JNIEXPORT void JNICALL
  Java_network_worktips_worktipsnet_Worktipsnet_1JNI_setVPNFileDescriptor(JNIEnv *, jclass,
                                                              jint, jint);

  /*
   * Class:     network_worktips_worktipsnet_Worktipsnet_JNI
   * Method:    onNetworkStateChanged
   * Signature: (Z)V
   */
  JNIEXPORT void JNICALL
  Java_network_worktips_worktipsnet_Worktipsnet_1JNI_onNetworkStateChanged(JNIEnv *, jclass,
                                                               jboolean);

#ifdef __cplusplus
}
#endif
#endif