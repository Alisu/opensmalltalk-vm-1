/* squeak socket support header file */

/* module struct foo * self/shutdown */
sqInt socketInit(struct foo * self);
sqInt socketShutdown(struct foo * self);

typedef struct
{
  int	sessionID;
  int	socketType;  /* 0 = TCP, 1 = UDP */
  void	*privateSocketPtr;
}  SQSocket, *SocketPtr;

/* networking primitives */
sqInt sqNetworkInit(sqInt resolverSemaIndex, struct foo * self);
void  sqNetworkShutdown(struct foo * self);
void  sqResolverAbort(struct foo * self);
void  sqResolverAddrLookupResult(char *nameForAddress, sqInt nameSize, struct foo * self);
sqInt sqResolverAddrLookupResultSize(struct foo * self);
sqInt sqResolverError(struct foo * self);
sqInt sqResolverLocalAddress(struct foo * self);
sqInt sqResolverNameLookupResult(struct foo * self);
void  sqResolverStartAddrLookup(sqInt address, struct foo * self);
void  sqResolverStartNameLookup(char *hostName, sqInt nameSize, struct foo * self);
sqInt sqResolverStatus(struct foo * self);
void  sqSocketAbortConnection(SocketPtr s, struct foo * self);
void  sqSocketCloseConnection(SocketPtr s, struct foo * self);
sqInt sqSocketConnectionStatus(SocketPtr s, struct foo * self);
void  sqSocketConnectToPort(SocketPtr s, sqInt addr, sqInt port, struct foo * self);
void  sqSocketCreateNetTypeSocketTypeRecvBytesSendBytesSemaID(SocketPtr s, sqInt netType, sqInt socketType, sqInt recvBufSize, sqInt sendBufSize, sqInt semaIndex, struct foo * self);
void  sqSocketCreateNetTypeSocketTypeRecvBytesSendBytesSemaIDReadSemaIDWriteSemaID(SocketPtr s, sqInt netType, sqInt socketType, sqInt recvBufSize, sqInt sendBufSize, sqInt semaIndex, sqInt readSemaIndex, sqInt writeSemaIndex, struct foo * self);
void sqSocketCreateRawProtoTypeRecvBytesSendBytesSemaIDReadSemaIDWriteSemaID(SocketPtr s, sqInt domain, sqInt protocol, sqInt recvBufSize, sqInt sendBufSize, sqInt semaIndex, sqInt readSemaIndex, sqInt writeSemaIndex, struct foo * self);
void  sqSocketDestroy(SocketPtr s, struct foo * self);
sqInt sqSocketError(SocketPtr s, struct foo * self);
void  sqSocketListenOnPort(SocketPtr s, sqInt port, struct foo * self);
sqInt sqSocketLocalAddress(SocketPtr s, struct foo * self);
sqInt sqSocketLocalPort(SocketPtr s, struct foo * self);
sqInt sqSocketReceiveDataAvailable(SocketPtr s, struct foo * self);
sqInt sqSocketReceiveDataBufCount(SocketPtr s, char *buf, sqInt bufSize, struct foo * self);
sqInt sqSocketRemoteAddress(SocketPtr s, struct foo * self);
sqInt sqSocketRemotePort(SocketPtr s, struct foo * self);
sqInt sqSocketSendDataBufCount(SocketPtr s, char *buf, sqInt bufSize, struct foo * self);
sqInt sqSocketSendDone(SocketPtr s, struct foo * self);
/* ar 7/16/1999: New primitives for accept().  Note: If accept() calls are not supported simply make the calls fail and the old connection style will be used. */
void  sqSocketListenOnPortBacklogSize(SocketPtr s, sqInt port, sqInt backlogSize, struct foo * self);
void  sqSocketListenOnPortBacklogSizeInterface(SocketPtr s, sqInt port, sqInt backlogSize, sqInt addr, struct foo * self);
void  sqSocketAcceptFromRecvBytesSendBytesSemaID(SocketPtr s, SocketPtr serverSocket, sqInt recvBufSize, sqInt sendBufSize, sqInt semaIndex, struct foo * self);
void  sqSocketAcceptFromRecvBytesSendBytesSemaIDReadSemaIDWriteSemaID(SocketPtr s, SocketPtr serverSocket, sqInt recvBufSize, sqInt sendBufSize, sqInt semaIndex, sqInt readSemaIndex, sqInt writeSemaIndex, struct foo * self);
sqInt sqSocketReceiveUDPDataBufCountaddressportmoreFlag(SocketPtr s, char *buf, sqInt bufSize,  sqInt *address,  sqInt *port, sqInt *moreFlag, struct foo * self);
sqInt sqSockettoHostportSendDataBufCount(SocketPtr s, sqInt address, sqInt port, char *buf, sqInt bufSize, struct foo * self);
sqInt sqSocketSetOptionsoptionNameStartoptionNameSizeoptionValueStartoptionValueSizereturnedValue(SocketPtr s, char *optionName, sqInt optionNameSize, char *optionValue, sqInt optionValueSize, sqInt *result, struct foo * self);
sqInt sqSocketGetOptionsoptionNameStartoptionNameSizereturnedValue(SocketPtr s, char *optionName, sqInt optionNameSize, sqInt *result, struct foo * self);
/* tpr 4/12/06 add declarations for two new socket routines */
void sqSocketBindToPort(SocketPtr s, int addr, int port, struct foo * self);
void sqSocketSetReusable(SocketPtr s, struct foo * self);

