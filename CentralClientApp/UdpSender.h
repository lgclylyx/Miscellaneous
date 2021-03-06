/*
 * UdpSender.h
 *
 *  Created on: Jun 7, 2016
 *      Author: ql
 */

#ifndef UDPSENDER_H_
#define UDPSENDER_H_

#include "CentralDefine.h"

#define TCP_LIS_PORT 62533
#ifndef _CENTRAL_HOST_
#define UDP_RECV_PORT 62536
#define UDP_SEND_PORT 62535
#else
#define UDP_RECV_PORT 62535
#define UDP_SEND_PORT 62536
#endif

typedef struct tagSendCmdHdr{
	CMDHDR cmdHdr;
	long timeDlay;
}SENDCMDHDR,*pSENDCMDHDR;

#include <cctype>
#include <sys/types.h>
#include <deque>
#include <pthread.h>
#include <arpa/inet.h>
#include <unistd.h>

class UdpSender
{
public:
	~UdpSender();
	static UdpSender* GetMainPtr();
	int SendCommandsById(u_int groupId);
	void SetCallBack(TRANSCALLBACK func)
	{
		m_pfun = func;
	}

	int SetFilePath(char* p, int n);

	int initT();

	static volatile int mErrState;
	static volatile int m_bUpdate;
protected:

	UdpSender();


	bool findGroupId(int id);

	int _ReadXmlFile(char* szFileName);

	static void SleepMs(unsigned long ms){::usleep(ms*1000);}
	static void* _RecvProc(void * lParam);
	static void* _SendProc(void * lParam);
	static void* _TCPrecv(void * lParam);

	static UdpSender* mCPtr;
	pthread_t m_sendTId;
	pthread_t m_recvTId;
	pthread_t m_TCPrecvTId;
	TRANSCALLBACK m_pfun;
	std::deque <SENDCMDHDR> gCommandQue;
	std::deque <SENDCMDHDR> gSendQue;
	pthread_mutex_t mutex;// = PTHREAD_MUTEX_INITIALIZER;
	sockaddr_in m_addrTo;
	char mfilePath[256];
};

#endif /* UDPSENDER_H_ */
