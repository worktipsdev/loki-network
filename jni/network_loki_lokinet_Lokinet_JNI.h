/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class network_loki_lokinet_Lokinet_JNI */

#ifndef _Included_network_loki_lokinet_Lokinet_JNI
#define _Included_network_loki_lokinet_Lokinet_JNI
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     network_loki_lokinet_Lokinet_JNI
 * Method:    getABICompiledWith
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_network_loki_lokinet_Lokinet_1JNI_getABICompiledWith
  (JNIEnv *, jclass);

/*
 * Class:     network_loki_lokinet_Lokinet_JNI
 * Method:    startLokinet
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_network_loki_lokinet_Lokinet_1JNI_startLokinet
  (JNIEnv *, jclass, jstring);

/*
 * Class:     network_loki_lokinet_Lokinet_JNI
 * Method:    stopLokinet
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_network_loki_lokinet_Lokinet_1JNI_stopLokinet
  (JNIEnv *, jclass);

/*
 * Class:     network_loki_lokinet_Lokinet_JNI
 * Method:    onNetworkStateChanged
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_network_loki_lokinet_Lokinet_1JNI_onNetworkStateChanged
  (JNIEnv *, jclass, jboolean);

#ifdef __cplusplus
}
#endif
#endif