void  sqResolverGetAddressInfoHostSizeServiceSizeFlagsFamilyTypeProtocol(char *hostName, sqInt hostSize, char *servName, sqInt servSize,
																		 sqInt flags, sqInt family, sqInt type, sqInt protocol, struct foo * self);
sqInt sqResolverGetAddressInfoSize(struct foo * self);
void  sqResolverGetAddressInfoResultSize(char *addr, sqInt addrSize, struct foo * self);
sqInt sqResolverGetAddressInfoFamily(struct foo * self);
sqInt sqResolverGetAddressInfoType(struct foo * self);
sqInt sqResolverGetAddressInfoProtocol(struct foo * self);
sqInt sqResolverGetAddressInfoNext(struct foo * self);

sqInt sqSocketAddressSizeGetPort(char *addr, sqInt addrSize, struct foo * self);
void  sqSocketAddressSizeSetPort(char *addr, sqInt addrSize, sqInt port, struct foo * self);

void  sqResolverGetNameInfoSizeFlags(char *addr, sqInt addrSize, sqInt flags, struct foo * self);
sqInt sqResolverGetNameInfoHostSize(struct foo * self);
void  sqResolverGetNameInfoHostResultSize(char *name, sqInt nameSize, struct foo * self);
sqInt sqResolverGetNameInfoServiceSize(struct foo * self);
void  sqResolverGetNameInfoServiceResultSize(char *name, sqInt nameSize, struct foo * self);

sqInt sqResolverHostNameSize(struct foo * self);
void  sqResolverHostNameResultSize(char *name, sqInt nameSize, struct foo * self);

void  sqSocketBindToAddressSize(SocketPtr s, char *addr, sqInt addrSize, struct foo * self);
void  sqSocketListenBacklog(SocketPtr s, sqInt backlogSize, struct foo * self);
void  sqSocketConnectToAddressSize(SocketPtr s, char *addr, sqInt addrSize, struct foo * self);

sqInt sqSocketLocalAddressSize(SocketPtr s, struct foo * self);
void  sqSocketLocalAddressResultSize(SocketPtr s, char *addr, int addrSize, struct foo * self);
sqInt sqSocketRemoteAddressSize(SocketPtr s, struct foo * self);
void  sqSocketRemoteAddressResultSize(SocketPtr s, char *addr, int addrSize, struct foo * self);

